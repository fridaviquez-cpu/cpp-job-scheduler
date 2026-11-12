#ifndef PQTYPE_H
#define PQTYPE_H
// Definition of class PQType, which represents the Priority Queue ADT
class FullPQ{};
class EmptyPQ{};
#include <iostream>
#include <string>
#include <cmath>
//#include <format>
#include "Heap.h"
using namespace std;
#define MAX_ITEMS 10
template<class ItemType>
class PQType
{
public:
  PQType();				//default constructor
  PQType(int);          // parameterized class constructor
  ~PQType();            // class destructor
  PQType(ItemType elements[]);
  
  PQType operator=(const PQType& rhs);

  void MakeEmpty();
  // Function: Initializes the queue to an empty state.
  // Post: Queue is empty.
  
  bool IsEmpty() const;
  // Function: Determines whether the queue is empty.
  // Post: Function value = (queue is empty)
  
  bool IsFull() const;
  // Function: Determines whether the queue is full.
  // Post: Function value = (queue is full)
  
  void Enqueue(ItemType newItem);
  // Function: Adds newItem to the rear of the queue.
  // Post: if (the priority queue is full) exception FullPQ is thrown;
  //       else newItem is in the queue.
  
  void Dequeue(ItemType& item);
  // Function: Removes element with highest priority from the queue
  // and returns it in item.
  // Post: If (the priority queue is empty) exception EmptyPQ is thrown;
  //       else highest priority element has been removed from queue.
  //       item is a copy of removed element.

  //Recursive Print of the Heap as a Tree: IT 4/8/2020
  void toString() const;
  void toStringRec(ItemType* elems, int level) const;

  //IT 4/5/2022, Find an item in the PQ
  bool FindSequential(ItemType item);

  bool FindBinary(ItemType item);

  bool FindPQ_Heap(ItemType item);
  void FindPQ_Heap_Rec(ItemType item, int index, bool& found);

  template <class ItemPQ>
  friend ostream& operator<<(ostream& out, const PQType<ItemPQ>& pq);

  //IT 4/5/2023, Find an item in the PQ using a sequential search
  bool Find(ItemType item);
  bool FindSorted(ItemType item);
  ItemType* Sort();

  PQType(PQType& rhs);


private:
  int length;
  HeapType<ItemType> items;
  int maxItems;
};

//A recursive binary search function.
//Pre-condition: arr is sorted in ascending order.
//Post-condition: returns true if x in given
//                array arr[l..r] is present,
//                otherwise false
template <class ItemType>
bool binarySearch(ItemType* arr, int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return true;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
    return false;
}


//Sort the items array that stored the original heap.
//Pre-condition: the heap exists.
//Post-condition: sorts the items of the heap in ascending order
template <class ItemType>
ItemType* PQType<ItemType>::Sort(){
	ItemType* sorted_items = items.HeapSort(length);
	return sorted_items;
}

//Find item in the heap using a sequential search.
//Pre-condition: the heap (items) is not empty.
//Post-condition: returns true if x in given
//                array items.elements[l..r] is present,
//                otherwise false
template <class ItemType>
bool PQType<ItemType>::Find(ItemType item){
	//sequential search for item
	//Time complexity: O(n)
	for(int i = 0; i < length; i++){
		if(items.elements[i] == item){
			return true;
		}
	}
	return false;
}

//Pre-condition: the heap (items) is not empty.
//Post-condition: returns true if x in given
//                array items.elements[l..r] is present,
//                otherwise false; use the binary search
template <class ItemType>
bool PQType<ItemType>::FindSorted(ItemType item){
	//sequential search for item
	//Time complexity: O(log n)
	return binarySearch(items.elements, 0, length, item);
}



//Author: Ivan Temesvari
//Date: 4/6/2022
//Pre-condition: the PQType is a min/max heap and is not empty.
//Post-condition: the PQType items is unchanged; if the item is found,
//				  return true; if it is not found, return false.
//Analysis: The complexity of the Find function is O(n + nlogn + n) using
//          sequential search, and O(n + nlogn + logn) using binarySearch.
template <class ItemType>
bool PQType<ItemType>::FindSequential(ItemType item){
	//Copy items.elements to a temp.
	HeapType<ItemType> temp;
	temp.elements = new ItemType[maxItems];
	//O(n) copy overhead
	for(int i = 0; i < length; i++){
		temp.elements[i] = items.elements[i];
	}
	//O(n*log(n)) for the sort
	temp.HeapSort(length);
	//O(n) for the sequential search.
	for(int i = 0; i < length; i++){
		if(item == temp.elements[i]){
			return true;
		}
	}
	return false;
}

//Author: Ivan Temesvari
//Date: 4/6/2022
//Pre-condition: the PQType is a min/max heap and is not empty.
//Post-condition: the PQType items is unchanged; if the item is found,
//				  return true; if it is not found, return false.
//Analysis: The complexity of the Find function is O(n + nlogn + n) using
//          sequential search, and O(n + nlogn + logn) using binarySearch.
template <class ItemType>
bool PQType<ItemType>::FindBinary(ItemType item){
	//Copy items.elements to a temp.
	HeapType<ItemType> temp;
	temp.elements = new ItemType[maxItems];
	//O(n) copy overhead
	for(int i = 0; i < length; i++){
		temp.elements[i] = items.elements[i];
	}
	//O(n*log(n)) for the sort
	temp.HeapSort(length);
	//O(logn) for the binary search.
	return binarySearch(temp.elements, 0, length-1, item);
}

