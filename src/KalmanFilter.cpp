/**
 * @file KalmanFilter.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "KalmanFilter.hpp"

#include "CompassSensor.hpp"
#include "Logger.hpp"
#include "OdometerSensor.hpp"

#include <cmath>

using namespace std;

namespace Model {
KalmanFilter::KalmanFilter()
    : AbstractFilter(eFilterType::KALMAN_FILTER),
      belief(Utils::Matrix<double, 2, 1>{0.0, 0.0}),
      error(Utils::Matrix<double, 2, 2>{{100, 0}, {0, 100}}) {}

KalmanFilter::KalmanFilter(const Point &aInitialPosition)
    : AbstractFilter(eFilterType::KALMAN_FILTER),
      belief(Utils::Matrix<double, 2, 1>{(double)aInitialPosition.x,
                                         (double)aInitialPosition.y}),
      error(Utils::Matrix<double, 2, 2>{{100, 0}, {0, 100}}) {}

void KalmanFilter::iterate(Point &perceivedPos, const Point &destPos,
                           vector<AbstractSensorPtr> &sensors) {
  Point measuredPos = getMeasuredPosition(perceivedPos, sensors);

  // control:
  Utils::Matrix<double, 2, 1> control = {
      (double)destPos.x - (double)perceivedPos.x,
      (double)destPos.y - (double)perceivedPos.y};
  // measurement
  Utils::Matrix<double, 2, 1> measured = {(double)measuredPos.x,
                                          (double)measuredPos.y};

  // CONTROL UPDATE:
  // predicted state:
  Utils::Matrix<double, 2, 1> PSV =
      (A * belief) + (A /*B*/ * control); // + predicted process noise
  // predicted process covariance:
  Utils::Matrix<double, 2, 2> PPC =
      A * error * A /*A^T*/; // + process noise covariance

  // kalman gain:
  Utils::Matrix<double, 2, 2> KG =
      (PPC * A /*C*/) * (A /*C*/ * PPC * A /*C^T*/ + R).inverse();

  // MEASUREMENT UPDATE:
  // adjusted state:
  belief = PSV + KG * (measured - A /*C*/ * PSV);
  // adjusted process covariance:
  error = PPC * (A /*I*/ - KG * A /*C*/);

  perceivedPos =
      Point((int32_t)round(belief[0][0]), (int32_t)round(belief[1][0]));
}

string KalmanFilter::asString() const { return "KalmanFilter"; }

Point KalmanFilter::getMeasuredPosition(const Point &robotPos,
                                        vector<AbstractSensorPtr> &sensors) {
  double distance = numeric_limits<double>::max();
  double orientation = numeric_limits<double>::max();

  for (AbstractSensorPtr &sensor : sensors) {
    if (sensor.get()->asString() == "CompassSensor") {
      CompassSensor *compass = dynamic_cast<CompassSensor *>(sensor.get());
      shared_ptr<AbstractStimulus> stimulus = compass->getStimulus();
      shared_ptr<AbstractPercept> percept = compass->getPerceptFor(stimulus);

      orientation = dynamic_cast<CompassPercept *>(percept.get())->orientation;
    } else if (sensor.get()->asString() == "OdometerSensor") {
      OdometerSensor *odometer = dynamic_cast<OdometerSensor *>(sensor.get());
      shared_ptr<AbstractStimulus> stimulus = odometer->getStimulus();
      shared_ptr<AbstractPercept> percept = odometer->getPerceptFor(stimulus);

      distance =
          dynamic_cast<OdometerPercept *>(percept.get())->distanceTravelled;
    }
  }

  if (distance == numeric_limits<double>::max() ||
      orientation == numeric_limits<double>::max()) {
    LOG("Error occurred while retrieving sensor percepts!");
    cerr << "Error occurred while retrieving sensor percepts!" << endl;
    return Point(0, 0);
  }

  int32_t posX = (int32_t)round(distance * cos(orientation) + robotPos.x);
  int32_t posY = (int32_t)round(distance * sin(orientation) + robotPos.y);

  return Point(posX, posY);
}
} // End of namespace Model
