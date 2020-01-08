#include "pch.h"
#include "CPU.h"
#include "Process.h"
#include <iostream>
#include <vector>

void CPU_M::insert_to_heap(std::vector<Process*> &heap, Process *P)
{
	heap.push_back(P);
	int start = heap.size(), i;

	// Ordering the Heap 
	while (start != 0 && heap[(start - 1) / 2]->priority() > heap[start]->priority()) {
		Process* temp = heap[(start - 1) / 2];
		heap[(start - 1) / 2] = heap[start];
		heap[start] = temp;
		start = (start - 1) / 2;
	}
}

//heapify function
void CPU_M::order_heap(std::vector<Process*> &heap)
{
	int n = heap.size();
	int i = 0;
	int largest = 0; // reordering from the beginning node
	int l = 2 * i + 1; // left node
	int r = 2 * i + 2; // right node
	// if a child L is larger than parent change the l
	if (l < n && heap[l]->priority() > heap[largest]->priority())
		largest = l;

	// if right child is larger than largest so far 
	if (r < n && heap[r]->priority() > heap[largest]->priority())
		largest = r;

	// if largest is not root then swap and reorder
	if (largest != i)
	{
		std::swap(heap[i], heap[largest]);
		//reorder the heap to get the largest to the top
		order_heap(heap);
	}
}

void CPU_M::scheduling(std::vector<Process*> &heap)
{
	//
}

//just compare processes' priorities
bool CPU_M::compare(Process *P1, Process *P2){
	if (P1->priority() > P1->priority()) {
		return true;
	}
	else return false;
}

Process* CPU_M::extract_highest(std::vector<Process*> &heap){
    int n = Heap.size();
	Process *min = Heap[0];
	for(int i = 1; i < n; i++){
		if(heap[i]->priority() > min->priority()){
			min = heap[i];
		}
	}
	return min;
}