/**
 *
 * @file image.cpp
 * @author John Poulos, jpoulos2
 * @date Oct 26, 2017
 *
 * @brief ITCS 3112 Project 4 part 2
 *
 * @section DESCRIPTION
 *
 * Image class implementation. All functions are defined in
 * the header file.
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include "image.h"

using namespace std;

/** Constant variable defining the PPM standard */
const string PPM_TYPE = "P3";

/**
 *
 * Default constructor for an Image object
 *
 */
Image::Image() {
    width = 0;
    height = 0;
}

/**
 *
 * Constructor used when a ppm input file is given.
 * This calls the read function which creates an image
 * object by reading in the input file.
 *
 * @param input_file String with the name of the input file
 */
Image::Image(string input_file) {
    read(input_file);
}

/**
 *
 * Constructor for an empty image object with given
 * height and width.
 *
 * @param width Width of the image object
 * @param height Height of the image object
 *
 */
Image::Image(int width, int height) {
    setWidth(width);
    setHeight(height);

    //Allocate the array given the dimensions
    image_array = new int* [height];

    for (int i = 0; i < width; i++){
        image_array[i] = new int[width*3];
    }
}

/**
 *
 * Destructor for the image object.
 * Checks to make sure that the 2d array has been allocated.
 * If it has been allocated then it is freed from memory.
 *
 */
Image::~Image() {

    if (!(image_array == NULL)) {
        //Delete each row
        for (int i = 0; i < height; i++){
            delete [] image_array[i];
        }
        //Delete outer array
        delete [] image_array;
    }
}

/**
 *
 * Returns the width of the Image object.
 *
 * @param none
 * @return width The width of the Image object
 *
 */
int Image::getWidth(){
    return width;
}

/**
 *
 * Sets the width of the Image object.
 *
 * @param w Width of the object that you would like to set
 * @return none
 *
 */
void Image::setWidth(int w) {
    width = w;
}

/**
 *
 * Returns the height of the Image object.
 *
 * @param none
 * @return height The height of the Image object
 *
 */
int Image::getHeight(){
    return height;
}

/**
 *
 * Sets the height of the Image object.
 *
 * @param h Height of the object that you would like to set
 * @return none
 *
 */
void Image::setHeight(int h) {
    height = h;
}

/**
 *
 * Returns the max pixe value of the Image object.
 *
 * @param none
 * @return maxPixel The max pixel value of the Image object
 *
 */
int Image::getMaxPixel(){
    return maxPixel;
}

/**
 *
 * Sets the max pixel value of the Image object.
 *
 * @param m Max pixel value of image
 * @return none
 *
 */
void Image::setMaxPixel(int m) {
    maxPixel = m;
}

/**
 *
 * Function that returns the RGB pixel value
 * at a given point.
 *
 * @param col Column of the pixel you want
 * @param row Row of the pixel you want
 * @param *pixel Pointer to a 3 element array that holds the RGB triple
 * @return none
 */
void Image::getImagePixel(int col, int row, int *pixel) {
    col *= 3;
    pixel[0] = image_array[row][col];
    pixel[1] = image_array[row][col + 1];
    pixel[2] = image_array[row][col + 2];
}

/**
 *
 * Function that sets the RGB pixel value
 * at a given point.
 *
 * @param col Column of the pixel you want
 * @param row Row of the pixel you want
 * @param *pixel Pointer to a 3 element array that holds the RGB triple
 * @return none
 */
void Image::setImagePixel(int col, int row, int *pixel) {
    col *= 3;
    image_array[row][col] = pixel[0];
    image_array[row][col + 1] = pixel[1];
    image_array[row][col + 2] = pixel[2];

}

/**
 *
 * This function reads the ppm image given by the infile parameter.
 * It reads the ppm image into a dynamically allocted 2d array called image_array.
 *
 * @param infile String with the name of the input file
 * @return none
 */
