To run Minotaur's Birthday Party
g++ -pthread cupcake.cpp
./a.out
You will be asked to enter the number of guests

To run Minotaur's Crystal Vase
g++ -pthread vase.cpp
./a.out
You will be asked to enter the number of guests

Minotaur's Birthday Party

My stategy for this I chose to appoint one guest as a leader. The leader would keep count and only the leader could request another cupcake. The other guests keep track of whether they have
ate the cupcake or not. When they get to the end of the labyrinth if the cupcake is present and they have not eaten it yet they will eat it otherwise nothing happens. If the leader gets to the end of the
labryinth and the cupcake is not present they adjust the count and and replace the cupcake. 


Minotaur's Crystal Vase

I chose the second strategy. I though of this was the best way to utilize the threads without them wait on another thread. If there were other tasks that the guests could do this method 
would allow for them to go about them while not waiting for the vase to be available. A disadvantage is that unlock the other options I have to have the guests keep checking whether it is
available. In my code I have a random guest check to see if the vase is available to view. If it is the lock is set to make sure only one guest can continue. The guest then immediately flips the sign to prevent others from attempting to view the vase. I tested the code with print statements to determine if two guests would ever attempt to enter the room at the same time. All the
results I had showed that a guest would always enter and then leave before another guest attempted to view.