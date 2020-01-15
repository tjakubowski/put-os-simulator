#include "pch.h"
#include "CPU.h"
#include "Process.h"
#include <iostream>
#include <vector>


void CPU_M::insert_to_heap(std::vector<Process*> &heap, Process *P)
{
	heap.push_back(P);
	
	order_heap(heap);
}

//heapify function
void CPU_M::heapify(std::vector<Process*> &heap, int n, int i)
{
	int largest = i; // reordering from the beginning node
	int l = 2 * i + 1; // left node
	int r = 2 * i + 2; // right node

	// if a child L is larger than parent change the l
	if (l < n && heap[l]->priority() < heap[largest]->priority())
		largest = l;

	// if right child is larger than largest so far 
	if (r < n && heap[r]->priority() < heap[largest]->priority())
		largest = r;

	// if largest is not root then swap and reorder
	if (largest != i)
	{
		std::swap(heap[i], heap[largest]);

		//reorder the heap to get the largest to the top
		heapify(heap, n, largest);
	}
}

void CPU_M::order_heap(std::vector<Process*> &heap){
	int n = heap.size();
	//Build heap
	for(int i = n/2-1; i>=0; i--){
		heapify(heap, n, i);
	}

	//One by one extract an element from heap
	for(int i = n-1;i>=0;i--){
		//Move root to hte end
		std::swap(heap[0], heap[i]);

		//call max heapify on the reduced heap
		heapify(heap, i, 0);

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


void CPU_M::printheap(std::vector<Process*> &heap){
	int n = heap.size();
	for(int i = 0; i < n; i++){
		std::cout<< "P.id: " << heap[i]->id() << " P.priority: " << heap[i]->priority();
		std::cout<< std:: endl;
	}
}
