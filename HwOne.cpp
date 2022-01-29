#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <fstream>
#define LIMIT 100000000
bool isPrime[LIMIT];

using namespace std::chrono;
//prototypes
void getTopTen(std::ofstream output);
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
    long int sum = 0;
    std::ofstream output;
    output.open("results.txt");
    int index = 9;
    int topTen[10];

    for(int i = 0; i < LIMIT; i++)
    {
        if(isPrime[i])
        {
            count++;
	    sum += i;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    output << "Time:\t" << duration.count() << "ms\n";
    output << "Total number of Primes:\t" << count << "\n";
    output << "Sum of all primes:\t" << sum << "\n";
    output << "Top ten max primes:\t";
    for(int i = LIMIT - 1; index > 0; i--)
    {
	if(isPrime[i])
	{
	    topTen[index] = i;
	    index--;
	}
    }
    for(int i = 0; i < 10; i++)
    {
	 output << topTen[i] << "\t";
    }
    output.close();
}//end main
void primeSieve()
{
    //bool *isPrime = new bool[LIMIT];
    std::fill_n(isPrime, LIMIT, true);
    PrimeThread* first = new PrimeThread();
    PrimeThread* second = new PrimeThread();
    PrimeThread* third = new PrimeThread();;
    PrimeThread* fourth = new PrimeThread();;
    PrimeThread* fifth = new PrimeThread();;
    PrimeThread* sixth = new PrimeThread();;
    PrimeThread* seventh = new PrimeThread();
    PrimeThread* eighth = new PrimeThread();;
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
            else if(!third->isRunning())
            {
                temp = index;
                index++;            
                third = new PrimeThread(temp);
                third->run();
                delete third;
            }//end third
            else if(!fourth->isRunning())
            {
                temp = index;
                index++;            
                fourth = new PrimeThread(temp);
                fourth->run();
                delete fourth;
            }//end fourth
            else if(!fifth->isRunning())
            {
                temp = index;
                index++;            
                fifth = new PrimeThread(temp);
                fifth->run();
                delete fifth;
            }//end fifth
            else if(!sixth->isRunning())
            {
                temp = index;
                index++;            
                sixth = new PrimeThread(temp);
                sixth->run();
                delete sixth;
            }//end sixth
            else if(!seventh->isRunning())
            {
                temp = index;
                index++;            
                seventh = new PrimeThread(temp);
                seventh->run();
                delete seventh;
            }//end seventh
            else if(!eighth->isRunning())
            {
                temp = index;
                index++;            
                eighth = new PrimeThread(temp);
                eighth->run();
                delete eighth;
            }//end eighth

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
