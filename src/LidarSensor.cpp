/**
 * @file LidarSensor.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "LidarSensor.hpp"
#include "MathUtils.hpp"
#include "Robot.hpp"
#include "Shape2DUtils.hpp"

#include "RobotWorld.hpp"
#include "Wall.hpp"
#include "Widgets.hpp"

#include "MainApplication.hpp"

using namespace std;

namespace Model {
LidarSensor::LidarSensor() : RealWorldSensor(0, 10) { recalibrate(); }

LidarSensor::LidarSensor(Robot *robot)
    : AbstractSensor(robot), RealWorldSensor(0, 10) {
  recalibrate();
}

AbstractStimulusPtr LidarSensor::getStimulus() const {
  double currentAngle =
      Utils::Shape2DUtils::getAngle(dynamic_cast<Robot *>(agent)->getFront());
  Point currentPosition = dynamic_cast<Robot *>(agent)->getPosition();

  LidarData data = getReadingFromLocation(currentPosition, currentAngle);

  return AbstractStimulusPtr(new LidarStimulus(data));
}

AbstractPerceptPtr LidarSensor::getPerceptFor(AbstractStimulusPtr aStimulus) {
  auto *stimulus = dynamic_cast<LidarStimulus *>(aStimulus.get());

  for (LidarMeasurement &reading : stimulus->measurements) {
    reading.distance = addNoise(reading.distance);
  }

  return AbstractPerceptPtr(new LidarPercept(*stimulus));
}

LidarData LidarSensor::getReadingFromLocation(const Point &robotLocation,
                                              double robotOrientationAngle) {
  LidarData data;

  for (uint8_t i = 0; i < LidarSensorFOV; ++i) {
    const double angleInRadians =
        Utils::MathUtils::toRadians((robotOrientationAngle + (2 * i)));
    double minMeasuredDistance = 1500; // numeric_limits<double>::max();

    const Point BEAM_END_POINT(
        static_cast<int32_t>(robotLocation.x +
                             minMeasuredDistance * cos(angleInRadians)),
        static_cast<int32_t>(robotLocation.y +
                             minMeasuredDistance * sin(angleInRadians)));

    // Check for collision beam with all walls:
    for (const WallPtr &wall : Model::RobotWorld::getRobotWorld().getWalls()) {
      Point beamIntersection = Utils::Shape2DUtils::getIntersection(
          robotLocation, BEAM_END_POINT, wall->getPoint1(), wall->getPoint2());
      if (beamIntersection != DefaultPosition) {
        const double measuredDistanceX =
            pow(robotLocation.x - beamIntersection.x, 2);
        const double measuredDistanceY =
            pow(robotLocation.y - beamIntersection.y, 2);
        const double measuredDistance =
            sqrt(measuredDistanceX + measuredDistanceY);

        minMeasuredDistance = min(minMeasuredDistance, measuredDistance);
      }
    }
    data[i] = LidarMeasurement{Utils::MathUtils::toDegrees(angleInRadians),
                               minMeasuredDistance};
  }
  return data;
}

string LidarSensor::asString() const { return "LidarSensor"; }

string LidarSensor::asDebugString() const { return asString(); }

void LidarSensor::recalibrate() { readFromConfigFile("-lidarStdDeviation"); }
} // namespace Model