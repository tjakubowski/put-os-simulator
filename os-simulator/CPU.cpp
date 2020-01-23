#include "pch.h"
#include "CPU.h"
#include "Process.h"
#include "ProcessManager.h"
#include <iostream>
#include <vector>


void CPU_M::insert_to_heap(Process *p)
{
	auto heap = ProcessManager::GetInstance().ready_processes();
	heap.push_back(p);
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

void CPU_M::scheduling()
{
	auto running_p = ProcessManager::GetInstance().running_process();
	auto heap = ProcessManager::GetInstance().ready_processes();

	if (heap.empty())
		return;
	
	order_heap(heap);
	if (running_p->priority() < heap[0]->priority()) {
		if (heap.size() > 1) {
			int pos = 0;
			int tmp_id = heap[0]->id();
			for (int i = 0; i < heap.size(); i++) {

				int tmp_p = heap[0]->priority();
				if (heap[i]->priority() == tmp_p && tmp_id > heap[i]->id()) {
					tmp_id = heap[i]->id();
				}

			}
			for (int i = 0; i < heap.size(); i++) {
				if (heap[i]->id() == tmp_id) {
					pos = i;
					break;
				}
		
			}
			ProcessManager::GetInstance().SetProcessRunning(heap[pos]);
			heap.erase(heap.begin()+pos);
		}
		else {
			ProcessManager::GetInstance().SetProcessRunning(heap[0]);
			heap.erase(heap.begin());
		}
		order_heap(heap);
	}
}

//just compare processes' priorities
bool CPU_M::compare(Process *p1, Process *p2){
	if (p1->priority() > p2->priority()) {
		return true;
	}
	else return false;
}


void CPU_M::print_heap(){
	auto heap = ProcessManager::GetInstance().ready_processes();
	int n = heap.size();
	for(int i = 0; i < n; i++){
		std::cout<< "P.id: " << heap[i]->id() << " P.proirytet: " << heap[i]->priority();
		std::cout<< std:: endl;
	}
}
