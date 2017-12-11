/**
 *
 * @file pixelItem.cpp
 * @author John Poulos, jpoulos2
 * @date Nov 9, 2017
 *
 * @brief ITCS 3112 Project 5
 *
 * @section DESCRIPTION
 *
 * Implementation of PixelItem.
 *
 */

#include <iostream>
#include "pixelItem.h"

/**
 *
 * Constructor for an empty PixelItem.
 *
 */
PixelItem::PixelItem(){
    ch[0] = ch[1] = ch[2] = 0;
}

/**
 *
 * Constructor for a PixelItem with known values.
 *
 */
PixelItem::PixelItem(int r, int g, int b){
     ch[0] = r; ch[1] = g; ch[2] = b;
}

/**
 *
 * Sets the rgb values of a PixelItem.
 *
 * @param r Integer containing the red value
 * @param g Integer containing the green value
 * @param b Integer containing the blue value
 * @return none
 *
 */
void PixelItem::setPixel(int r, int g, int b){
    ch[0] = r; ch[1] = g; ch[2] = b;
}

/**
 *
 * Returns the red value of the PixelItem.
 *
 * @param none
 * @return Red value of the PixelItem.
 *
 */
int PixelItem::getRed(){
    return ch[0];
}

/**
 *
 * Returns the green value of the PixelItem.
 *
 * @param none
 * @return Green value of the PixelItem.
 *
 */
int PixelItem::getGreen(){
    return ch[1];
}

/**
 *
 * Returns the blue value of the PixelItem.
 *
 * @param none
 * @return Green value of the PixelItem.
 *
 */
int PixelItem::getBlue(){
    return ch[2];
}

/**
 *
 * Operator overload to compare 2 PixelItem objects.
 *
 * @param Second PixelItem to be compared
 * @return true if the objects are equal
 * @return false if the objects are not equal
 *
 */
bool PixelItem::operator==(PixelItem& item){
    if (this->ch[0] == item.ch[0] && this->ch[1] == item.ch[1] && this->ch[2] == item.ch[2]){
        return true;
    } else {
        return false;
    }
}

