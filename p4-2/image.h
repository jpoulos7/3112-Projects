/**
 *
 * @file image.h
 * @author John Poulos, jpoulos2
 * @date Oct 26, 2017
 *
 * @brief ITCS 3112 Project 4 part 2
 *
 * @section DESCRIPTION
 *
 * Image header file containing all the function definitions.
 *
 */


#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Image {

private:

    //Image Dimensions
    int width, height;
    //Max pixel value
    int maxPixel;
    //Pointer to dynamic image array
    int **image_array;

public:

    //Default constructor
    Image();
    //Creates image object by reading input file
    Image(string input_file);
    //Create image object using the given dimensions
    Image(int width, int height);
    //Destructor for image object
    ~Image();

    //Accessors and mutators
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    int getMaxPixel();
    void setMaxPixel(int m);

    //Get and set image pixel given a row and column
    void getImagePixel(int col, int row, int *pixel);
    void setImagePixel(int col, int row, int *pixel);

    //Read image from infile
    void read(string infile);
    //Write image to outfile
    void write(string outfile);

    //Convert to grayscale
    void toGrayscale();
    //Flips the image horizontally
    void flipHorizontal();
    //Flips the blue around 255
    void negateBlue();
    //Sets all red pixels to zero
    void flattenRed();


};

#endif
