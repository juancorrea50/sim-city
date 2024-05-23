#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include "commercial.h"
#include "commCollect.h"
#include "Industry.h"
#include "residential.h"
#include "resColl.h"
#include "PowerplantCollect.h"
#include "Industrial.h"
#include "Seasons.h"
#include "fire.h"
#include "disaster.h"

#define MAX_REGION_SIZE 20 // The maximum size 

using namespace std;

// Struct to hold simulation configuration
struct SimulationConfig {
    char regionLayout[MAX_REGION_SIZE][MAX_REGION_SIZE]; // Maximum region size
    int rows;
    int cols;
    int maxTimeSteps;
    int refreshRate;
    string regionFilename;
};
//Instantiate the collections class
commCollect cColl;
resColl res;
PowerplantCollect powerColl;
disaster dis;
// Function to initialize simulation from user input
void initializeSimulation(SimulationConfig& config) {
    // Get simulation configuration filename from user
    cout << "Enter simulation configuration file name: ";
    cin >> config.regionFilename;

    // Read simulation configuration
    ifstream configFile(config.regionFilename);
    if (!configFile) {
        cerr << "Error opening configuration file." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(configFile, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
	    string key = line.substr(0, colonPos);
	    string value = line.substr(colonPos + 1);

            cout << "Key: " << key << ", Value: " << value << endl; // Output region file data to user

            if (key == "Region Layout") {
                config.regionFilename = value;
            } else if (key == "Time Limit") {
                config.maxTimeSteps = stoi(value);
            } else if (key == "Refresh Rate") {
                config.refreshRate = stoi(value);
            }
        }
    }
    configFile.close();

    // Read region layout
    ifstream regionFile(config.regionFilename);
    if (!regionFile) {
        cerr << "Error opening region file." << endl;
        exit(EXIT_FAILURE);
    }

    // Determine number of rows and columns in the region layout file
    config.rows = 0;
    config.cols = 0;
    while (getline(regionFile, line)) {
        config.rows++; // Increment row count for each line
        config.cols = max(config.cols, static_cast<int>(line.size())); // Update column count
    }

    // Resize region layout array based on the determined rows and columns
    for (int i = 0; i < MAX_REGION_SIZE; i++) {
        for (int j = 0; j < MAX_REGION_SIZE; j++) {
            config.regionLayout[i][j] = ' '; // Initialize region layout with spaces
        }
    }

    regionFile.clear(); // Reset file stream state
    regionFile.seekg(0); // Reset file stream position to beginning

    // Read region layout data into the array
        for (int i = 0; i < config.rows; i++) {
            getline(regionFile, line);
            // Ensure that the line does not exceed the maximum number of columns
            line.resize(MAX_REGION_SIZE, ' '); // Pad with spaces if needed
                for (size_t j = 0; j < line.size(); j++) {
                    if (line[j] != ',' && line[j]!= ' ' && line[j] != '\0' )
                        config.regionLayout[i][j] = line[j];
             }
         }
         regionFile.close(); // Close region file
    }

