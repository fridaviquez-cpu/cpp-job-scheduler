//============================================================================
// Name        : CSC240_HeapSort.cpp
// Author      : Ivan Temesvari
// Version     : 4/8/2020
//============================================================================

#include <iostream>
#include <chrono>
#include "PQType.h"
using namespace std::chrono;
using namespace std;

int main() {
	int nums[] = {2, 44, 55, 73, 76, 16, 23, 33};
	PQType<int> theHeap(nums);  //call to Heapify which builds the heap.
	cout << "Print Heap as list (in heap level order): \n" << theHeap << endl;
	cout << "Print Heap as list (in ascending order): \n";
	int* nums_sorted = theHeap.Sort();
	for(int i = 0; i < sizeof(nums_sorted); i++){
		cout << nums_sorted[i] << endl;
	}

	PQType<int> maxHeap(40);
	// Insert 2, 44, 55, 73, 76, 16, 23, 33
	maxHeap.Enqueue(2);
	maxHeap.Enqueue(44);
	maxHeap.Enqueue(55);
	maxHeap.Enqueue(73);
	maxHeap.Enqueue(76);
	maxHeap.Enqueue(16);
	maxHeap.Enqueue(23);
	maxHeap.Enqueue(33);

	int dequeued;
	cout << "Print Heap as a tree: \n";
	maxHeap.toString();
	cout << endl;
	maxHeap.Dequeue(dequeued);
	cout << "Item dequeued: " << dequeued << endl;

	cout << "Print Heap as a tree (after removing max item): \n";
	maxHeap.toString();
	cout << endl;
	maxHeap.Enqueue(60);
	cout << "Print Heap as a tree (after enqueuing 60): \n";
	maxHeap.toString();
	cout << endl;
	maxHeap.Enqueue(90);
	cout << "Print Heap as a tree (after enqueuing 90): \n";
	maxHeap.toString();
	cout << endl;

	int maxItem;
	maxHeap.Dequeue(maxItem);
	cout << "The max item removed from the heap: " << maxItem << endl;
	maxHeap.toString();
	cout << endl;
	maxHeap.Dequeue(maxItem);
	cout << "The max item removed from the heap: " << maxItem << endl;
	maxHeap.toString();

	cout << "Enter an item to find:";
	int item;
	cin >> item;

	int option = -1;
	cout << "Enter the option to use for the find\n(1. Sort-Sequential, 2. Sort-Binary, 3. Dynamic, 4. Sequential, 5. Sort-Binary with no copy overhead): " << endl;
	cin >> option;
	bool found = false;
	//Sequential find
	if(option == 1){
		auto start = high_resolution_clock::now();
		found = maxHeap.FindSequential(item);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		if(found){
			cout << item << " found." << endl;
		}
		else{
			cout << item << " not found." << endl;
		}
		cout << "Time for sequential search: " << duration.count()
			 << " microseconds." << endl;
	}
	//Binary find
	else if(option == 2){
		auto start = high_resolution_clock::now();
		found = maxHeap.FindBinary(item);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		if(found){
			cout << item << " found." << endl;
		}
		else{
			cout << item << " not found." << endl;
		}
		cout << "Time for binary search: " << duration.count()
			<< " microseconds." << endl;
	}
	//Dynamic programming find
	else if(option == 3){
		auto start = high_resolution_clock::now();
		found = maxHeap.FindPQ_Heap(item);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		if(found){
			cout << item << " found." << endl;
		}
		else{
			cout << item << " not found." << endl;
		}
		cout << "Time for dynamic search: " << duration.count()
			<< " microseconds." << endl;
	}
	else if(option == 4){
		//Find sequentially a given value in the heap before sort. Time this search.
		auto start = high_resolution_clock::now();
		bool found = maxHeap.Find(item);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		if(found){
			cout << item << " found." << endl;
		}
		else{
			cout << item << " not found." << endl;
		}
		cout << "Time for sequential search with no sort: " << duration.count()
			 << " microseconds." << endl;
	}
	else if(option == 5){
		//Find a given value in the heap after sort. Time this search.
		auto start = high_resolution_clock::now();
		//Sort the heap and display it.
		maxHeap.Sort();  //No longer a heap!!
		bool found = maxHeap.FindSorted(item);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		if(found){
			cout << item << " found." << endl;
		}
		else{
			cout << item << " not found." << endl;
		}
		cout << "Time for sequential search with sort (no copy overhead): " << duration.count()
				 << " microseconds." << endl;
	}
	else
		cout << "Option not found." << endl;
	return 0;
}
