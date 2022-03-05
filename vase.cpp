#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mutex>

std::mutex mtx;
bool sign;
int count;

int getGuestCount();
class Guest
{
    private:
        bool sawVase;
    public:
        Guest()
        {
            sawVase = false;
        }//end constructor
        void seeVase()
        {
            if(!sawVase)
            {
                sawVase = true;
                count++;
            }
        }//end seeVase
        void lookAtSign(int num)
        {
            if(sign)
            {
                mtx.lock();
                sign = false;
                std::thread t (&Guest::seeVase, this);
                t.join();
                sign = true;
            }
            mtx.unlock();
        } //end run


};//end class
int main()
{
    int numGuests = getGuestCount();
    sign = true;
    count = 0;
    int allowedGuest = 0;
    Guest guests[numGuests];
    //seed random
    srand(time(NULL));

    while(count < numGuests - 1)
    {
        allowedGuest = rand() % numGuests;

        guests[allowedGuest].lookAtSign(allowedGuest);
    }//end while

    std::cout << "All guests have seen the vase\n";
    return 0;
}//end main
/////////////////////////////////////////////////////////////////////////////////////////////////////
int getGuestCount()
{
    int result = 0;
    
    std::cout << "Enter the amount of guests attending: ";
    std::cin >> result;

    return result;
}//end of getGuests