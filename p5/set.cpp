/**
 *
 * @file set.cpp
 * @author John Poulos, jpoulos2
 * @date Nov 9, 2017
 *
 * @brief ITCS 3112 Project 5
 *
 * @section DESCRIPTION
 *
 * Implementation of Set.
 *
 */

#include "set.h"
#include <iostream>
#include <algorithm>

/**
 *
 * Destructor for a set. Frees the necessary memory.
 *
 */
template<class T>
Set<T>::~Set(){
    //delete [] set_data;
    //delete [] item_counts;
}

/**
 *
 * Default constructor. Initializes the set to default values.
 *
 */
template<class T>
Set<T>::Set(){
    used = 0;
    capacity = 20000000;
    set_data = new T[capacity];
    item_counts = new int[capacity];
}

/**
 *
 * Constructor for a set that accepts an initial capacity.
 *
 * @param cap capacity you wish to initialize the set with
 */
template<class T>
Set<T>::Set(int cap){
    used = 0;
    capacity = cap;
    set_data = new T[capacity];
    item_counts = new int[capacity];
}

/**
 *
 * This function returns the total capacity of the set.
 *
 * @param none
 * @return the total capacity of the set
 *
 */
template<class T>
int Set<T>::getCapacity(){
    return capacity;
}

/**
 *
 * This function sets the total capacity of the set.
 *
 * @param w total capacity of the set
 * @return none
 *
 */
template<class T>
void Set<T>::setCapacity(int w){
    capacity = w;
}

/**
 *
 * This function returns the current amount of space
 * in use by the set.
 *
 * @param none
 * @return current size in use by the set
 *
 */
template<class T>
int Set<T>::getSize(){
    return used;
}

/**
 *
 * This function returns the data at a specific location 
 * in the set. 
 *
 * @param loc Location you wish to get the data at
 * @return The data at that particular location in the set
 *
 */
template<class T>
T Set<T>::getData(int loc){
    return set_data[loc];
}

/**
 *
 * This function returns the item_counts at a
 * specific location.
 *
 * @param loc Location you wish to get the frequency for
 * @return frequency of the item at the location you requested
 *
 */
template<class T>
int Set<T>::getFreq(int loc){
    return item_counts[loc];
}

/**
 *
 * Function to test if an element already exists in the set.
 *
 * @param target Element to check
 * @return true if the element already exists
 * @return false if the element does not exist in the set
 *
 */
template<class T>
bool Set<T>::contains(T target){

    if (findItem(target) == -1) {
        return false;
    } else {
        return true;
    }

}

/**
 *
 * This function adds an element to the set. Before adding
 * the element it checks to see if it already exists. If it does
 * exist then the item_count for that element is updated. If it
 * does not yet exist then the element is added and the item_count
 * for that element is initialized.
 *
 * @param item Element to be added to the set
 * @return none
 *
 */
template<class T>
void Set<T>::addElement(T item){
    //std::cout << "Used: " << used << " Capacity: " << getCapacity() << std::endl;
    if (!this->contains(item)) {
        // Does not contain
        //put it in the array at the next open space
        set_data[used] = item;
        //set the item count 0 at that same space
        item_counts[used] = 1;
        //Increase used size
        used++;
    } else {
        // Already in set
        item_counts[currentLocation]++;
    }
}

/**
 *
 * This function finds the location of an item in the set.
 *
 * @param item Item to find in the set
 * @return index of the item in the set
 *
 */
template<class T>
int Set<T>::findItem(T item){
    for (int i = 0; i < used; i++){
        if(set_data[i] == item) {
            //set contains target
            //return the location of it
            currentLocation = i;
            return i;
        }
    }
    return -1;
}
