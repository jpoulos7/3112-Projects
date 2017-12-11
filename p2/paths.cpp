/**
 *
 * @file paths.cpp
 * @author John Poulos, jpoulos2
 *
 * Project 2 for ITCS 3112.
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//Function declarations
int largestValue(int *data, int size);
void outputPPM(int *data, int max, int height, int width, string filename);
void calculatePath(string filename, int max, int height, int width);

//Constant variable defining the PPM standard
const string PPM_TYPE = "P3";


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
    
    FILE *data_file = fopen(argv[1], "r");
    
    //Read first 2 ints to get width and height
    int width = 1, height = 1;
    fscanf(data_file, "%d%d", &width, &height);
    
    //Setup the array
    int *data;
    int size = width*height;
    data = (int *)malloc(sizeof(int)*(size));
    
    //Read all the values from the dataset into the array
    int counter = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            fscanf(data_file, "%d", &data[counter]);
            //cout << data[counter] << " ";
            counter++;
        }
        //cout << "\n" << endl;
    }
    
    //Save the filename to a string and pass it to the next function
    string fname = string(argv[1]);
    outputPPM(data, largestValue(data, size), height, width, fname);
    
    //Free and close everything
    free(data);
    fclose(data_file);
    
    return 0;
}

/**
 * Returns the largest value in the array.
 * This is necessary for the PGM format
 *
 * @param *data Pointer to the array we are searching
 * @param size Size of the array we are searching
 */
int largestValue(int *data, int size){
    int max = 0;
    for (int i = 0; i < size; i++){
        if (data[i] > max){
            max = data[i];
        }
    }
    
    return max;
}

/**
 * This function takes the dataset and outputs the ppm file.
 * It will automatically name the file for the user based on the input data file name.
 *
 * @param data Pointer to the array containing the dataset
 * @param max The max value in the array, used for PPM standard
 * @param height Height of the image
 * @param width Width of the image
 * @param filename Filename that the user gave as an argument
 */
void outputPPM(int *data, int max, int height, int width, string filename){
    
    //cout << filename << endl;
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
    
    //Make sure our values follow the ppm standard
    if (max > 255){
        //Print max val
        fprintf(output_file, "%i\n", max/255);
        //Print the array to the ppm file
        for (int i = 0; i < width*height; i++){
            fprintf(output_file, "%i ", data[i]/255);
            fprintf(output_file, "%i ", data[i]/255);
            fprintf(output_file, "%i ", data[i]/255);
        }
        
    } else {
        //Print max val
        fprintf(output_file, "%i\n", max);
        //Print the array to the ppm file
        //int count = 1;
        for (int i = 0; i < width*height; i++){
            fprintf(output_file, "%i ", data[i]);
            fprintf(output_file, "%i ", data[i]);
            fprintf(output_file, "%i ", data[i]);
        }
    }
    
    fclose(output_file);
    
    //Calculate the path across the image
    calculatePath(name, max, height, width);
}

/**
 *
 * Method that calculates the path across the image.
 *
 * @param filename Name of the file, we will use this to name the output file
 * @param max Max value in the array, necessary for the ppm format to work.
 * @param height Height of the ppm
 * @param width Width of the ppm 
 *
 */
