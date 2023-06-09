/**
 * @file CompassSensor.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef COMPASSSENSOR_HPP
#define COMPASSSENSOR_HPP

#include "AbstractSensor.hpp"
#include "Config.hpp"
#include "RealWorldSensor.hpp"

using namespace std;

namespace Model {
// declaration of the robot class:
class Robot;
typedef shared_ptr<Robot> RobotPtr;

class CompassStimulus : public AbstractStimulus {
public:
  explicit CompassStimulus(double anOrientation) : orientation(anOrientation) {}

  string asString() override { return "CompassStimulus"; }

  double orientation;
};

class CompassPercept : public AbstractPercept {
public:
  explicit CompassPercept(double anOrientation) : orientation(anOrientation){};
  explicit CompassPercept(const CompassStimulus &pStimulus)
      : orientation(pStimulus.orientation) {}

  string asString() override { return "CompassPercept"; }

  double orientation;
};

class CompassSensor : public AbstractSensor, RealWorldSensor {
public:
  CompassSensor();

  explicit CompassSensor(Robot *pRobot); // explicit so that it can't be used as
                                         // implicit conversion

  ~CompassSensor() override = default;

  AbstractStimulusPtr getStimulus() const override;

  AbstractPerceptPtr getPerceptFor(AbstractStimulusPtr pStimulus) override;

  string asString() const override;

  string asDebugString() const override;

  // reset sensor standard deviation to configured value
  void recalibrate() override;
};
} // namespace Model

#endif // end of COMPASSSENSOR_HPP definition