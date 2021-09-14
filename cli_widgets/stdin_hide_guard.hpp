#pragma once
#include <iostream>
#include <boost/predef.h>
#if BOOST_OS_WINDOWS
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace cli_widgets{
  struct stdin_hide_guard {
    stdin_hide_guard() {
#if BOOST_OS_WINDOWS
      HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
      DWORD mode;
      GetConsoleMode(hStdin, &mode);
      mode &= ~ENABLE_ECHO_INPUT;
      SetConsoleMode(hStdin, mode);
#else
      struct termios tty;
      tcgetattr(STDIN_FILENO, &tty);
      tty.c_lflag &= ~ECHO;
      (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
    }

    ~stdin_hide_guard() {
#if BOOST_OS_WINDOWS
      HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
      DWORD mode;
      GetConsoleMode(hStdin, &mode);
      mode |= ENABLE_ECHO_INPUT;
      SetConsoleMode(hStdin, mode);
#else
      struct termios tty;
      tcgetattr(STDIN_FILENO, &tty);
      tty.c_lflag |= ECHO;
      (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
    }
  };
}