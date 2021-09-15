#include <iostream>
#include <thread>
#include <chrono>
#include <cli_widgets/stdin_hide_guard.hpp>

int main(int argc, char **argv) {
  std::string passphrase;
  std::cout << "Please enter your password : " << std::endl;
  cli_widgets::stdin_hide_guard hide_password{true};
  std::cin >> passphrase;
  return 0;
}