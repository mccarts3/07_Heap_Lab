#include "Queue.h"
#include <utility>

//This should be the initial arrSize
#define START_SIZE 10

/*
 * This is a priority queue, which means that as items are removed in order
 * of decreasing priority.
 *
 *
 */
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
    
    //Used in the destructor to delete all the elements of the heap
    void removeAll();
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
    //No memory leak by deleting all elements and then backingArray
    removeAll();
    delete[] backingArray;
}


template<class Pri, class T>
void Heap<Pri,T>::removeAll() {
    while(numItems > 0) {
        std::pair<Pri,T> temp = remove();
    }
}

template<class Pri, class T>
void Heap<Pri,T>::grow(){
    arrSize = arrSize*2;
    std::pair<Pri, T>* tempArray = backingArray;
    backingArray = new std::pair<Pri, T>[arrSize];
    
    for(int i=0; i < numItems; i++) {
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
        std::pair<Pri,T> tempPair = swap(parent, index);
        bubbleUp(parent);
    }
}

template<class Pri, class T>
void Heap<Pri,T>::trickleDown(unsigned long index){
    //recursive?
}

template<class Pri, class T>
std::pair<Pri,T> Heap<Pri,T>::remove(){
    if(numItems == 0) {
        throw std::string("In remove(), tried to remove from an empty array.");
    }
    else {
        //Swaps the first and last pairs, remove the last item
        //and return it at the end of remove()
        std::pair<Pri,T> removedPair = swap(0, numItems-1);
        
        //make the last index a null pair
        backingArray[numItems-1] = NULL;
        
        //Trickle down from the first index
        trickleDown(0);
        numItems--;
        return removedPair;
    }
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::getNumItems(){
    return numItems;
}
