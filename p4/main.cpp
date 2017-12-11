#include <iostream>
#include <string>
#include "image.h"


using namespace std;

/**
 *
 * Main function for driver program. Does some simple
 * tests with a few different image objects.
 *
 * @param none
 * @return none
 *
 */
int main() {

    //Test constructor that accepts file input.

    //Read in yosemite image
    Image myImage("yosemite.ppm");
    int pixel[3] = {myImage.getMaxPixel(),0, 0};
    int start = (myImage.getHeight() / 2) - 10;
    for (int j = start; j < start + 20; j++){
        for (int i = 0; i < myImage.getWidth(); i++){
            myImage.setImagePixel(i, j, pixel);
        }
    }
    myImage.write("yosemite_OUTPUT");


    //Read in test2 image
    Image myImage2("test2.ppm");
    int pixel2[3] = {myImage2.getMaxPixel(), 0, 0};
    for (int i = 0; i < myImage2.getWidth(); i++){
        myImage2.setImagePixel(i, 4, pixel2);
    }
    myImage2.write("test2_OUTPUT");


    //Test constructor that accepts height and width
    Image myImage3(100,200);
    cout << "Image3 Width: " << myImage3.getWidth() << endl;
    cout << "Image3 Height: " << myImage3.getHeight() << endl;

    //Test default constructor
    Image myImage4;
    myImage4.setWidth(50);
    cout << "Image4 Width: " << myImage4.getWidth() << endl;


    return 0;
}
