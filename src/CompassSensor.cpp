/**
 * @file CompassSensor.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "CompassSensor.hpp"
#include "MainApplication.hpp"
#include "Robot.hpp"
#include "Shape2DUtils.hpp"

using namespace std;

namespace Model {
CompassSensor::CompassSensor()
    : RealWorldSensor(0, Utils::MathUtils::toRadians(2)) {
  recalibrate();
}

CompassSensor::CompassSensor(Robot *pRobot)
    : AbstractSensor(pRobot),
      RealWorldSensor(0, Utils::MathUtils::toRadians(2)) {
  recalibrate();
}

AbstractStimulusPtr CompassSensor::getStimulus() const {
  double orientation =
      Utils::Shape2DUtils::getAngle(dynamic_cast<Robot *>(agent)->getFront());
  AbstractStimulusPtr stimulus(new CompassStimulus(orientation));

  return stimulus;
}

AbstractPerceptPtr CompassSensor::getPerceptFor(AbstractStimulusPtr pStimulus) {
  auto *stimulus = dynamic_cast<CompassStimulus *>(pStimulus.get());

  stimulus->orientation = addNoise(stimulus->orientation);

  return AbstractPerceptPtr(new CompassPercept(*stimulus));
}

string CompassSensor::asString() const { return "CompassSensor"; }

string CompassSensor::asDebugString() const { return asString(); }

void CompassSensor::recalibrate() {
  readFromConfigFile("-compassStdDeviation");
}
} // namespace Model