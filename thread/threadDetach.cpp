#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
 
void pause_thread(int n) 
{
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "thread: " << n << " spawned here\n";
}
 
int main() 
{
  std::cout << "Spawning and detaching 3 threads...\n";
  for (int i = 0 ; i < 1000; i++ ){
    std::thread (pause_thread,i).detach();
  }
  std::cout << "Done spawning threads.\n";

  std::this_thread::sleep_for (std::chrono::seconds(1000));
  std::cout << "(the main thread will now pause for 5 seconds)\n";
  // give the detached threads time to finish (but not guaranteed!):
  pause_thread(5);
  return 0;
}
