/**
 * @file OdometerSensor.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ODOMETERSENSOR_HPP
#define ODOMETERSENSOR_HPP

#include "AbstractSensor.hpp"
#include "Point.hpp"
#include "RealWorldSensor.hpp"

using namespace std;

namespace Model {
class Robot;
typedef shared_ptr<Robot> RobotPtr;

class OdometerStimulus : public AbstractStimulus {
public:
  OdometerStimulus(Point currentPos, double pDistanceTravelled)
      : curPos(currentPos), distanceTravelled(pDistanceTravelled) {}

  string asString() override { return "OdometerStimulus"; }

  Point curPos;
  double distanceTravelled;
};

class OdometerPercept : public AbstractPercept {
public:
  explicit OdometerPercept(double pDistanceTravelled)
      : distanceTravelled(pDistanceTravelled) {}

  explicit OdometerPercept(const OdometerStimulus &pStimulus)
      : distanceTravelled(pStimulus.distanceTravelled) {}

  string asString() override { return "OdometerPercept"; }

  double distanceTravelled;
};

class OdometerSensor : public AbstractSensor, RealWorldSensor {
public:
  OdometerSensor();

  explicit OdometerSensor(Robot *robot);

  ~OdometerSensor() override = default;

  AbstractStimulusPtr getStimulus() const override;

  AbstractPerceptPtr getPerceptFor(AbstractStimulusPtr pStimulus) override;

  string asString() const override;

  string asDebugString() const override;

  // Reset sensor standard deviation to configured value
  void recalibrate() override;

private:
  Point prevPos;
};
} // namespace Model

#endif // End of ODOMETERSENSOR_HPP definition
