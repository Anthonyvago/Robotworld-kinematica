/**
 * @file StringUtils.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

namespace Utils {
enum class Color_e {
  NORMAL_BLACK = 30,
  NORMAL_RED = 31,
  NORMAL_GREEN = 32,
  NORMAL_YELLOW = 33,
  NORMAL_BLUE = 34,
  NORMAL_MAGENTA = 35,
  NORMAL_CYAN = 36,
  NORMAL_WHITE = 37,

  BRIGHT_BLACK = 90,
  BRIGHT_RED = 91,
  BRIGHT_GREEN = 92,
  BRIGHT_YELLOW = 93,
  BRIGHT_BLUE = 94,
  BRIGHT_MAGENTA = 95,
  BRIGHT_CYAN = 96,
  BRIGHT_WHITE = 97,

  NONE = 0,
};

class StringUtils {
public:
  /**
   * @brief Divide a string into smaller sections based on given start and stop
   * char.
   *
   * @param str
   * @param start Start of substring char.
   * @param stop Stop of substring char.
   * @return vector<string> Found substrings.
   */
  static vector<string> Divide(const string &str, char start, char stop);

  /**
   * @brief Divide a string into smaller sections based on given target char.
   *
   * @param str
   * @param target Target to search for.
   * @return vector<string> Found substrings.
   */
  static vector<string> Divide(const string &str, char target);

  /**
   * @brief Check if value is within bounds.
   *
   * @param value Buffer for validated value.
   * @param reading The read value.
   * @param min Minimal value of reading.
   * @param max Maximal value of reading.
   * @return true If the validation was successful.
   * @return false If the validation was unsuccessful.
   */
  static bool ValidateNumber(float &value, const string &reading, float min,
                             float max);

  /**
   * @brief Add color codes to string.
   *
   * @param str
   * @param color
   * @return string String with color codes.
   */
  static string Color(const string &str, Color_e color);

  /**
   * @brief Add color codes to char.
   *
   * @param el
   * @param color
   * @return string Char with color codes.
   */
  static string Color(char el, Color_e color);

  /**
   * @brief Convert value to string with precision.
   *
   * @tparam T Type of variable.
   * @tparam size Size of array.
   * @param list Array of variables to convert.
   * @param precision Precision of conversion.
   * @return array<string, size> Array of converted values.
   */
  template <typename T, uint32_t size>
  static array<string, size> ToString(array<T, size> list,
                                      uint8_t precision = 2);

  /**
   * @brief Convert value to string with precision.
   *
   * @tparam T Type of variable.
   * @param list Vector of variables to convert.
   * @param precision Precision of conversion.
   * @return vector<string> Vector of converted values.
   */
  template <typename T>
  static vector<string> ToString(vector<T> list, uint8_t precision = 2);

  /**
   * @brief Convert value to string with precision.
   *
   * @tparam T Type of variable.
   * @param number Variable to convert.
   * @param precision Precision of conversion.
   * @return string Converted value.
   */
  template <typename T> static string ToString(T number, uint8_t precision = 2);

  /**
   * @brief Remove target chars from stirng.
   *
   * @param str
   * @param target
   */
  static void Remove(string &str, char target);

  /**
   * @brief Remove list of target chars from string.s
   *
   * @param str
   * @param targets
   */
  static void Remove(string &str, const vector<char> &targets);

  /**
   * @brief Replace all occurrences of target char with replacement.
   *
   * @param str
   * @param target
   * @param replacement
   */
  static void Replace(string &str, char target, char replacement);

  /**
   * @brief Encase string with colored char.
   *
   * @param str
   * @param element
   * @param color
   */
  static void Encase(string &str, char element, Color_e color = Color_e::NONE);

  /**
   * @brief Encase string with colored start and stop char.
   *
   * @param str
   * @param start
   * @param stop
   * @param color
   */
  static void Encase(string &str, char start, char stop,
                     Color_e color = Color_e::NONE);

  /**
   * @brief Remove first and last element from string.
   *
   * @param str
   */
  static void RemoveEncasement(string &str);
};
} // End of namespace Utils

#endif // End of STRING_UTILS_HPP
