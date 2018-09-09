#pragma once 

#include <ostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <codecvt>
#include <locale>
#include <string>

#include <boost/predef.h>
#include <termcolor/termcolor.hpp>

namespace cli_widgets {

  // convert wstring to UTF-8 string
  std::string wstring_to_utf8 (const std::wstring& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
  }


  /**
   * \brief spin_loaders constructs a txt widget to shows an
   *        action is in progress that we don't know the end
   *        for.
   *        It shows an animated : `⏳ {   ●●●       }`
   *        
   *        Usage is simple : 
   *
   *        ```cpp
   *        cli_widgets::spin_loader loader(std::cout);
   *        loader.launch();
   *        
   *        bool error = some_long_running_computation(); 
   *
   *        if (error) 
   *          loader.stop("error : it failed", true);
   *        else 
   *          loader.stop("success");
   *
   *        ```
   * 
   */
  struct spin_loader {

    //! configurable size
    std::size_t size = 10;

    //! configurable start icon
    std::wstring start_icon = 
      #if BOOST_OS_WINDOWS 
        L"- ";
      #else
        L"⏳ ";
      #endif

    //! configurable loader boundary
    std::string begin = "{";
    
    //! configurable loader boundary
    std::string end = "}";

    //! action being run, this can be a message too
    std::wstring action = 
      #if BOOST_OS_WINDOWS 
        L"...";
      #else
        L"●●●";
      #endif

    //! step_speed of the animation
    std::chrono::nanoseconds step_speed{80000000};

    std::ostream& _out;
    volatile bool _stop = true;
    std::thread _animating_thread;

    /**
     * \param out On which stream to display
     */
    spin_loader(std::ostream& out)
      : _out(out) {
    }

    /**
     * \param out On which stream to display
     * \param size size of the loader
     */
    spin_loader(std::ostream& out, std::size_t size)
      : size(size),
        _out(out) {
    }

    /**
     * \brief if not stopped the animation will be stopped.
     */
    ~spin_loader() { if (!_stop) stop(); }

    /**
     * \brief launches the animated spinloader.
     */ 
    void launch() {
      _stop = false;
      _animating_thread = std::thread([this]() {
        std::wstring action_expanded = action + std::wstring(size, ' ');

        for(;!_stop;) {
          
          for (size_t i=0; ((i < size) && !_stop); ++i) {
            _out << "\r" << wstring_to_utf8(start_icon) << termcolor::green << begin << termcolor::reset ;

            _out << termcolor::yellow;
            std::rotate(action_expanded.rbegin(), action_expanded.rbegin() + 1, action_expanded.rend());
            _out << wstring_to_utf8(action_expanded);
            _out << termcolor::reset;

            _out << termcolor::green << end << termcolor::reset << std::flush;

            std::this_thread::sleep_for(step_speed);
          }

        }

        _out << termcolor::reset;
        _out << "\r" << std::string(start_icon.size() + begin.size() + end.size() + action_expanded.size(), ' ');
      });
    }

    /**
     * \brief stops the animation.
     * \param stop_message by default `done.`
     * \param is_error green when false, red otherwise.
     */ 
    void stop(const std::string& stop_message = "done.", bool is_error = false) {

      try {
        _stop = true;
        _animating_thread.join();
      } catch (const std::system_error& ec) {
        // ignore if not joinable ( e.g. was not started)
      }

      if (is_error) {
        _out << termcolor::red;
      } else {
        _out << termcolor::green;
      }
      _out << "\r" << wstring_to_utf8(start_icon) << stop_message << std::endl;
      _out << termcolor::reset;

    }

    
  };
}
