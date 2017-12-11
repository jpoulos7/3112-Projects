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

    //Test grayscale
    Image* myImage = new Image("yosemite.ppm");
    myImage->toGrayscale();
    myImage->write("YOSEMITE_GRAYSCALE");
    delete myImage;

    //Test negate blue
    Image* myImage3 = new Image("yosemite.ppm");
    myImage3->negateBlue();
    myImage3->write("YOSEMITE_NEG_BLUE");
    delete myImage3;

    //Test flatten red
    Image* myImage4 = new Image("yosemite.ppm");
    myImage4->flattenRed();
    myImage4->write("YOSEMITE_FLAT_RED");
    delete myImage4;

    //Test flip horizontal
        Image* myImage2 = new Image("yosemite.ppm");
        myImage2->flipHorizontal();
        myImage2->write("YOSEMITE_FLIPPED");
        delete myImage2;

    return 0;
}
