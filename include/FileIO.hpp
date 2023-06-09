/**
 * @file FileIO.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Utils {
class FileIO {
private:
  typedef const string &Path;
  typedef const string &Name;
  typedef vector<string> &Buffer;
  typedef const vector<string> &Lines;

public:
  static bool readDirectory(Path path, Buffer buffer, bool fromRoot = true);

  static bool createDirectory(Path path, Name name, bool fromRoot = true);

  static bool removeDirectory(Path path, bool fromRoot = true);

  static bool readFile(Path path, Buffer buffer, bool fromRoot = true,
                       int16_t index = -1);

  static bool createFile(Path path, Name name, bool fromRoot = true);

  static bool removeFile(Path path, bool fromRoot = true);

  static bool elementExist(Path path, bool fromRoot = true);

  static bool writeToFile(Path path, Lines lines, bool append = true,
                          bool fromRoot = true);

private:
  static string getFileName(Path path);
};

} // End of namespace Utils

#endif // End of FILEIO_HPP
