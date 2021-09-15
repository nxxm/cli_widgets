#include <iostream>
#include <thread>
#include <chrono>
#include <cli_widgets/hidden_input_guard.hpp>

int main(int argc, char **argv) {
  std::string passphrase;
  std::cout << "Please enter your password : " << std::endl;
  
  {
    cli_widgets::hidden_input_guard hide_password{};
    std::cin >> passphrase;
  }
  
  std::cout << "passphrase : " << passphrase << std::endl;
  return 0;
}
