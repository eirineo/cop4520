#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mutex>
//globals
std::mutex mtx;
bool cupcakePresent;
int count = 0;
std::string temp;
//prototyping
int getGuestCount();

class Guest
{
    private:
        bool ateCupcake;
        bool leader;
    public:
        Guest()
        {
            ateCupcake = false;
            leader = false;
        }//end constructor
        void eatCupcake()
        {
            ateCupcake = true;
	    cupcakePresent = false;
        }//end eatCupcake
        void makeLeader()
        {
            leader = true;
        }
        bool leaderStatus()
        {
            return leader;
        }//end leader
        void run()
        {
            mtx.lock();
            std::thread t (&Guest::visitLab, this);
            t.join();
            mtx.unlock();
        } //end run
        void visitLab()
        {   
            if(leader && !cupcakePresent)
            {

                count++;
                cupcakePresent = true;
            }
            if(!ateCupcake && cupcakePresent)
            {
                eatCupcake();
            }//end if
        }//end visitLab

};//end class
int main()
{
    int numGuests = getGuestCount();
    cupcakePresent = true;
    int selectedGuest = 0;
    Guest guests[numGuests];
    //seed random
    srand(time(NULL));
    guests[0].makeLeader();
    while(count != numGuests - 1)
    {
        selectedGuest = rand() % numGuests;

        guests[selectedGuest].visitLab();

	//std::cin >> temp;
    }//end while

    std::cout << "All cupcakes eaten\n";
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
