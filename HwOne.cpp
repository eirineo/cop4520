#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#define LIMIT 100000000
bool isPrime[LIMIT];

using namespace std::chrono;
//prototypes
void primeSieve();
void removeMultiples(int index);


class PrimeThread
{
    private:
        int classIndex;
        bool running;
    public:
        PrimeThread()
        {
            running = false;
        }
        PrimeThread(int i)
        {
            classIndex = i;
            running = false;
        }//end of constructor

        bool isRunning()
        {
            return running;
        }//end isRunning
        void run()
        {
	    running = true;
            std::thread t (removeMultiples, classIndex);
            t.join();
            running = false;
        }//end run

};//end of class

int main()
{
    auto start = high_resolution_clock::now();
    primeSieve();
    int count = 0;
    for(int i = 0; i < LIMIT; i++)
    {
        if(isPrime[i])
        {
            count++;
        }
    }
    //should 5761455
    std::cout << count << std::endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << duration.count() << "ms" << std::endl;
}//end main
void primeSieve()
{
    //bool *isPrime = new bool[LIMIT];
    std::fill_n(isPrime, LIMIT, true);
    PrimeThread* first = new PrimeThread();
    PrimeThread* second = new PrimeThread();
    //PrimeThread third;
    //PrimeThread fourth;
    //PrimeThread fifth;
    //PrimeThread sixth;
    //PrimeThread seventh;
    //PrimeThread eighth;
    int temp = 0;

    isPrime[0] = false;
    isPrime[1] = false;
    //this needs to be removed
    // for(int i = 2; i * i <= LIMIT; i++)
    // {
    //     // std::cout << i << std::endl;
    //     if(isPrime[i])
    //     {
    //         removeMultiples(i, isPrime);
    //     }//end if
    // }//end for loop
    //end old stuff

    int index = 2;
    while(index * index <= LIMIT)
    {   

        if(isPrime[index])
        {
	    if(!first->isRunning())
	    {
		temp = index;
		index++;
		first = new PrimeThread(temp);
		first->run();
		delete first;
	    }
	    else if(!second->isRunning())
	    {

            temp = index;
            index++;            
            second = new PrimeThread(temp);
	    second->run();
	    delete second;
	    }//end second
        }
	else
	{
	    index++;	
	}
    }//end while loop
}//end of primeSieve

void removeMultiples(int index)
{
    for(int j = 2 * index; j <= LIMIT; j += index)
    {
        isPrime[j] = false;
    }//end for loop
    return;
}//end removeMultiples
