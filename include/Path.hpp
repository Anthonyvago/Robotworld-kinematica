/**
 * @file Path.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PATH_HPP
#define PATH_HPP

#include "ModelObject.hpp"
#include "Point.hpp"
#include "Widgets.hpp"

using namespace std;

namespace Model {
class Path;
typedef shared_ptr<Path> PathPtr;

class Path : public ModelObject {
public:
  Path(string name, const wxColor &pathColor, const wxColor &posColor);

  explicit Path(string name, vector<Point> path, const wxColor &pathColor,
                const wxColor &posColor);

  ~Path() override = default;

  void addPoint(const Point &newPoint);

  void removePoint(int32_t index);

  // User defined operators:
  bool operator==(const Path &other);

  // Setters:
  void setPoint(size_t index, const Point &newPoint);

  void setPath(const vector<Point> &newPath);

  void setPathState(bool newState);

  // Getters:
  bool getPathState() const;

  Point getPoint(size_t index) const;

  vector<Point> getPoints() const;

  wxColour getPathColor() const;

  wxColour getPositionColor() const;

  string getName() const;

  string asString() const override;

  string asDebugString() const override;

private:
  string name;
  vector<Point> points;
  bool state; // true=active, false=inactive
  wxColour pathColor;
  wxColour posColor;
};
} // End of namespace Model

#endif // End of PATH_HPP
