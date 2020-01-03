#pragma once
#include <vector>
#include <iostream>

class CPU_M{
    private:

	//Dodanie procesu do kopca
	void insert_to_heap(std::vector<Process*> &heap, Process *P);

    //Utrzymanie kopca
	void order_heap(std::vector<Process*> &heap);
   
	//WYkonywanie procesu na gorze kopca
    void scheduling(std::vector <Process*> &heap);
    
	//Porownanie procesow pod wzgledem priority
	bool compare(Process *P1, Process *P2);

    //Wyciagniecie ze stosu procesu z najwiekszym priorytetem
    Process extract_highest(std::vector <Process*> &heap);
};