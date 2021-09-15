#include <iostream>
#include <thread>
#include <chrono>
#include <cli_widgets/stdin_hide_guard.hpp>

int main(int argc, char **argv) {
  std::string passphrase;
  std::cout << "Please enter your password : " << std::endl;
  // the structure is forced to false for the example but it is the same not to use it 
  cli_widgets::stdin_hide_guard hide_password{false};
  std::cin >> passphrase;
  std::cout<<passphrase<<std::endl;
  return 0;
}