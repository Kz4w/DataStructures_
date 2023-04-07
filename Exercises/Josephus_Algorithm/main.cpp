#include <iostream>
#include "circularList.cpp"

circularList* match = new circularList();

int jhosephus (int n,int k) {
    while (n == 1) {
        for (short i = 1; i < k; i++)
            match -> it();
        n--;
    }
}


int main () {
    /*
        Se modificaron cosas ...
    */
    int personas = 10;
    bool flow = false;
    int jump = 2;
    short i = 0;

    
    for (i = 1; i < 42 ; i++)
        match -> pushBack(i);
    
    int result = jhosephus(flow,jump);
    std::cout << "Survivor -> " << result;
    return 0;
}