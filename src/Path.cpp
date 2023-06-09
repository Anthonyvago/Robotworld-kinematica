/**
 * @file Path.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Path.hpp"
#include "Logger.hpp"

#include <utility>

using namespace std;

namespace Model {
Path::Path(string name, const wxColor &pathColor, const wxColor &posColor)
    : name(move(name)), state(true), pathColor(pathColor), posColor(posColor) {}

Path::Path(string name, vector<Point> path, const wxColor &pathColor,
           const wxColor &posColor)
    : name(move(name)), points(move(path)), state(true), pathColor(pathColor),
      posColor(posColor) {}

void Path::addPoint(const Point &newPoint) { points.emplace_back(newPoint); }

void Path::removePoint(int32_t index) {
  points.erase(points.begin() + static_cast<int32_t>(index));
}

// USER DEFINED OPERATORS from here on:
bool Path::operator==(const Path &other) {
  // First, check if name and size of points are equal:
  if ((name == other.name) && (points.size() == other.points.size())) {
    // Then, check if all points are equal to each other:
    for (size_t i = 0; i < points.size(); ++i) {
      if (points[i] != other.points[i]) {
        // If one point is not equal, return false immediately because checking
        // is no longer necessary:
        return false;
      }
    }
  } else {
    return false;
  }

  // If code reaches this point, all points are equal and the name is equal, so
  // return true:
  return true;
}

// SETTERS from here on:
void Path::setPoint(size_t index, const Point &newPoint) {
  try {
    points.at(index) = newPoint;
  } catch (out_of_range &e) {
    LOG("exception caught", e.what());
    cerr << "exception caught, " << e.what() << endl;
  }
}

void Path::setPath(const vector<Point> &newPath) { points = newPath; }

void Path::setPathState(bool newState) { state = newState; }

// GETTERS from here on:
bool Path::getPathState() const { return state; }

Point Path::getPoint(size_t index) const {
  Point point(0, 0);

  try {
    point = points.at(index);
  } catch (out_of_range &e) {
    // Print error message to console:
    LOG("exception caught", e.what());
    cerr << "exception caught, " << e.what() << endl;
  }

  return point;
}

vector<Point> Path::getPoints() const { return points; }

wxColour Path::getPathColor() const { return pathColor; }

wxColour Path::getPositionColor() const { return posColor; }

string Path::getName() const { return name; }

string Path::asString() const { return "Path"; }

string Path::asDebugString() const { return asString(); }

} // End of namespace Model