//Author: Ivan Temesvari
//Date: 4/6/2022
//Pre-condition: the PQType is a min/max heap and is not empty.
//Post-condition: the PQType items is unchanged; if the item is found,
//				  return true; if it is not found, return false.
//Analysis: The complexity of the Find function is O(n + nlogn + n) using
//          sequential search, and O(n + nlogn + logn) using binarySearch,
//          and using a dynamic programming approach is O(???)
template <class ItemType>
bool PQType<ItemType>::FindPQ_Heap(ItemType item){
	bool found = false;
	FindPQ_Heap_Rec(item, 0, found);
	return found;
}

template <class ItemType>
void PQType<ItemType>::FindPQ_Heap_Rec(ItemType item, int index, bool& found){
	if(index <= length and !found){
		if(items.elements[index] == item){
			found = true;
			return;
		}
		else{
			if(2*index+2 <= length){  //check left and right
				if(item == items.elements[2*index+1] or item == items.elements[2*index+2]){
					found = true;
					return;
				}
				else if(item > items.elements[2*index+1]
						and item > items.elements[2*index+2]){ //don't look left nor right
					found = false;
				}
				else if(item > items.elements[2*index+1]){  //don't look left
					FindPQ_Heap_Rec(item, 2*index+2, found);  //recurse right
				}
				else{  //recurse left...right
					FindPQ_Heap_Rec(item, 2*index+1, found);
					FindPQ_Heap_Rec(item, 2*index+2, found);
				}
			}
			else if(2*index+1 <= length){  //check only left
				if(item == items.elements[2*index+1]){
					found = true;
					return;
				}
				else if(item > items.elements[2*index+1]){ //don't look left anymore
					FindPQ_Heap_Rec(item, 2*index+2, found);  //recurse right
				}
				else{  //recurse left...right
					FindPQ_Heap_Rec(item, 2*index+1, found);
					FindPQ_Heap_Rec(item, 2*index+2, found);
				}
			}
			return;
		}
	}
	return;
}

template<class ItemType>
PQType<ItemType>::PQType(ItemType elements[]){
	length = sizeof(elements);
	maxItems = length;
	items.elements = new ItemType[length];
	for(int i = 0; i < length; i++){
		items.elements[i] = elements[i];
	}
	items.Heapify(length);
}


template<class ItemType>
PQType<ItemType>::PQType(){
	maxItems = MAX_ITEMS;
	items.elements = new ItemType[maxItems];
	length = 0;
}

template<class ItemType>
PQType<ItemType>::PQType(PQType& rhs){
	length = 0;
	maxItems = rhs.maxItems;
	items.elements = new ItemType[rhs.maxItems];

	//copy new contents over to this from rhs
	int count = 0;
	while(count < rhs.length){
		items.elements[count] = rhs.items.elements[count];
		count++;
	}
}

template<class ItemType>
PQType<ItemType>::PQType(int max)
{
  maxItems = max;
  items.elements = new ItemType[maxItems];
  length = 0;
}

template<class ItemType>
PQType<ItemType> PQType<ItemType>::operator=(const PQType<ItemType>& rhs){
	//assignment operator=
	if(this == &rhs){
		return *this;
	}
	else{
		//delete old contents of this
		delete [] items.elements;
		length = 0;
		maxItems = rhs.maxItems;
		items.elements = new ItemType[rhs.maxItems];

		//copy new contents over to this from rhs
		int count = 0;
		while(count < rhs.length){
			items.elements[count] = rhs.items.elements[count];
			count++;
		}
	}
	return *this;
}

template<class ItemType>
void PQType<ItemType>::MakeEmpty()
{
  length = 0;
}

template<class ItemType>
PQType<ItemType>::~PQType()
{
  delete [] items.elements;
}
template<class ItemType>
void PQType<ItemType>::Dequeue(ItemType& item)
// Post: element with highest priority has been removed 
//       from the queue; a copy is returned in item.
{
  if (length == 0)
    throw EmptyPQ();
  else
  {
    item = items.elements[0];
    items.elements[0] = items.elements[length-1];
    length--;
    items.ReheapDown(0, length-1);
  }
}

template<class ItemType>
void PQType<ItemType>::Enqueue(ItemType newItem)
// Post: newItem is in the queue.
{
  if (length == maxItems)
    throw FullPQ();
  else
  {
    length++;
    items.elements[length-1] = newItem;
    items.ReheapUp(0, length-1);
  }
}
template<class ItemType>
bool PQType<ItemType>::IsFull() const
// Post: Returns true if the queue is full; false, otherwise.
{
  return length == maxItems;
}

template<class ItemType>
bool PQType<ItemType>::IsEmpty() const
// Post: Returns true if the queue is empty; false, otherwise.
{
  return length == 0;
}

template <class ItemPQ>
ostream& operator<<(ostream& out, const PQType<ItemPQ>& pq){
	for(int i = 0; i < pq.length; i++){
		out << pq.items.elements[i] << endl;
	}
	return out;
}

template <class ItemType>
void PQType<ItemType>::toString() const{
	toStringRec(items.elements, 0);
}

template <class ItemType>
void PQType<ItemType>::toStringRec(ItemType* elems, int level) const{
	if(level < length){
		toStringRec(elems, 2*level+2);  //right node recursive call
		for(int i = 0; i < int(log2(level+1)); i++){
			cout << "| ";
		}
		cout << elems[level] << "\n";
		toStringRec(elems, 2*level+1);  //left node recursive call
	}
}

#endif
