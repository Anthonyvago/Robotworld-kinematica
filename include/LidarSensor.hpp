/**
 * @file LidarSensor.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LIDARSENSOR_HPP
#define LIDARSENSOR_HPP

#include "AbstractSensor.hpp"
#include "Point.hpp"
#include "RealWorldSensor.hpp"

using namespace std;

#define LidarSensorFOV 180

namespace Model {
// Decleration of robot class:
class Robot;
typedef shared_ptr<Robot> RobotPtr;

struct LidarMeasurement {
  double angle = 0, distance = 0;
};
typedef array<LidarMeasurement, LidarSensorFOV> LidarData;

class LidarStimulus : public AbstractStimulus {
public:
  explicit LidarStimulus(const LidarData &lidarData)
      : measurements(lidarData) {}

  string asString() override { return "LidarStimulus"; }

  LidarData measurements;
};

class LidarPercept : public AbstractPercept {
public:
  explicit LidarPercept(const LidarData &lidarData) : measurements(lidarData) {}

  explicit LidarPercept(const LidarStimulus &stimulus)
      : measurements(stimulus.measurements) {}

  string asString() override { return "LidarPercept"; }

  LidarData measurements;
};

class LidarSensor : public AbstractSensor, RealWorldSensor {
public:
  LidarSensor();

  explicit LidarSensor(Robot *robot);

  ~LidarSensor() override = default;

  AbstractStimulusPtr getStimulus() const override;

  AbstractPerceptPtr getPerceptFor(AbstractStimulusPtr pStimulus) override;

  static LidarData getReadingFromLocation(const Point &robotLocation,
                                          double robotOrientationAngle);

  string asString() const override;

  string asDebugString() const override;

  // reset standard deviation to configured value
  void recalibrate() override;
};
} // namespace Model

#endif // End of LIDARSENSOR_HPP definition
