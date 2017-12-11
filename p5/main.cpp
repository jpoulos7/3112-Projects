/**
 *
 * @file main.cpp
 * @author John Poulos, jpoulos2
 * @date Nov 9, 2017
 *
 * @brief ITCS 3112 Project 5
 *
 * @section DESCRIPTION
 *
 * Main driver used to test the functionality of the set.
 *
 */

#include <iostream>
#include "set.h"
#include "pixelItem.h"
#include "image.h"


using namespace std;

/**
 *
 * Main function used to test the program. 
 * Each image is turned into a set. The rgb
 * data is exported and then plotted using an outside script.
 * Each image is then written out, but each pixel occuring more than 
 * the threshold number of times is turned white.
 *
 */
int main() {

    Image* myImage = new Image("test1.ppm");
    myImage->makeSet();
    myImage->commonPixels(30);
    myImage->write("test1-OUTPUT.ppm");
    delete myImage;


    Image* myImage1 = new Image("test2.ppm");
    myImage1->makeSet();
    myImage1->commonPixels(25);
    myImage1->write("test2-OUTPUT.ppm");
    delete myImage1;


    Image* myImage2 = new Image("landscape1.ppm");
    myImage2->makeSet();
    myImage2->commonPixels(1000);
    myImage2->write("landscape1-OUTPUT.ppm");
    delete myImage2;


    Image* myImage3 = new Image("landscape2.ppm");
    myImage3->makeSet();
    myImage3->commonPixels(50);
    myImage3->write("landscape2-OUTPUT.ppm");
    delete myImage3;

    Image* myImage4 = new Image("yosemite.ppm");
    myImage4->makeSet();
    myImage4->commonPixels(500);
    myImage4->write("yosemite-OUTPUT.ppm");
    delete myImage4;


    return 0;

}
