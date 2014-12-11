/* 
 * This is a priority queue, which means that as items are removed in order
 * of decreasing priority.
 *
 * Author 2: Scott McCartney
 * Date 2: 2014/12/10
 * All code was written by me for CSE274.
 */
#include "Queue.h"
#include <utility>

//This should be the initial arrSize
#define START_SIZE 10


template<class Pri, class T>
class Heap : public Queue<std::pair<Pri, T> > {
public:
    Heap();
    ~Heap();
    
    //Add a new item
    virtual void add(std::pair<Pri,T> toAdd);
    
    //Remove the item with lowest priority, and return it
    //If the queue is empty, throw a string exception
    virtual std::pair<Pri,T> remove();
    
    //Return the number of items currently in the queue
    virtual unsigned long getNumItems();
    
private:
    int arrSize;
    int numItems;
    std::pair<Pri, T>* backingArray;
    
    //Grow the backingArray by making a new array of twice the size,
    // and copying over the data
    void grow();
    
    //Check the item at index, and make sure it is in the right place.
    // If not, swap it up the "tree" of the heap until you find the right
    // place
    void bubbleUp(unsigned long index);
    
    //Check the item at index, and make sure it is in the right place.
    // If not, swap it down the "tree" of the heap until you find the right
    // place
    void trickleDown(unsigned long index);
};

/***********************
 * Originally Heap.ipp *
 **********************/
//Used http://www.cplusplus.com/reference/utility/pair/ as a reference for the
//pair class
#include <string>

template<class Pri, class T>
Heap<Pri,T>::Heap(){
    numItems = 0;
    arrSize = START_SIZE;
    
    //Creates a pointer variable of type pair<Pri, T>
	backingArray = new std::pair<Pri,T>[arrSize];
}

template<class Pri, class T>
Heap<Pri,T>::~Heap(){
    //No memory leak by deleting backingArray
    delete[] backingArray;
}

template<class Pri, class T>
void Heap<Pri,T>::grow(){
    arrSize = arrSize*2;
    std::pair<Pri, T>* tempArray = backingArray;
    backingArray = new std::pair<Pri, T>[arrSize];
    
	int currentItems = numItems;
    for(int i=0; i < currentItems; i++) {
        add(tempArray[i]);
    }
    
    delete[] tempArray;
}

template<class Pri, class T>
void Heap<Pri,T>::add(std::pair<Pri,T> toAdd){
    if(numItems == arrSize) {
        grow();
    }
    
    backingArray[numItems] = toAdd;
    bubbleUp(numItems);
    numItems++;
}

template<class Pri, class T>
void Heap<Pri,T>::bubbleUp(unsigned long index){
    //Base case since the first index has no parent
    if(index <= 0) {
        return;
    }
    int parent = (index-1)/2;
    
    if(backingArray[parent].first > backingArray[index].first) {
        backingArray[parent].swap(backingArray[index]);
        bubbleUp(parent);
    }
}

template<class Pri, class T>
void Heap<Pri,T>::trickleDown(unsigned long index){
    std::pair<Pri, T> tempPair;
    int leftIndex = (2*index)+1;
    int rightIndex = (2*index)+2;
	
    if(rightIndex == numItems) {
        backingArray[rightIndex].swap(backingArray[index]);
        if(rightIndex < numItems - 1) {
            trickleDown(rightIndex);
        }
    }
    else if(backingArray[leftIndex].first > backingArray[index].first) {
        
        backingArray[leftIndex].swap(backingArray[index]);
        if(leftIndex < numItems - 1) {
            trickleDown(leftIndex);
        }
    }
}

template<class Pri, class T>
std::pair<Pri,T> Heap<Pri,T>::remove(){
    if(numItems == 0) {
        throw std::string("In remove(), tried to remove from an empty array.");
    }
    else {
        //Swaps the first and last pairs, remove the last item
        //and return it at the end of remove()
		std::pair<Pri,T> removedPair = backingArray[0];
        backingArray[0].swap(backingArray[numItems-1]);
        
        numItems--;
        //Trickle down from the first index
        trickleDown(0);
        return removedPair;
    }
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::getNumItems(){
    return numItems;
}