void calculatePath(string filename, int max, int height, int width){
    //Ask the user which row to start the path finding algorithm on
    int input = 0;
    cout << "Please select a row from 0 to " << height-1 << " to start the path finding algorithm: ";
    cin >> input;
    
    if (input < 0 || input > height - 1){
        calculatePath(filename, max, height, width);
    }
    
    //Read in the existing ppm file
    string filename1 = filename + ".ppm";
    FILE *dataset = fopen(filename1.c_str(), "r");
    
    
    if (max > 255){
        max = max / 255;
    }
    
    //Create a 1d array for storing the ppm file
    int *data;
    int size = width*height * 3;
    data = (int *)malloc(sizeof(int)*(size + 3) + sizeof(char)*3);
    
    //Take the existing ppm and read it into a 1d array
    fscanf(dataset, "%*s%*d%*d%*d");
    for (int i = 0; i < size*3; i++){
        fscanf(dataset, "%d ", &data[i]);
    }
    
    //Find the starting column in the 1d array
    int startPoint = input * height * 3;
    int initial = data[startPoint];
    //Set the starting pixel
    data[startPoint] = max;
    data[startPoint + 1] = 0;
    data[startPoint + 2] = 0;
    
    //loop/function to find path
    int column = 0;
    int guess1 = 0, guess2 = 0, guess3 = 0;
    int diff1 = 0, diff2 = 0, diff3 = 0;
    int rando = 0;
    int current = startPoint + 2;
    while (column < width - 1){
        //Top right
        guess1 = current - width * 3 + 1;
        //Directly to the right
        guess2 = current + 1;
        //Bottom right
        guess3 = current + width * 3 + 1;
        
        //cout << "CURRENTposition: " << current - 2<< " ";
        //cout << "DATA[currentposition]: " << initial << "\n";
        
        //cout << "GUESSpos 1: " << guess1 << "\n";
        //cout << "GUESSpos 2: " << guess2 << "\n";
        //cout << "GUESSpos 3: " << guess3 << "\n";
        
        //Calculate the elevation change
        diff1 = abs(data[guess1] - initial);
        diff2 = abs(data[guess2] - initial);
        diff3 = abs(data[guess3] - initial);
        //cout << "Diff 1: " << data[guess1] << "-" << initial << "=" << diff1 << "\n";
        //cout << "Diff 2: " << data[guess2] << "-" << initial << "=" << diff2 << "\n";
        //cout << "Diff 3: " << data[guess3] << "-" << initial << "=" << diff3 << "\n";
        
        if (guess1 < 0){
            //close to the edge?. Force right 1
            if (diff3 < diff2){
                //cout << "Too high moving down\n\n";
                initial = data[guess3];
                data[guess3] = max;
                data[guess3 + 1] = 0;
                data[guess3 + 2] = 0;
                current = guess3 + 2;
            } else {
                //cout << "Too high moving right\n\n";
                initial = data[guess2];
                data[guess2] = max;
                data[guess2 + 1] = 0;
                data[guess2 + 2] = 0;
                current = guess2 + 2;
            }
        } else if (guess3 > width*height*3){
            //close to the edge?. Force right 1
            if (diff1 < diff2){
                //cout << "Too low moving up\n\n";
                initial = data[guess1];
                data[guess1] = max;
                data[guess1 + 1] = 0;
                data[guess1 + 2] = 0;
                current = guess1 + 2;
            } else {
                //cout << "Too low moving across\n\n";
                initial = data[guess2];
                data[guess2] = max;
                data[guess2 + 1] = 0;
                data[guess2 + 2] = 0;
                current = guess2 + 2;
            }
        } else if (diff1 == diff2 && diff1 == diff3){
            //Elevation is the same, move right
            initial = data[guess2];
            data[guess2] = max;
            data[guess2 + 1] = 0;
            data[guess2 + 2] = 0;
            current = guess2 + 2;
            //cout << "No change, move right 1\n\n";
        } else if (diff1 < diff2 && diff1 < diff3){
            //Move to guess 1
            //cout << "guess1, Up and right\n\n";
            initial = data[guess1];
            data[guess1] = max;
            data[guess1 + 1] = 0;
            data[guess1 + 2] = 0;
            current = guess1 + 2;
        } else if (diff2 < diff1 && diff2 < diff3){
            //Move to guess 2
            //cout << "guess2, Move right\n\n";
            initial = data[guess2];
            data[guess2] = max;
            data[guess2 + 1] = 0;
            data[guess2 + 2] = 0;
            current = guess2 + 2;
        } else if (diff3 < diff1 && diff3 < diff2){
            //Move to guess 3
            //cout << "guess3, down and right\n\n";
            initial = data[guess3];
            data[guess3] = max;
            data[guess3 + 1] = 0;
            data[guess3 + 2] = 0;
            current = guess3 + 2;
        } else if (diff2 == diff3 && diff2 < diff1 && diff3 < diff1){
            //else if (diff2 == diff3 && diff1 != diff2 && !(diff1 < diff3)){
            //cout << "moving right\n\n";
            initial = data[guess2];
            data[guess2] = max;
            data[guess2 + 1] = 0;
            data[guess2 + 2] = 0;
            current = guess2 + 2;
        } else if (diff1 == diff2 && diff1 < diff3 && diff2 < diff3){
            //cout << "moving right\n\n";
            initial = data[guess2];
            data[guess2] = max;
            data[guess2 + 1] = 0;
            data[guess2 + 2] = 0;
            current = guess2 + 2;
        } else if (diff1 == diff3 && diff1 < diff2 && diff3 < diff2){
            //tie between 1 and 3, flip
            rando = rand() % 100;
            if (rando % 2 == 0) {
                //cout << "RAND 0 guess3\n\n";
                initial = data[guess3];
                data[guess3] = max;
                data[guess3 + 1] = 0;
                data[guess3 + 2] = 0;
                current = guess3 + 2;
            } else {
                //cout << "RAND 1 guess1\n\n";
                initial = data[guess1];
                data[guess1] = max;
                data[guess1 + 1] = 0;
                data[guess1 + 2] = 0;
                current = guess1 + 2;
            }
        } else {
            //Just in case?
            //cout << "IDK moving right\n\n";
            initial = data[guess2];
            data[guess2] = max;
            data[guess2 + 1] = 0;
            data[guess2 + 2] = 0;
            current = guess2 + 2;
        }
        
        column++;
    }
    
    //Once the path is calculated in the array
    string filename2 = filename + "_OUTPUT.ppm";
    FILE *output_file = fopen(filename2.c_str(), "w");
    cout << "Writing image with path to file: " << filename2 << endl;
    
    fprintf(output_file, "%s\n", PPM_TYPE.c_str());
    //Print the width and height
    fprintf(output_file, "%i %i\n", width, height);
    //Print max val
    fprintf(output_file, "%i\n", max);
    //Print the array to the ppm file
    int count = 1;
    for (int i = 0; i < width*height*3; i++){
        fprintf(output_file, "%i ", data[i]);
        if (count == width*3){
            fprintf(output_file, "\n");
            count = 0;
        }
        count++;
    }
    
    fclose(dataset);
    fclose(output_file);
    free(data);
    exit(0);
    
}
