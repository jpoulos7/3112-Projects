/**
 *
 * @file set.h
 * @author John Poulos, jpoulos2
 * @date Nov 9, 2017
 *
 * @brief ITCS 3112 Project 5
 *
 * @section DESCRIPTION
 *
 * Set header file containing all the function definitions.
 *
 */

#ifndef SET_H
#define SET_H
#include <iostream>
#include <vector>

template<typename T>
class Set {
    private:

    //Total capacity of the set
    int capacity;
    //Actual used space
    int used;
    //Pointer to store all the data
    T *set_data;
    //Pointer to store the frequency of each item in the set
    int *item_counts;
    int currentLocation;

    public:

    //Constructors & Destructor
    Set();
    Set(int cap);
    ~Set();

    //Getters and Setters
    int getCapacity();
    void setCapacity(int w);
    int getSize();
    T getData(int loc);
    int getFreq(int loc);

    //Checks if an item exists in the set
    bool contains(T target);
    //Adds a new item to the set
    void addElement(T item);
    //Returns the index of an item in the set
    int findItem(T item);

};

#include "set.cpp"
#endif //SET_H
