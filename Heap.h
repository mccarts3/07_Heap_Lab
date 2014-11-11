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
#include <string>

template<class Pri, class T>
Heap<Pri,T>::Heap(){
    numItems = 0;
    arrSize = START_SIZE;
    
    //Creates a pointer variable of type pair<Pri, T>
	backingArray = new pair<Pri, T>[arrSize];
}

template<class Pri, class T>
Heap<Pri,T>::~Heap(){
    //No memory leak by deleting all elements and then backingArray
    removeAll();
    delete backingArray;
}


template<class Pri, class T>
Heap<Pri,T>::removeAll() {
    while(numItems > 0) {
        //remove() returns something, do i need to take care of it?
        remove();
    }
}

template<class Pri, class T>
void Heap<Pri,T>::grow(){
    arrSize = arrSize*2;
    pair<Pri, T>* tempArray = new pair<Pri, T>[arrSize];
    
    for(int i=0; i < numItems; i++) {
        tempArray[i] = backingArray[i];
    }
    
    backingArray = tempArray;
    delete tempArray;
}

template<class Pri, class T>
void Heap<Pri,T>::add(std::pair<Pri,T> toAdd){
    if(numItems == arrSize) {
        grow();
    }
    
    backingArray[numItem] = toAdd;
    numItems++;
    bubbleUp(numItems-1);
}

//COPIED FROM ABOVE - Check the item at index, and make
// sure it is in the right place.  If not, swap it up the
//"tree" of the heap until you find the right place
template<class Pri, class T>
void Heap<Pri,T>::bubbleUp(unsigned long index){
    //recursive?
}

//COPIED FROM ABOVE - Check the item at index, and make
// sure it is in the right place.  If not, swap it down
// the "tree" of the heap until you find the right place
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
        //swap the first and the last, then remove the last
        std::pair<Pri,T> tmp;
        
        numItems--;
        return tmp;
    }
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::getNumItems(){
    return numItems;
}
