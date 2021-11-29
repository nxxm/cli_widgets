#define BOOST_TEST_MODULE passphrase_test
#include <boost/test/included/unit_test.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cli_widgets/hidden_input_guard.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>

 BOOST_AUTO_TEST_CASE(passphrase_test) {
  namespace bp = boost::process;
  namespace fs = boost::filesystem;

  bp::opstream in;
  bp::ipstream out;
  bp::pipe p;
  std::vector<std::string> outline;
  std::string value;
  std::string path_to_exe;

  fs::path current_path = fs::absolute(fs::current_path());
  for (fs::directory_entry &entry : fs::recursive_directory_iterator{current_path}) {
    if (entry.path().filename().string() == "stdin_hide_guard" ||entry.path().filename().string() == "stdin_hide_guard.exe" ) {
      path_to_exe = entry.path().string();
    }
  }

  std::vector<std::string> many_password = {"Un p@ssw0rd balnéaire à Zürich ?"};

  for (auto password : many_password){
    bp::child c(path_to_exe,"automatic",bp::std_out > out, bp::std_in < in);

    while (c.running() && std::getline(out, value) && !value.empty()) {
      in << password << std::endl;
      outline.push_back(value);
    }

    c.wait();
    c.terminate();
    int found_pass = 0;
    std::string output_password;
    std::string begin_from_password = password.substr(0,3);
    for (auto read : outline) {
      if (boost::algorithm::starts_with(read, begin_from_password)) {

        output_password = read;
      }
    }

    BOOST_REQUIRE(boost::algorithm::contains(output_password,password));
  }
}