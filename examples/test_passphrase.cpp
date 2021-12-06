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
#if BOOST_OS_WINDOWS
  path_to_exe ="./stdin_hide_guard.exe"
#else
  path_to_exe ="./stdin_hide_guard";
#endif

  std::vector<std::string> many_password = {"Un p@ssw0rd balnéaire à Zürich ?"
                                            ,"canal&descent(copper+slip)simplicity"
                                            ,"ownership&ease%by)scent*just"
                                            ,"now_meanwhileöclimb<duty/effect"
                                            ,"picture-complication_grow everlasting&beam"};

  for (auto password : many_password){
    bp::opstream in;
    bp::ipstream out;
    std::string value="";
    
    bp::child ask_passphrase_child(path_to_exe,bp::std_out > out, bp::std_in < in);
    bool  is_the_right_password = false;
    bool is_password_not_display = false;
    while (ask_passphrase_child.running() && std::getline(out, value) && !value.empty()) {
      in << password;

      if (value!=password){
        is_password_not_display = true;
      }

      in << std::endl;
      if (value==password){
        is_the_right_password = true;
        break;
      }
    }

    BOOST_REQUIRE(is_password_not_display);
    BOOST_REQUIRE(is_the_right_password);
    ask_passphrase_child.wait();
  }
}