#include <thread>
#include <functional>

class PrimeThread
{
    private:
        bool running;
        std::function<void(int, bool*)> sieve;
        std::thread t;
    public:
        PrimeThread(function<void(int, bool*)> foo)
        {
            running = false;
            sieve = foo;
        }//end of constructor

        bool isRunning()
        {
            return running;
        }//end isRunning
        void run()
        {
            t = std::thread(sieve);
            t.join();
            running = false;
        }//end run

}//end of class