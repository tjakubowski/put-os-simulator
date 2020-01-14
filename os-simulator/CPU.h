#pragma once
#include <vector>
#include <iostream>
#include "Process.h"

class CPU_M{
    private:

	static void heapify(std::vector<Process*> &heap, int n, int i);

	//Dodanie procesu do kopca
	static void insert_to_heap(std::vector<Process*> &heap, Process *P);

    //Utrzymanie kopca
	static void order_heap(std::vector<Process*> &heap);
   
	//WYkonywanie procesu na gorze kopca
    void scheduling(std::vector <Process*> &heap);
    
	//Porownanie procesow pod wzgledem priority
	bool compare(Process *P1, Process *P2);

	//Print the heap with ID and PRIORITY
	static void printheap(std::vector<Process*> &heap);
};