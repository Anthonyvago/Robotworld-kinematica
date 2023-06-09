/**
 * @file PathShape.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PATHSHAPE_HPP
#define PATHSHAPE_HPP

#include "Path.hpp"
#include "Shape.hpp"

namespace View {
class PathShape : public Shape {
public:
  explicit PathShape(const Model::PathPtr &path);

  ~PathShape() override = default;

  bool occupies(const Point &point) const override;

  void draw(wxDC &dc) override;

  Point getCentre() const override;

  void setCentre(const Point &point) override;

  Model::PathPtr getPath() const;

  void handleNotification() override;
};
} // End of namespace View

#endif // End of PATHSHAPE_HPP
