#include <iostream>
#include <math.h>
#include <chrono>

#define LIMIT 100000000

using namespace std::chrono;
//prototypes
bool* primeSieve();
void removeMultiples(int index, bool* arr);

int main()
{
    auto start = high_resolution_clock::now();

    bool *test = primeSieve();
    int count = 0;
    for(int i = 0; i < LIMIT; i++)
    {
        if(test[i])
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
bool* primeSieve()
{
    bool *isPrime = new bool[LIMIT];
    std::fill_n(isPrime, LIMIT, true);

    isPrime[0] = false;
    isPrime[1] = false;

    for(int i = 2; i * i <= LIMIT; i++)
    {
        // std::cout << i << std::endl;
        if(isPrime[i])
        {
            removeMultiples(i, isPrime);
        }//end if
    }//end for loop
    return isPrime;
}//end of primeSieve

void removeMultiples(int index, bool* arr)
{
    for(int j = 2 * index; j <= LIMIT; j += index)
    {
        arr[j] = false;
    }//end inner for loop
    return;
}//end removeMultiples