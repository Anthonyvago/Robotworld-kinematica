/**
 * @file FileIO.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "FileIO.hpp"

using namespace std;

namespace Utils {
bool FileIO::readDirectory(Path path, Buffer buffer, bool fromRoot) {
  filesystem::path dirPath = ((fromRoot) ? getenv("HOME") : "") + path;

  try {
    if (!exists(dirPath)) {
      cerr << "Error while reading dir: Dir does not exist! " << path << endl;

      return false;
    } else {
      for (const auto &entry : filesystem::directory_iterator(dirPath)) {
        buffer.emplace_back(entry.path().generic_string());
      }
    }
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error while reading dir: " << e.what() << "\nWith path: " << path
         << endl;
    return false;
  }
  return true;
}

bool FileIO::createDirectory(Path path, Name name, bool fromRoot) {
  filesystem::path dirPath = ((fromRoot) ? getenv("HOME") : "") + path + name;
  try {
    if (exists(dirPath)) {
      cerr << "Warning while creating dir '" << dirPath << "': Already exists!"
           << endl;

      return false;
    } else {
      filesystem::create_directory(dirPath);
    }
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error while checking if dir exists/creating dir: " << e.what()
         << "\nWith path: " << path << endl;
    return false;
  }
  return true;
}

bool FileIO::removeDirectory(Path path, bool fromRoot) {
  filesystem::path dirPath = ((fromRoot) ? getenv("HOME") : "") + path;
  try {
    if (!exists(dirPath)) {
      cerr << "Error: Dir '" << path << "' does not exist!" << endl;
      return false;
    } else {
      filesystem::remove_all(dirPath);
    }
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error while checking if dir exists/removing dir: " << dirPath
         << endl
         << e.what() << endl;
    return false;
  }
  return true;
}

bool FileIO::readFile(Path path, Buffer buffer, bool fromRoot, int16_t index) {
  filesystem::path filePath = ((fromRoot) ? getenv("HOME") : "") + path;

  try {
    if (!exists(filePath)) {
      cerr << "Error: file '" << filePath << "' does not exist!" << endl;
      return false;
    } else {
      ifstream file(filePath);
      string line;

      if (index > -1) {
        uint16_t lineIndex = 0;
        while (getline(file, line) && lineIndex < index)
          ++lineIndex;
        buffer.emplace_back(line);
      } else {
        while (getline(file, line))
          buffer.emplace_back(line);
      }
      file.close();
    }
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error while reading file '" << filePath << "': " << e.what()
         << endl;
    return false;
  }
  return true;
}

bool FileIO::createFile(Path path, Name name, bool fromRoot) {
  filesystem::path filePath = ((fromRoot) ? getenv("HOME") : "") + path + name;
  try {
    if (exists(filePath)) {
      cerr << "Error while creatin file '" << filePath << "': Already exists!"
           << endl;

      return false;
    } else {
      ofstream file(filePath);
      file.close();
    }
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error while creating file '" << filePath << "': " << e.what()
         << endl;
    return false;
  }
  return true;
}

bool FileIO::removeFile(Path path, bool fromRoot) {
  filesystem::path filePath = ((fromRoot) ? getenv("HOME") : "") + path;
  try {
    if (!exists(filePath)) {
      cerr << "Error while removing file '" << filePath << "': Does not exist!"
           << endl;

      return false;
    } else {
      filesystem::remove(filePath);
    }
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error while removing file '" << filePath << "': " << e.what()
         << endl;
    return false;
  }
  return true;
}

bool FileIO::elementExist(Path path, bool fromRoot) {
  filesystem::path elementPath = ((fromRoot) ? getenv("HOME") : "") + path;
  try {
    return (exists(elementPath));
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error: " << e.what() << endl;
    return false;
  }
}

bool FileIO::writeToFile(Path path, Lines lines, bool append, bool fromRoot) {
  filesystem::path filePath = ((fromRoot) ? getenv("HOME") : "") + path;
  try {
    ofstream file;

    if (append) {
      file.open(filePath, ios_base::app);
    } else {
      file.open(filePath, ofstream::trunc | ofstream::out);
    }
    for_each(lines.begin(), lines.end(),
             [&](const string &line) { file << line << "\n"; });
    file.close();
  } catch (filesystem::filesystem_error &e) {
    cerr << "Error: " << e.what() << endl;
    return false;
  }
  return true;
}

string FileIO::getFileName(Path path) {
  return string(path.begin() + static_cast<long>(path.rfind('/')) + 1,
                path.end());
}

} // End namespace Utils