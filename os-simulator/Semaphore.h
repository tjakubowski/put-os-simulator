#pragma once
#include <queue>
#include <string>
#include "Singleton.h"
#include "ProcessManager.h"

using namespace std;
class ProcessManager;

class Semaphore
{
protected:
	int value;
	queue<string> queue;

public:

	void Wait(std::string name);
	void Signal();

	Semaphore(int k) : value(k) {}


	//krokowy
	/*
	void/bool print_value();
	void/bool print_queue();

	*/

};
