07_HeapLab
==============

Implement a heap in C++

Requirements
------------

1. `add` and `remove` should be O(log n), except for `grow` which can be O(n)
2. Do not leak memory

Reading
=======
"Open Data Structures," Chapter 10, just the intro and section 1. http://opendatastructures.org/ods-cpp/10_Heaps.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. Add works and is O(log n) because bubbleUp is called recursively with a max amount of times of being called log n. Remove almost works, but there is a problem with deleting the values that are removed.  It still runs O(log n) time because trickleDown is called a max of log n times.
2. No memory is leaked.  Any arrays and their contents are destroyed in destructors or with delete statements when they are no longer needed.

#### 2. Exercises 10.1 and 10.2 from http://opendatastructures.org/ods-cpp/10_3_Discussion_Exercises.html

10.1 - If a value of 7 is added, the add() method initially adds it to the end of backingArray, growing the array if necessary.  bubbleUp() then checks it’s parent recursively until the priorities are in the right order.  The value of 3 is then added in the same way to the Heap.

10.2 - The first priority, or top of the tree, is always removed.  If six was removed, it would first be swapped with the value of 55.  The six value would be deleted from the tree, and then trickleDown would recursively compare 55 with it’s children and swap along the way until it is in the correct, farthest left open spot on the Heap.  The value of 8 would now be at the top of the tree as 55 initially swapped with its right child, 8.  8 would be removed in the same manner, this time swapping with 93.  

#### 3. Exercise 10.4 from http://opendatastructures.org/ods-cpp/10_3_Discussion_Exercises.html
Start with index 0.  There is no parent, but it’s children split into the 1st and 2nd spot of the array.  The 1st and 2nd have children that split into the 3-4 and 5-6 indexes respectively.  The children’s indexes can be reached from the parent index by multiplying by 2 and adding a constant, and just by trial and error, we see that a parent index i has children of (2*i + 1) and (2*i + 2). These equations can be used to go the opposite direction, subtracting 1 and dividing 2 will again find the parent index i, so the equation for a parent index is from a child index j is ((j-1)/2).  Computer arithmetic with integers make sure that both children will point to the same int parent index.

#### 4. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

In the exercises, why do the values not appear to be in breadth first order?  It seems to be completely random, which is not what I thought would happen