// Function to output region layout to the user
void outputRegionLayout(const SimulationConfig& config) {
    for (int i = 0; i < config.rows; i++) {
        for (int j = 0; j < config.cols; j++) {
            if (config.regionLayout[i][j] != ',') {
                cout << config.regionLayout[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Function to output final region layout
void outputFinalRegionLayout(vector<vector<cell*>> region) {
    // Implementation for analyzing the entire region
    for (int i = 0; i < region.size(); ++i) {
        for (int j = 0; j < region[i].size(); ++j) {
            switch (region[i][j]->getCellTag()) {
                case 'R':
                    std::cout << "Residential ";
                    break;
                case 'I':
                    std::cout << "Industrial ";
                    break;
                case 'C':
                    std::cout << "Commercial ";
                    break;
                case '-':
                    std::cout << "Road ";
                    break;
                case 'T':
                    std::cout << "Powerline ";
                    break;
                case '#':
                    std::cout << "Powerline over Road ";
                    break;
                case 'P':
                    std::cout << "Power Plant ";
                    break;
                case 'F': 
                    std::cout << "Fire ";
                    break; 
                case 'H': 
                    std::cout << "Firehouse "; 
                    break;
                default:
                    std::cout << "Unknown ";
            }
            std::cout << "Population: " << region[i][j]->getPop() << ", Pollution: " << region[i][j]->getPop() << std::endl;
        }
    }
}
//Fix
// Function to calculate totals
void calculateTotals(vector<vector<cell*>> region) {
    int totalResidentialPopulation = 0;
    int totalIndustrialPopulation = 0;
    int totalCommercialPopulation = 0;
    int totalPollution = 0;

    for (int i = 0; i < region.size(); ++i) {
        for (int j = 0; j < region[i].size(); ++j) {
            switch (region[i][j]->getCellTag()) {
                case 'R':
                    totalResidentialPopulation += region[i][j]->getPop();
                    break;
                case 'I':
                    totalIndustrialPopulation += region[i][j]->getPop();
                    break;
                case 'C':
                    totalCommercialPopulation += region[i][j]->getPop();
                    break;
                default:
                    break;
            }
            totalPollution += region[i][j]->getPollution();
        }
    }

    std::cout << "Total Residential Population: " << totalResidentialPopulation << std::endl;
    std::cout << "Total Industrial Population: " << totalIndustrialPopulation << std::endl;
    std::cout << "Total Commercial Population: " << totalCommercialPopulation << std::endl;
    std::cout << "Total Pollution: " << totalPollution << std::endl;
}

// Function to analyze desired area
void analyzeDesiredArea(vector<vector<cell*>> region) {
    int startX, startY, endX, endY;
    int totalPopulation = 0;
    int totalPollution = 0;

    std::cout << "Enter coordinates of the area to analyze (startX, startY, endX, endY): ";
    std::cin >> startX >> startY >> endX >> endY;

    // Bounds checking
    if (startX < 0 || startY < 0 || endX >= region.size() || endY >= region[0].size() || startX > endX || startY > endY) {
        std::cout << "Invalid coordinates. Please enter valid coordinates within the region bounds." << std::endl;
        return;
    }

    // Iterate over the specified area
    for (int i = startX; i <= endX; ++i) {
        for (int j = startY; j <= endY; ++j) {
            totalPopulation += region[i][j]->getPop();
            totalPollution += region[i][j]->getPollution();
        }
    }

    std::cout << "Total Population in the specified area: " << totalPopulation << std::endl;
    std::cout << "Total Pollution in the specified area: " << totalPollution << std::endl;
}


//TODO: Move this out of main & into the collections class
/// <summary>
/// Builds a 2D vector of cells from the 2D char array from the SimulationConfig struct, and sets the cell type based on the char.
/// </summary>
/// <param name="config">A reference to the simulation config</param>
/// <returns>The 2D vector of cells</returns>
vector<vector<cell*>> BuildCellVector(const SimulationConfig& config)
{
    //Temporary vector to move the chars from the config array to the cell vector array
    vector<vector<cell*>> region(config.rows, vector<cell*>(config.cols));
    //Copies the chars from the config.regionLayout 2D array to the 2d cell vector
    //The config array has an extra character inbetween the cells we care about
    //So we are just reading every other cell in the j dimension
    for (int i = 0; i < config.rows; i++)
    {
        for (int j = 0; j < config.cols; j+=2)
        {
            if (config.regionLayout[i][j] != ',' && config.regionLayout[i][j] != '\0'){
                if(config.regionLayout[i][j] == 'C'){
                    //Create new Commercial Cell and push to cell* vector
                    commercial* newCell =  new commercial(i, j/2);
                    newCell->setTag(config.regionLayout[i][j]);
                    region[i][j/2] = newCell;
                    cColl.collectCells(newCell);

                } else if(config.regionLayout[i][j] == 'R'){
                    //Create new Residential cell pointer and push to cell* vector
                    residential* resCell =  new residential(i, j/2);
                    resCell->setTag(config.regionLayout[i][j]);
                    region[i][j/2] = resCell;
                    res.resCollect(resCell);
                } else if (config.regionLayout[i][j] == 'I') {
                    //Create new Industrial cell pointer and push to cell* vector
                    Industrial* indCell = new Industrial(i, j / 2);
                    indCell->setTag(config.regionLayout[i][j]);
                    region[i][j / 2] = indCell;
                } 
                else if (config.regionLayout[i][j] == 'P') {
                    Powerplant* powerCell = new Powerplant(i, j/2);
                    powerCell->setTag(config.regionLayout[i][j]);
                    region[i][j/2] = powerCell;
                    powerColl.CollectPowerplantCell(powerCell);
                }
                else{ 
                    //Else creates a new cell for things like T,#,- etc.
                    cell* newCell =  new cell(i, j/2);
                    newCell->setTag(config.regionLayout[i][j]);
                    region[i][j/2] = newCell;
                }

            }
        }
    }
    //Right now the region has extra empty space at the ends of the 2d vector
    //ex. with an 8x8 region, right now the size is 8x15. 
    //thankfully just the ends of the vector are empty, so a resize will crop out the extra empty space
    for (int i = 0; i < region.size(); i++)
    {
        region[i].resize((config.cols / 2) + 1);
    }

    return region;
}

void printRegion(vector<vector<cell*>> region){
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            cout << region[i][j]->getCellTag() << "    ";
        }
        cout << endl;
    }
}
void deleteRegion(vector<vector<cell*>> region){
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j+=2){
            if(region[i][j]->getCellTag() == 'A'){
                if(i==2 && j==5){
                    delete region[i][j];
                } else {

                }
            } else {
                delete region[i][j];
            }

        }
    }
}

vector<vector<char>> createBeforeRegion(vector<vector<cell*>> region){
    
    vector<vector<char>> savedRegion(region.size(), vector<char>(region[0].size()));

    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            if(region[i][j]->getPop() > 0){
                string popN = to_string(region[i][j]->getPop());
                savedRegion[i][j] = *popN.c_str();
            } else {
                savedRegion[i][j] = region[i][j]->getCellTag();
            }

        }
    }
    return savedRegion;
}
void printBeforeAndAfterRegion(vector<vector<char>> bRegion,vector<vector<cell*>> region){
    for (int i = 0; i < bRegion.size(); i++){
        //Before
        for (int j = 0; j < bRegion[i].size(); j++){
            cout << bRegion[i][j]<< "    ";
        }

        
        //After
        for(int l =0; l<region[i].size();l++){
            if(region[i][l]->getPop() > 0){
                if(region[i][l]->getCellTag() == 'A'){
                    cout <<region[i][l]->getCellTag()<< region[i][l]->getPop()<< "   ";    
                } else {
                    cout << region[i][l]->getPop() << "   ";
                }
            }  else {
                cout << region[i][l]->getCellTag() << "   ";
            }
        }
        cout << '\t' << '\t' << '\t' << endl;
    }
}



