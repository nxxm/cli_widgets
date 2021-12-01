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
  
  std::string path_to_exe;

  fs::path current_path = fs::absolute(fs::current_path());
  for (fs::directory_entry &entry : fs::recursive_directory_iterator{current_path}) {
    if (entry.path().filename().string() == "stdin_hide_guard" ||entry.path().filename().string() == "stdin_hide_guard.exe" ) {
      path_to_exe = entry.path().string();
    }
  }

  std::vector<std::string> many_password = {"Un p@ssw0rd balnéaire à Zürich ?"
                                            ,"canal&descent(copper+slip)simplicity"
                                            ,"ownership&ease%by)scent*just"
                                            ,"now_meanwhileöclimb<duty/effect"
                                            ,"picture-complication_grow everlasting&beam"};

  for (auto password : many_password){
    bp::opstream in;
    bp::ipstream out;
    std::string value="";
    
    bp::child c(path_to_exe,bp::std_out > out, bp::std_in < in);
    bool  is_password = false;
    while (c.running() && std::getline(out, value) && !value.empty()) {
      in << password << std::endl;
      if (boost::algorithm::contains(value,password)){
        is_password = true;
      }
    }
    BOOST_REQUIRE(is_password);
    c.wait();
  }
}