void Image::read(string infile) {
    //Open our file for reading
    FILE *dataset = fopen(infile.c_str(), "r");
    //Skip the ppm format since we know it
    fscanf(dataset, "%*s");
    //Read in the height, width, and max pixel
    int tempH = 0, tempW = 0, tempM = 0;
    fscanf(dataset, "%d%d%d", &tempW, &tempH, &tempM);
    //Set those values in the image object.
    width = tempW;
    height = tempH;
    maxPixel = tempM;

    //Create an array to store the entire ppm file
    image_array = new int* [height];

    for (int i = 0; i < height; i++){
        image_array[i] = new int[width*3];
    }

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width*3; j++){
            fscanf(dataset, "%d ", &image_array[i][j]);
        }
    }

    fclose(dataset);

}

/**
 *
 * This function writes the current object out to a given file.
 * If the filename can be given with our without an extension.
 * The function will remove any file extensions and force the
 * output file to be .ppm
 *
 * @param outfile String with the name of the output file
 * @return none
 */
void Image::write(string outfile) {
    size_t lastindex = outfile.find_first_of(".");
    string outname = outfile.substr(0, lastindex);

    outname = outname + ".ppm";
    FILE *output_file = fopen(outname.c_str() , "w");

    //Print the PPM header
    fprintf(output_file, "%s\n", PPM_TYPE.c_str());
    //Print the width and height
    fprintf(output_file, "%i %i\n", width, height);

    if (maxPixel > 255){
        maxPixel = maxPixel / 255;
    }
    fprintf(output_file, "%i\n", maxPixel);
    //Print the array to the ppm file
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width*3; j++){
            fprintf(output_file, "%d ", image_array[i][j]);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);

}

/**
 *
 * This function converts the image to grayscale using the
 * formula R*0.299+G*0.587+B*0.114.
 *
 * @param none
 * @return none
 */
void Image::toGrayscale() {
    int pixel[3];
    int oldPixel[3];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            getImagePixel(j, i, oldPixel);
            int val = (oldPixel[0] * 0.299) + (oldPixel[1] * 0.587) + (oldPixel[2] * 0.114);
            pixel[0] = val;
            pixel[1] = val;
            pixel[2] = val;
            setImagePixel(j, i, pixel);
        }
    }
}

/**
 *
 * This funciton flips the image horizontally.
 *
 * @param none
 * @return none
 */
void Image::flipHorizontal() {

    int **temp_array;
    //Allocate the array given the dimensions
    temp_array = new int* [height];

    for (int i = 0; i < width; i++){
        temp_array[i] = new int[width*3];
    }

    int pixel[3];
    int count = (width * 3) - 1;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            getImagePixel(j, i, pixel);
            //cout << pixel[0] << " " << pixel[1] << " " << pixel[2] << endl;
            //cout << count << endl;
            temp_array[i][count - 2] = pixel[0];
            temp_array[i][count - 1] = pixel[1];
            temp_array[i][count] = pixel[2];
            count -= 3;
            if (count < 2) {
                count = (width * 3) - 1;
            }
        }
    }

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width * 3; j++){
            image_array[i][j] = temp_array[i][j];
        }
    }

    if (!(temp_array == NULL)) {
        //Delete each row
        for (int i = 0; i < height; i++){
            delete [] temp_array[i];
        }
        //Delete outer array
        delete [] temp_array;
    }
}

/**
 *
 * This function flips each blue pixel in the image about the
 * max pixel value.
 * ex. Assume the max pixel value is 255
 * If the blue were 0, it would become 255; 
 * if it were 255 it would become 0. 
 * If the blue were 100, it would become 155.
 *
 * @param none
 * @return none
 */
void Image::negateBlue() {
    int pixel[3];
    int oldPixel[3];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            getImagePixel(j, i, oldPixel);
            pixel[0] = oldPixel[0];
            pixel[1] = oldPixel[1];
            pixel[2] = abs(oldPixel[2] - maxPixel);
            setImagePixel(j, i, pixel);
        }
    }
}

/**
 *
 * This funciton sets all the red pixel values to 0.
 *
 * @param none
 * @return none
 */
void Image::flattenRed() {
    int pixel[3];
    int oldPixel[3];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            getImagePixel(j, i, oldPixel);
            pixel[0] = 0;
            pixel[1] = oldPixel[1];
            pixel[2] = oldPixel[2];
            setImagePixel(j, i, pixel);
        }
    }
}
