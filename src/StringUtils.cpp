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

#include "StringUtils.hpp"
#include <cmath>

namespace Utils {
vector<string> StringUtils::Divide(const string &str, char start, char stop) {
  vector<string> words = Divide(str, stop);
  for (string &word : words) {
    Remove(word, start);
  }
  return words;
}

vector<string> StringUtils::Divide(const string &str, char target) {
  stringstream ss(str);
  string token;
  vector<string> words;

  while (getline(ss, token, target)) {
    words.emplace_back(token);
  }
  return words;
}

bool StringUtils::ValidateNumber(float &value, const string &reading, float min,
                                 float max) {
  try {
    value = stof(string(reading));
    value = fmax(min, fmin(max, value));
    return true;
  } catch (invalid_argument &e) {
    cerr << "Exception caught" << e.what() << endl;
  } catch (out_of_range &e) {
    cerr << "Exception caught" << e.what() << endl;
  }
  return false;
}

string StringUtils::Color(const string &str, Color_e color) {
  if (color == Color_e::NONE) {
    return str;
  } else {
    return "\x1B[" + to_string(static_cast<uint8_t>(color)) + "m" + str +
           "\033[0m";
  }
}

string StringUtils::Color(char el, Color_e color) {
  if (color == Color_e::NONE) {
    return string(1, el);
  } else {
    return "\x1B[" + to_string(static_cast<uint8_t>(color)) + "m" + el +
           "\033[0m";
  }
}

template <typename T, uint32_t size>
array<string, size> StringUtils::ToString(array<T, size> list,
                                          uint8_t precision) {
  array<string, size> newList;
  for_each(list.begin(), list.end(), [&precision, &newList](T number) {
    string element = ToString(number, precision);
    newList.template emplace_back(element);
  });
  return newList;
}

template <typename T>
vector<string> StringUtils::ToString(vector<T> list, uint8_t precision) {
  vector<string> newList;
  for_each(list.begin(), list.end(), [&precision, &newList](T number) {
    string element = ToString(number, precision);
    newList.template emplace_back(element);
  });
  return newList;
}

template <typename T>
string StringUtils::ToString(T number, uint8_t precision) {
  ostringstream os;
  os << fixed;
  os << setprecision(precision);
  os << number;

  return os.str();
}

void StringUtils::Remove(string &str, char target) {
  str.erase(remove(str.begin(), str.end(), target), str.end());
}

void StringUtils::Remove(string &str, const vector<char> &targets) {
  for (char target : targets) {
    str.erase(remove(str.begin(), str.end(), target), str.end());
  }
}

void StringUtils::Replace(string &str, char target, char replacement) {
  replace(str.begin(), str.end(), target, replacement);
}

void StringUtils::Encase(string &str, char element, Color_e color) {
  str = Color(element, color) + str + Color(element, color);
}

void StringUtils::Encase(string &str, char start, char stop, Color_e color) {
  str = Color(start, color) + str + Color(stop, color);
}

void StringUtils::RemoveEncasement(string &str) {
  str = str.substr(1, str.size() - 2);
}

} // End of namespace Utils
