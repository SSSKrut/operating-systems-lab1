// utils.h
#pragma once
#include <iostream>
#include <string>

namespace console::color {

enum class Color {
    Reset = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37
};

enum class Style { Reset = 0, Bold = 1, Dim = 2, Italic = 3, Underline = 4 };

class Colorizer {
   public:
    explicit Colorizer(Color color, Style style = Style::Reset) : color_(color), style_(style) {}

    friend std::ostream& operator<<(std::ostream& os, const Colorizer& c) {
        return os << "\033[" << static_cast<int>(c.style_) << ";" << static_cast<int>(c.color_)
                  << "m";
    }

   private:
    Color color_;
    Style style_;
};

inline std::string colorize(const std::string& text, Color color, Style style = Style::Reset) {
    return "\033[" + std::to_string(static_cast<int>(style)) + ";" +
           std::to_string(static_cast<int>(color)) + "m" + text + "\033[0m";
}

inline Colorizer red() { return Colorizer(Color::Red); }
inline Colorizer green() { return Colorizer(Color::Green); }
inline Colorizer yellow() { return Colorizer(Color::Yellow); }
inline Colorizer blue() { return Colorizer(Color::Blue); }
inline Colorizer cyan() { return Colorizer(Color::Cyan); }
inline Colorizer reset() { return Colorizer(Color::Reset); }

}  // namespace console::color
