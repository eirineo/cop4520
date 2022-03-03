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
/*
guests are threads
the first guest will act as a counter.
the cupcake will act as a boolean true the cupcake is there false the cupcake has been eaten
Only the first guest can request a new cupcake
when tehe first guest sees that a cupcake have been eaten he requests a new one and counts up 
each guest will need to check if they have eatena cupcake
*/
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
            //std::cout << leader << "\t" << cupcakePresent << "\t" << ateCupcake << "\n";
            if(leader && !cupcakePresent)
            {

                count++;
                cupcakePresent = true;
		std::cout << count << " cupcaks eaten\n";
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
	/*
	std::cout << selectedGuest << "\t";
	if(guests[selectedGuest].leaderStatus())
	{
		std::cout << "is a leader" << "\n";
	}
	else
	{
		std::cout << "is not leader" << "\n";
	}
	*/
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
// Guest[] initializeGuests(Guest[] guests)
// {
//     for(int i = 0; i < guest.length; i++)
//     {
//         Guest = new
//     }
// }