int main() {
    //Varable Section
    int avWorkers = 0;
    int avGoods = 0;

    int avPower = -1;
    int powerConsumption = -1;

    cell* chosenCell;

    bool Scheck = true;

    //Region Section
    SimulationConfig config;
    //Initialize simulation configuration
    initializeSimulation(config);
   
    //Calling the BuildCellVector function to take in and return from the growth of all regions
    vector<vector<cell*>> region = BuildCellVector(config);

    //Initialize saveRegion for before snapshot and userOption for quitting the loop
    vector<vector<char>> saveRegion;
    string userOption;

    res.resAdj(region);
    res.AdjPower(region[6][5]);
    //Logic Section
    cColl.setAllAdj(region);
    Industry* industry = new Industry(region);
    Fire* fire = new Fire(1,2,3);
    cin.ignore();
    powerColl.SetRegion(region);
    //Loop to output maxTimeSteps


    //Set initial power use & production
    if (avPower == -1)
        avPower = powerColl.GetTotalPower();
    if (powerConsumption == -1)
        powerConsumption = powerColl.CalculateInitialPowerUse();
    
    for (int counter = 0; counter < config.maxTimeSteps; counter++) 
    {
        if(userOption == "q"){
            break;
        }
        saveRegion = createBeforeRegion(region);
        
        if(counter == 0){
            cout << endl;
            cout << "Time Step: " << counter << endl;
            
            cout << "Initial region layout:" << endl << endl;
            printRegion(region);
            cout << "Available Goods: " << avGoods << endl;
            cout << "Available Workers: " << avWorkers << endl;
            cout << "Available Power: " << avPower << endl;
            cout << "Power Use: " << powerConsumption << endl;

        } else {
            cout << endl << endl;
            cout << "Time Step: " << counter << endl;

            /*if (counter == 5 || counter == 10 || counter == 15 || counter == 20)
            {

                dis.Emergency();
            }*/
            if(avWorkers >= 1 && avGoods >= 1){
                //Commercial
                cColl.commercialGrowth(avWorkers,avGoods,region);
                avWorkers--;
                avGoods--;
            } else if(avWorkers >= 2){
                //Indsutrial
                industry->CalculateIndustrialGrowth(1,avWorkers,avGoods);
            } else {
                //Residential
                res.resGrowth(avWorkers);

            }

            if (counter == 5 || counter == 10 || counter == 15 || counter == 20)
            {

                dis.Emergency();
                res.resDecay(avWorkers);
                //res.resGone(avWorkers);
            }

            //Extended Seasons functionalities
            if (counter % 5 == 0) {  //output the current season after 5 steps
                Seasons::SetTimeStep(Scheck);
                Seasons::SeasonCheck(counter);
                cout << "Current Season: " << Seasons::getCurrentSeason() << endl;
            }
            if (counter % 2 == 0 ){
                cout << "firefighters are on their way" << endl; 
            }
            if(counter % 2 == 0 && cColl.getHasArena() == true){
                //Start Event every 2 turns **DIFFERS FROM DESIGN THAT SAYS 5 DUE TO TIME STEP CONSTRAINTS**
                cColl.startEvent(region);
            } else if(cColl.getHasArena() == true){
                cColl.endEvent();
            }


            //do powerplant stuff
            powerColl.CalcPower(avPower, powerConsumption, avWorkers);

            //Print Region Before and After changes
            printBeforeAndAfterRegion(saveRegion, region);
            cout << endl;
            cout << "\t     " << "Before" << "\t \t \t \t    " << "After" << endl;
            cout << "Available Goods: " << avGoods << endl;
            cout << "Available Workers: " << avWorkers << endl;
            cout << "Available Power: " << avPower << endl;
            cout << "Power Use: " << powerConsumption << endl;
        }
	    
        //End of functionality press enter to continue loop or 'q' to quit
        cout << "Please enter q if you would like to exit simulation" << endl;
        cout << "Just press enter to continue" << endl;
        getline(cin, userOption);
        
    }
    
    //Analyze and zoom in on a specific region
    printBeforeAndAfterRegion(saveRegion,region);
    industry->CalculateAllPollution();
    calculateTotals(region);
    analyzeDesiredArea(region);


    //Very end delete pointer vector region
    deleteRegion(region);
    delete industry;
    return 0;
}

