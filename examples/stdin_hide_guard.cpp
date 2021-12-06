
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cli_widgets/hidden_input_guard.hpp>

int main(int argc, const char *argv[]) {
  std::string passphrase;
  std::cout << "Please enter your password : " << std::endl;
  {
  cli_widgets::hidden_input_guard disable_display{};
  passphrase = disable_display.ask_something_to_user();
  }
  std::cout << passphrase << std::endl;

  return 0;
}