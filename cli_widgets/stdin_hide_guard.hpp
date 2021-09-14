#pragma once
#include <iostream>
#include <boost/predef.h>
#if BOOST_OS_WINDOWS
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace cli_widgets {

  inline void set_stdin_echo(bool enable) {
#if BOOST_OS_WINDOWS
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (!enable) {
      mode &= ~ENABLE_ECHO_INPUT;
    } else {
      mode |= ENABLE_ECHO_INPUT;
    }

    SetConsoleMode(hStdin, mode);
#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable) {
      tty.c_lflag &= ~ECHO;
    } else {
      tty.c_lflag |= ECHO;
    }

    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
  }

  struct stdin_hide_guard {
    stdin_hide_guard() { set_stdin_echo(true); }
    ~stdin_hide_guard() { set_stdin_echo(false); }
  };
}
