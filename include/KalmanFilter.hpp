/**
 * @file KalmanFilter.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef KALMANFILTER_HPP
#define KALMANFILTER_HPP

#include "AbstractFilter.hpp"
#include "Matrix.hpp"

using namespace std;

namespace Model {
class KalmanFilter : public AbstractFilter {
public:
  KalmanFilter();

  explicit KalmanFilter(const Point &aInitialPosition);

  ~KalmanFilter() override = default;

  // One execution equals one iteration:
  void iterate(Point &perceivedPos, const Point &destPos,
               vector<AbstractSensorPtr> &sensors) override;

  string asString() const override;

private:
  // To calculate measured position from sensors:
  Point getMeasuredPosition(const Point &robotPos,
                            vector<AbstractSensorPtr> &sensors);

private:
  Utils::Matrix<double, 2, 2> error;  // previous process covariance
  Utils::Matrix<double, 2, 1> belief; // previous state vector

  const Utils::Matrix<double, 2, 2> R = {{1, 0},
                                         {0, 1}}; // sensor covariance matrix
  const Utils::Matrix<double, 2, 2> A = {{1, 0}, {0, 1}};
};
} // End of namespace Model

#endif // End of KALMANFILTER_HPP
