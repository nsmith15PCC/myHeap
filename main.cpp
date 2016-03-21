#include <iostream>
#include <cstdlib>
#include <fstream>
#include "heap.h"
#include <ctime>
#include <iomanip>


using namespace std;


int main(int argc, char *argv[])
{
    heap<int> theHeap;
    int theRandNum;
    srand(time(NULL));
    cout<<"Unsorted numbers: "<<endl;
    for(int i = 0; i < 25; i++)
    {
        theRandNum = rand()% 100 + 1;
        if(!(i%5))
            cout<<endl;
        cout<<setw(5)<<theRandNum;
        theHeap << theRandNum;
    }
    int count = 0;
    cout<<endl<<"\n\nsorted: "<<endl;
    while(!theHeap.empty())
    {
        theHeap>>theRandNum;
           if(!(count%5))
             cout<<endl;
        cout<<setw(5)<<theRandNum;
        count++;
    }
    cout<<"\n\n\nThat\'s all folks!!!"<<endl;
    return 0;
}
