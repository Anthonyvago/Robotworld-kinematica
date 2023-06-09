/**
 * @file PathShape.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "PathShape.hpp"
#include "Logger.hpp"

using namespace std;

namespace View {
PathShape::PathShape(const Model::PathPtr &path) : Shape(path) {}

bool PathShape::occupies(const Point &point) const {
  vector<Point> pathPoints = getPath()->getPoints();

  for (const Point &pathPoint : pathPoints) {
    if (point == pathPoint) {
      return true;
    }
  }

  return false;
}

void PathShape::draw(wxDC &dc) {
  if (getPath()->getPathState()) {
    vector<Point> pathPoints = getPath()->getPoints();

    if (!pathPoints.empty()) {
      wxColour pathColor = getPath()->getPathColor();
      wxColour positionColor = getPath()->getPositionColor();

      wxPen positionPen(positionColor, 1, wxPENSTYLE_SOLID);
      wxPen pathPen(pathColor, 2, wxPENSTYLE_SOLID);
      dc.SetBrush(positionColor);

      for (auto it = next(pathPoints.begin()); it != pathPoints.end(); ++it) {
        Point start = *(it - 1);

        dc.SetPen(pathPen);
        dc.DrawLine(start, *(it));

        dc.SetPen(positionPen);
        dc.DrawCircle(start, 1);
      }
    }
  }
}

Point PathShape::getCentre() const {
  vector<Point> pathPoints = getPath()->getPoints();

  uint64_t sumX = 0;
  uint64_t sumY = 0;
  for (const Point &point : pathPoints) {
    sumX += (uint64_t)point.x;
    sumY += (uint64_t)point.y;
  }

  int32_t centreX = (int32_t)(sumX / pathPoints.size());
  int32_t centreY = (int32_t)(sumY / pathPoints.size());

  return Point(centreX, centreY);
}

void PathShape::setCentre(const Point &point) {
  // This function has to be here because of the pure virtual function in class
  // Shape.
  LOG("cannot set center, all points are absolute.");
  // ??
}

Model::PathPtr PathShape::getPath() const {
  return dynamic_pointer_cast<Model::Path>(getModelObject());
}

void PathShape::handleNotification() {
  LOG("handle notification");
  cout << "handle notification" << endl;
}

} // End of namespace View