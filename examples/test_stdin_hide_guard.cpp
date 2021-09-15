#define BOOST_TEST_MODULE test_stdin_hide_guard
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cli_widgets/stdin_hide_guard.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_CASE(test_stdin_hide_guard) {
  namespace bp = boost::process;
  namespace fs = boost::filesystem;

  bp::opstream in;
  bp::ipstream out;
  bp::pipe p;
  std::vector<std::string> outline;
  std::string value;
  std::string path_to_exe;
  std::string password = "passwordtest";

  fs::path current_path = fs::absolute(fs::current_path());
  for (fs::directory_entry &entry : fs::recursive_directory_iterator{current_path}) {
    if (entry.path().filename().string() == "stdin_hide_guard") {
      std::cout << entry.path().string() << std::endl;
      path_to_exe = entry.path().string();
    }
  }

  bp::child c(path_to_exe, bp::std_out > out, bp::std_in < in);

  while (c.running() && std::getline(out, value) && !value.empty()) {
    in << password << std::endl;
    outline.push_back(value);
  }

  c.wait();
  c.terminate();
  int found_pass = 0;

  for (auto read : outline) {
    std::cout << read << std::endl;
    std::size_t found = read.find(password);
    if (found != std::string::npos) {
      found_pass++;
    }
  }

  BOOST_REQUIRE(found_pass == 1);
}