/**
 *
 * @file paths.cpp
 * @author John Poulos, jpoulos2
 *
 * Project 3 for ITCS 3112.
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//Constant variable defining the PPM standard
const string PPM_TYPE = "P3";

//Function declarations
int largestValue(int **elev_data, int height, int width);
string outputPPM(int **elev_data, int max, int height, int width, string filename);
void calculatePath(string filename, int max, int height, int width, int *pointsPtr, int numPoints);

/*
 * Main function of the program. It takes the data file as a command line argument.
 * It will then create an array and read the dataset into the array.
 *
 * @param argc Number of arguments given
 * @param argv Array containing the command line arguments
 */
int main(int argc, char *argv[]){
    
    //Check to make sure we have command line argument
    if (argc != 2){
        cout << "Please give data file as command line argument" << endl;
        cout << "Ex: './paths test2.dat'" << endl;
        exit(0);
    }
    
    //Setup the file to be read in
    FILE *data_file = fopen(argv[1], "r");
    //Read the first 2 integers to get the height and width of the ppm
    int width = 1, height = 1;
    fscanf(data_file, "%d%d", &width, &height);
    
    //Get the starting points where the user wants to run the algorithm
    int numPoints = 0;
    cout << "Please enter the number of starting points you wish to select: ";
    cin >> numPoints;
    //Array to hold the starting points the user has selected
    int points[numPoints];
    int counter = 0, temp = 0;
    cout << "Please enter points between 0 and " << height - 1 << endl;
    while (counter < numPoints){
        cout << "Enter a point: ";
        cin >> temp;
        points[counter] = temp;
        counter++;
    }
    
    for (int i = 0; i < numPoints; i++){
        if (points[i] < 0 || points[i] > height - 1){
            cout << "Invalid point given" << endl;
            cout << "Quitting..." << endl;
            exit(0);
        }
    }
    int *pointsPtr = points;
    
    //Create the 1d array to store the image
    int **elev_data = new int* [height];
    for (int i = 0; i < width; i++){
        elev_data[i] = new int[width];
    }
    
    //Read all the data from the file into the array
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            fscanf(data_file, "%d", &elev_data[i][j]);
        }
    }
    
    //Get the name of the file given as an argument
    string fname = string(argv[1]);
    //Create an initial ppm based on this input array
    int max = largestValue(elev_data, height, width);
    string originalFile = outputPPM(elev_data, max, height, width, fname);
    
    //calculate the paths and write them to the image
    calculatePath(originalFile, max, height, width, pointsPtr, numPoints);
    
    
    //Delete each row
    for (int i = 0; i < height; i++){
        delete [] elev_data[i];
    }
    
    //Delete other array
    delete [] elev_data;
    
    //Close the file we wrote to
    fclose(data_file);
    
    return 0;
    
}

/**
 * Returns the largest value in the array.
 * This is necessary for the PPM format
 *
 * @param **elev_data Pointer to the array we are searching
 * @param height Height of the array
 * @param width Width of the array
 */
int largestValue(int **elev_data, int height, int width){
    int max = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if(elev_data[i][j] > max)
                max = elev_data[i][j];
        }
    }
    return max;
}

/**
 * This function takes the dataset and outputs the ppm file.
 * It will automatically name the file for the user based on the input data file name.
 *
 * @param **elev_data Pointer to the array containing the dataset
 * @param max The max value in the array, used for PPM standard
 * @param height Height of the image
 * @param width Width of the image
 * @param filename Filename that the user gave as an argument
 *
 * @return Returns a string containing the name of the ppm file it wrote to
 */
