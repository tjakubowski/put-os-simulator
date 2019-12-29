#pragma once

class CPU_M{
    private:
    //Utrzymanie kopca
    void order_heap(Process Heap[], int* heapsize, int start);
    //Dodanie procesu do kopca
    void insert_to_heap(Process Heap[], int* heapsize, int priority);
    //WYkonywanie procesu na gorze kopca
    void scheduling(Process Heap[], int* heapsize, int n, int* heapsize);
    //Porownanie procesow pod wzgledem priority
    bool compare(Process P1, Process P2);
}