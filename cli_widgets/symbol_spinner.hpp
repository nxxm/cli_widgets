#pragma once
#include <string>

namespace cli_widgets {

  /**
   * \brief symbol_spinner is a circular 
   * 
   * 
   * \note to future self and anyone else: don't do silly things which could make both passed iterators 
   * swap places like sorting the list etc which likely could cause havoc. Should be fine otherwise _/\Ö/\_
   */
  class symbol_spinner : public std::list<std::string>::const_iterator  {

    std::list<std::string>::const_iterator  begin, end;

  public:
    /**
     * \brief symbol spinner to (ring-)iterate over a collection of symbols
     * Symbols can be stored in a const std::list<std::string> whose begin() and end() itterators
     * must be passed to this class during construction.
     * 
     * Each iterator incrementation (or next() call) will get you access to the next symbol of
     * your favourite ASCII spinner.
     */
    symbol_spinner(std::list<std::string>::const_iterator b, std::list<std::string>::const_iterator e) 
      : std::list<std::string>::const_iterator(b)
      , begin(b)
      , end(e) {}

     /**
     * \brief symbol spinner to (ring-)iterate over a collection of symbols
     * Using the full range of provided symbols by accessing the begin() and end() operators
     * 
     * For reduced range look at the other constructor overloads
     */
    symbol_spinner(const std::list<std::string> &list) 
      : std::list<std::string>::const_iterator(list.begin())
      , begin(list.begin())
      , end(list.end()) {}   

    symbol_spinner &operator++(void) {
      std::list<std::string>::const_iterator::operator++();
      if (*this == end)
        std::list<std::string>::const_iterator::operator=(begin);
      return *this;
    }

    const symbol_spinner operator++(int) {
      const auto oldValue = *this;
      this->operator++();
      return oldValue;
    };

    const std::string& next() {
        return *(this->operator++());
    }

    symbol_spinner &operator--(void) = delete;
    const symbol_spinner operator--(int) = delete;
  };
}

namespace cli_widgets::spinner_symbols {

  /**
   * \brief ← ↖ ↑ ↗ → ↘ ↓ ↙
   */
  const std::list<std::string> symbols_arrows { "←", "↖", "↑", "↗", "→", "↘", "↓", "↙" };

  /**
   * \brief ▁ ▂ ▃ ▄ ▅ ▆ ▇ █ ▇ ▆ ▅ ▄ ▃ ▁
   */
  const std::list<std::string> symbols_bars_vertical { "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█", "▇", "▆", "▅", "▄", "▃", "▁" };

  /**
   * \brief ▉▊▋▌▍▎▏▎▍▌▋▊▉
   */  
  const std::list<std::string> symbols_bars_horizontal { "▉", "▊", "▋", "▌", "▍", "▎", "▏", "▎", "▍", "▌", "▋", "▊", "▉" };

  /**
   * \brief ▖ ▘ ▝ ▗
   */
  const std::list<std::string> symbols_sqares { "▖", "▘", "▝", "▗" };

  /**
   * \brief ┤ ┘ ┴ └ ├ ┌ ┬ ┐
   * 
   * /!\ this one is actually code page 850 safe
   */
  const std::list<std::string> symbols_angles { "┤", "┘", "┴", "└", "├", "┌", "┬", "┐" };
  /**
   * \brief ◢ ◣ ◤ ◥
   */
  const std::list<std::string> symbols_triangles {"◢", "◣", "◤", "◥" };

  /**
   * \brief ◰ ◳ ◲ ◱
   */
  const std::list<std::string> symbols_blocks { "◰", "◳", "◲", "◱" };

  /**
   * \brief ◴ ◷ ◶ ◵
   */
  const std::list<std::string> symbols_quarters { "◴", "◷", "◶", "◵" };

  /**
   * \brief ◐ ◓ ◑ ◒

   */
  const std::list<std::string> symbols_halves { "◐", "◓", "◑", "◒" };

  /**
   * \brief ◡◡ ⊙⊙ ◠◠
   */
  const std::list<std::string> symbols_circles { "◡", "◡", "⊙", "⊙", "◠", "◠" };

  /**
   * \brief ⠁⠂⠄⡀⢀⠠⠐⠈
   */
  const std::list<std::string> symbols_braille { "⠁", "⠂", "⠄", "⡀", "⢀", "⠠", "⠐", "⠈" };

  /**
   * \brief ⣾⣽⣻⢿⡿⣟⣯⣷
   */
  const std::list<std::string> symbols_braille_inverted { "⣾", "⣽", "⣻", "⢿", "⡿", "⣟", "⣯", "⣷" };

  /**
   * \brief 🕛 🕐 🕑 🕒 🕓 🕔 🕕 🕖 🕗 🕘 🕙 🕚
   */    
  const std::list<std::string> symbols_clocks { "🕛", "🕐", "🕑", "🕒", "🕓", "🕔", "🕕", "🕖", "🕗", "🕘", "🕙", "🕚" };

}