string outputPPM(int **elev_data, int max, int height, int width, string filename){
    
    //First we need to get the name for the file we want to output
    //in this case we take the name of the dataset file and attach .PPM to it
    size_t lastindex = filename.find_first_of(".");
    string outname = filename.substr(0, lastindex);
    //cout << outname << "\n" << endl;
    string name = outname;
    outname = outname + ".ppm";
    
    //Open the output file for writing
    FILE *output_file = fopen(outname.c_str() , "w");
    cout << "Writing initial image to file: " << outname << endl;
    
    //Print the PPM header
    fprintf(output_file, "%s\n", PPM_TYPE.c_str());
    //Print the width and height
    fprintf(output_file, "%i %i\n", width, height);
    
    if (max > 255){
        //Print max val
        fprintf(output_file, "%i\n", max/255);
        //Print the array to the ppm file
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                fprintf(output_file, "%i ", elev_data[i][j]/255);
                fprintf(output_file, "%i ", elev_data[i][j]/255);
                fprintf(output_file, "%i ", elev_data[i][j]/255);
            }
        }
    } else {
        //Print max val
        fprintf(output_file, "%i\n", max);
        //Print the array to the ppm file
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                fprintf(output_file, "%i ", elev_data[i][j]);
                fprintf(output_file, "%i ", elev_data[i][j]);
                fprintf(output_file, "%i ", elev_data[i][j]);
            }
        }
    }
    
    fclose(output_file);
    return name;
    
}

/**
 *
 * Method that calculates the paths across the image.
 *
 * @param filename Name of the file, we will use this to name the output file
 * @param max Max value in the array, necessary for the ppm format to work.
 * @param height Height of the ppm
 * @param width Width of the ppm
 * @param *pointsPtr Pointer to the array containing the start points for the algorithm
 * @param numPoints Number of elements in the pointsPtr array
 *
 */
