#include <iostream>
#include <cli_widgets/spin_loader.hpp>

void some_long_running_computation();

int main(int argc, char** argv) {

  // Simple example
  cli_widgets::spin_loader loader(std::cout);
  loader.launch();
    some_long_running_computation();
  loader.stop();//("error.", true);


//  // Configurable
//  loader.size = 30;
//  loader.begin = "<[";
//  loader.end = "]>";
//  loader.action = L"<=== please wait ===>";
//  loader.step_speed = 
//    std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds{30});
//  loader.launch();
//    some_long_running_computation();
//  loader.stop();

  return 0;
}













void some_long_running_computation() {
  int sum = 0;
  for (long long i = 0; i < 1000000000; ++i) {
    sum *= (i * 12) / 3;
  }
}
