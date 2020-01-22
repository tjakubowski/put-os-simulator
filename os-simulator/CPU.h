#pragma once
#include <vector>
#include <iostream>
#include "Process.h"
#include "ProcessManager.h"
#include "Singleton.h"


class CPU_M : public Singleton<CPU_M>{
	friend class Singleton<CPU_M>;
	
	public:
	//Dodanie procesu do kopca
	void insert_to_heap(Process *p);

	//WYkonywanie procesu na gorze kopca
    void scheduling();
	
	//Print the heap with ID and PRIORITY
	void print_heap();
	
    //Utrzymanie kopca
	void order_heap(std::vector<Process*> &heap);
   
	void heapify(std::vector<Process*> &heap, int n, int i);
   
private:
	//Porownanie procesow pod wzgledem priority
	bool compare(Process *p1, Process *p2);

	
};