void calculatePath(string filename, int max, int height, int width, int *pointsPtr, int numPoints){
    cout << "Calculating paths..." << endl;
    //Open the existing ppm for reading
    string filename1 = filename + ".ppm";
    FILE *dataset = fopen(filename1.c_str(), "r");
    
    //Create an array to store the entire ppm file
    int **ppm_data = new int* [height];
    for (int i = 0; i < width; i++){
        ppm_data[i] = new int[width*3];
    }
    
    //Read the ppm into a new dynamic array
    //Throw away all the starting data, we can re add that later
    fscanf(dataset, "%*s%*d%*d%*d");
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width*3; j++){
            fscanf(dataset, "%d ", &ppm_data[i][j]);
        }
    }

    //Row,col
    int counter = 0;
    int guess1R = 0, guess1C = 0, guess2R = 0, guess2C = 0, guess3R = 0, guess3C = 0;
    int diff1 = 0, diff2 = 0, diff3 = 0;
    int initialVal = 0;
    int rando = 0;
    while (counter < numPoints){
        initialVal = ppm_data[pointsPtr[counter]][0];
        
        
        //Set the starting pixel
        ppm_data[pointsPtr[counter]][0] = max;
        ppm_data[pointsPtr[counter]][1] = 0;
        ppm_data[pointsPtr[counter]][2] = 0;
        
        int currentColumn = 0;
        int currentRow = pointsPtr[counter];
        
        while (currentColumn < width * 3 - 3){
            
            //Edge cases
            if (currentRow == 0){
                //Directly to the right
                guess2R = currentRow;
                guess2C = currentColumn + 3;
                //Bottom right
                guess3R = currentRow + 1;
                guess3C = currentColumn + 3;
                
                diff2 = abs(ppm_data[guess2R][guess2C] - initialVal);
                diff3 = abs(ppm_data[guess3R][guess3C] - initialVal);
                
                if (diff3 < diff2){
                    //cout << "Too high moving down\n\n";
                    initialVal =  ppm_data[guess3R][guess3C];
                    ppm_data[guess3R][guess3C] = max;
                    ppm_data[guess3R][guess3C + 1] = 0;
                    ppm_data[guess3R][guess3C + 2] = 0;
                    currentRow = guess3R;
                    currentColumn = guess3C;
                } else {
                    //cout << "Too high moving right\n\n";
                    initialVal =  ppm_data[guess2R][guess2C];
                    ppm_data[guess2R][guess2C] = max;
                    ppm_data[guess2R][guess2C + 1] = 0;
                    ppm_data[guess2R][guess2C + 2] = 0;
                    currentRow = guess2R;
                    currentColumn = guess2C;
                }
            } else if (currentRow == height - 1){
                //Top right
                guess1R = currentRow - 1;
                guess1C = currentColumn + 3;
                //Directly to the right
                guess2R = currentRow;
                guess2C = currentColumn + 3;
                
                diff1 = abs(ppm_data[guess1R][guess1C] - initialVal);
                diff2 = abs(ppm_data[guess2R][guess2C] - initialVal);
                
                if (diff1 < diff2){
                    //cout << "Too low moving up\n\n";
                    initialVal =  ppm_data[guess1R][guess1C];
                    ppm_data[guess1R][guess1C] = max;
                    ppm_data[guess1R][guess1C + 1] = 0;
                    ppm_data[guess1R][guess1C + 2] = 0;
                    currentRow = guess1R;
                    currentColumn = guess1C;
                } else {
                    //cout << "Too low moving across\n\n";
                    initialVal =  ppm_data[guess2R][guess2C];
                    ppm_data[guess2R][guess2C] = max;
                    ppm_data[guess2R][guess2C + 1] = 0;
                    ppm_data[guess2R][guess2C + 2] = 0;
                    currentRow = guess2R;
                    currentColumn = guess2C;
                }
            } else {
                guess1R = currentRow - 1;
                guess1C = currentColumn + 3;
                //Directly to the right
                guess2R = currentRow;
                guess2C = currentColumn + 3;
                //Bottom right
                guess3R = currentRow + 1;
                guess3C = currentColumn + 3;
                
                //Calcaulte the elevation change from those points
                //Calculate the elevation change
                diff1 = abs(ppm_data[guess1R][guess1C] - initialVal);
                diff2 = abs(ppm_data[guess2R][guess2C] - initialVal);
                diff3 = abs(ppm_data[guess3R][guess3C] - initialVal);
                
                
                if (guess1R <= 0){
                    //close to the edge?. Force right 1
                    if (diff3 < diff2){
                        //cout << "Too high moving down\n\n";
                        initialVal =  ppm_data[guess3R][guess3C];
                        ppm_data[guess3R][guess3C] = max;
                        ppm_data[guess3R][guess3C + 1] = 0;
                        ppm_data[guess3R][guess3C + 2] = 0;
                        currentRow = guess3R;
                        currentColumn = guess3C;
                    } else {
                        //cout << "Too high moving right\n\n";
                        initialVal =  ppm_data[guess2R][guess2C];
                        ppm_data[guess2R][guess2C] = max;
                        ppm_data[guess2R][guess2C + 1] = 0;
                        ppm_data[guess2R][guess2C + 2] = 0;
                        currentRow = guess2R;
                        currentColumn = guess2C;
                    }
                } else if (guess3R > width*height*3){
                    //close to the edge?. Force right 1
                    if (diff1 < diff2){
                        //cout << "Too low moving up\n\n";
                        initialVal =  ppm_data[guess1R][guess1C];
                        ppm_data[guess1R][guess1C] = max;
                        ppm_data[guess1R][guess1C + 1] = 0;
                        ppm_data[guess1R][guess1C + 2] = 0;
                        currentRow = guess1R;
                        currentColumn = guess1C;
                    } else {
                        //cout << "Too low moving across\n\n";
                        initialVal =  ppm_data[guess2R][guess2C];
                        ppm_data[guess2R][guess2C] = max;
                        ppm_data[guess2R][guess2C + 1] = 0;
                        ppm_data[guess2R][guess2C + 2] = 0;
                        currentRow = guess2R;
                        currentColumn = guess2C;
                    }
                } else if (diff1 == diff2 && diff1 == diff3){
                    //Elevation is the same, move right
                    initialVal =  ppm_data[guess2R][guess2C];
                    ppm_data[guess2R][guess2C] = max;
                    ppm_data[guess2R][guess2C + 1] = 0;
                    ppm_data[guess2R][guess2C + 2] = 0;
                    currentRow = guess2R;
                    currentColumn = guess2C;
                    //cout << "No change, move right 1\n\n";
                } else if (diff1 < diff2 && diff1 < diff3){
                    //Move to guess 1
                    //cout << "guess1, Up and right\n\n";
                    initialVal =  ppm_data[guess1R][guess1C];
                    ppm_data[guess1R][guess1C] = max;
                    ppm_data[guess1R][guess1C + 1] = 0;
                    ppm_data[guess1R][guess1C + 2] = 0;
                    currentRow = guess1R;
                    currentColumn = guess1C;
                } else if (diff2 < diff1 && diff2 < diff3){
                    //Move to guess 2
                    //cout << "guess2, Move right\n\n";
                    initialVal =  ppm_data[guess2R][guess2C];
                    ppm_data[guess2R][guess2C] = max;
                    ppm_data[guess2R][guess2C + 1] = 0;
                    ppm_data[guess2R][guess2C + 2] = 0;
                    currentRow = guess2R;
                    currentColumn = guess2C;
                } else if (diff3 < diff1 && diff3 < diff2){
                    //Move to guess 3
                    //cout << "guess3, down and right\n\n";
                    initialVal =  ppm_data[guess3R][guess3C];
                    ppm_data[guess3R][guess3C] = max;
                    ppm_data[guess3R][guess3C + 1] = 0;
                    ppm_data[guess3R][guess3C + 2] = 0;
                    currentRow = guess3R;
                    currentColumn = guess3C;
                } else if (diff2 == diff3 && diff2 < diff1 && diff3 < diff1){
                    //cout << "moving right\n\n";
                    initialVal =  ppm_data[guess2R][guess2C];
                    ppm_data[guess2R][guess2C] = max;
                    ppm_data[guess2R][guess2C + 1] = 0;
                    ppm_data[guess2R][guess2C + 2] = 0;
                    currentRow = guess2R;
                    currentColumn = guess2C;
                } else if (diff1 == diff2 && diff1 < diff3 && diff2 < diff3){
                    //cout << "moving right\n\n";
                    initialVal =  ppm_data[guess2R][guess2C];
                    ppm_data[guess2R][guess2C] = max;
                    ppm_data[guess2R][guess2C + 1] = 0;
                    ppm_data[guess2R][guess2C + 2] = 0;
                    currentRow = guess2R;
                    currentColumn = guess2C;
                } else if (diff1 == diff3 && diff1 < diff2 && diff3 < diff2){
                    //tie between 1 and 3, flip
                    rando = rand() % 100;
                    if (rando % 2 == 0) {
                        //cout << "RAND 0 guess3\n\n";
                        initialVal =  ppm_data[guess3R][guess3C];
                        ppm_data[guess3R][guess3C] = max;
                        ppm_data[guess3R][guess3C + 1] = 0;
                        ppm_data[guess3R][guess3C + 2] = 0;
                        currentRow = guess3R;
                        currentColumn = guess3C;
                    } else {
                        //cout << "RAND 1 guess1\n\n";
                        initialVal =  ppm_data[guess1R][guess1C];
                        ppm_data[guess1R][guess1C] = max;
                        ppm_data[guess1R][guess1C + 1] = 0;
                        ppm_data[guess1R][guess1C + 2] = 0;
                        currentRow = guess1R;
                        currentColumn = guess1C;
                    }
                } else {
                    //Just in case?
                    //cout << "IDK moving right\n\n";
                    initialVal =  ppm_data[guess2R][guess2C];
                    ppm_data[guess2R][guess2C] = max;
                    ppm_data[guess2R][guess2C + 1] = 0;
                    ppm_data[guess2R][guess2C + 2] = 0;
                    currentRow = guess2R;
                    currentColumn = guess2C;
                }
            }
        }
        counter++;
    }
    
    //Once the path is calculated in the array
    string filename2 = filename + "_OUTPUT.png";
    FILE *output_file = fopen(filename2.c_str(), "w");
    cout << "Writing image with paths to file: " << filename2 << endl;
    
    fprintf(output_file, "%s\n", PPM_TYPE.c_str());
    //Print the width and height
    fprintf(output_file, "%i %i\n", width, height);
    //Print max val
    if (max > 255){
        max = max / 255;
    }
    fprintf(output_file, "%i\n", max);
    //Print the array to the ppm file
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width*3; j++){
            fprintf(output_file, "%d ", ppm_data[i][j]);
        }
        fprintf(output_file, "\n");
    }
    
    fclose(dataset);
    fclose(output_file);
    
    //Delete each row starting from bottom
    for (int i = 0; i < height; i++){
        delete [] ppm_data[i];
    }
    
    delete [] ppm_data;
}
