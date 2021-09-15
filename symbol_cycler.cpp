#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cli_widgets/spin_loader.hpp>
#include <cli_widgets/symbol_cycler.hpp>
#include <termcolor/termcolor.hpp>

const std::chrono::nanoseconds step_slow{100000000};

int main(int argc, char** argv) {
 
  std::cout << termcolor::yellow << "Just a simple symblo cycler: " << termcolor::reset << std::endl;

  const std::vector<std::string> symbols { "v", "<", "^", ">" };
  cli_widgets::symbol_cycler spinner(symbols);

  for(int i = 50; i > 0; i--) {
    std::cout << "\r" << spinner.next() << " <- Hey! Look at me =D" << std::flush;
    std::this_thread::sleep_for(step_slow);
  }

  std::cout << std::endl;
  std::cout << termcolor::yellow << "Same game using one of the inbuilt symbol collections: " << termcolor::reset << std::endl;

  cli_widgets::symbol_cycler spinner_inbuilt(cli_widgets::spinner_symbols::symbols_braille_inverted);

  for(int i = 50; i > 0; i--) {
    std::cout << "\r" << termcolor::bright_red << spinner_inbuilt.next() << termcolor::reset;
    std::cout << " <- We can do just the spinner in color as well!" << std::flush;
    std::this_thread::sleep_for(step_slow);
  }

  std::cout << std::endl;
  std::cout << "Combining ";
  std::cout << termcolor::bright_magenta << "cli_widget::symbol_cycler" << termcolor::reset;
  std::cout << " and ";
  std::cout << termcolor::cyan << "cli_widget::spin_loader" << termcolor::reset;
  std::cout << std::endl;

  // Combining two widgets
  cli_widgets::symbol_cycler spinner_inbuilt2(cli_widgets::spinner_symbols::symbols_angles);
  cli_widgets::spin_loader loader(std::cout);
  loader.launch();

  for(int i = 100; i > 0; i--) {
    std::cout << " --> " << termcolor::bright_green << spinner_inbuilt2.next() << termcolor::reset;
    std::cout << " <-- totally magically works too";
    std::this_thread::sleep_for(step_slow);
  }

  loader.stop();
  return 0;
}