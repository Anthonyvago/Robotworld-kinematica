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

#include "OdometerSensor.hpp"
#include "Robot.hpp"

#include "MainApplication.hpp"

using namespace std;

namespace Model {
OdometerSensor::OdometerSensor() : RealWorldSensor(0, 1), prevPos(0, 0) {
  recalibrate();
}

OdometerSensor::OdometerSensor(Robot *robot)
    : AbstractSensor(robot), RealWorldSensor(0, 1),
      prevPos(robot->getPosition()) {
  recalibrate();
}

AbstractStimulusPtr OdometerSensor::getStimulus() const {
  Point robotPos = dynamic_cast<Robot *>(agent)->getPosition();

  double distanceX = prevPos.x - robotPos.x;
  double distanceY = prevPos.y - robotPos.y;

  double distance = (sqrt(pow(distanceX, 2) + pow(distanceY, 2)));

  return AbstractStimulusPtr(
      new OdometerStimulus(/*prevPos,*/ robotPos, distance));
}

AbstractPerceptPtr
OdometerSensor::getPerceptFor(AbstractStimulusPtr pStimulus) {
  auto *stimulus = dynamic_cast<OdometerStimulus *>(pStimulus.get());

  prevPos = stimulus->curPos;
  stimulus->distanceTravelled +=
      (addNoise(0) * stimulus->distanceTravelled / 10);

  return AbstractPerceptPtr(new OdometerPercept(*stimulus));
}

string OdometerSensor::asString() const { return "OdometerSensor"; }

string OdometerSensor::asDebugString() const { return asString(); }

void OdometerSensor::recalibrate() {
  readFromConfigFile("-odometerStdDeviation");
}

} // namespace Model