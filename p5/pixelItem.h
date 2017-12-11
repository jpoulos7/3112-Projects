/**
 *
 * @file pixelItem.h
 * @author John Poulos, jpoulos2
 * @date Nov 9, 2017
 *
 * @brief ITCS 3112 Project 5
 *
 * @section DESCRIPTION
 *
 * Header file for a PixelItem definitions.
 *
 */

#ifndef PIXELITEM_H
#define PIXELITEM_H
#include <iostream>

class PixelItem {
    private:

    //Character array to hold the pixel values
    int ch[3];

    public:

    //Constructors
    PixelItem();
    PixelItem(int r, int g, int b);

    //Sets the rgb value of a pixel item
    void setPixel(int r, int g, int b);

    //Getters
    int getRed();
    int getGreen();
    int getBlue();

    //Overload to compare 2 pixelItems 
    bool operator==(PixelItem& item);

};

#endif //PIXELITEM_H
