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
        void run()
        {
            mtx.lock();
            std::thread t (&Guest::seeVase, this);
            t.join();
            mtx.unlock();
        } //end run


};//end class
int main()
{
    int numGuests = getGuestCount();
    sign = true;
    count = 0;
    int selectedGuest = 0;
    Guest guests[numGuests];
    //seed random
    srand(time(NULL));

    while(count < numGuests - 1)
    {
        if(sign)
        {
            selectedGuest = rand() % numGuests;

            guests[selectedGuest].run();            
        }//end if
    }//end while

    std::cout << "Guests have seen the vase\n";
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