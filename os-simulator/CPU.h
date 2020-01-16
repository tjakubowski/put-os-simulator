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
	static void insert_to_heap(std::vector<Process*> &heap, Process *p);

	//WYkonywanie procesu na gorze kopca
    static void scheduling(std::vector <Process*> &heap);
	
	//Print the heap with ID and PRIORITY
	static void print_heap(std::vector<Process*> &heap);
	
	private:
	
    //Utrzymanie kopca
	static void order_heap(std::vector<Process*> &heap);
   
	static void heapify(std::vector<Process*> &heap, int n, int i);
   
	//Porownanie procesow pod wzgledem priority
	bool compare(Process *p1, Process *p2);

	
};