/**
 * @file RealWorldSensor.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef REALWORLDSENSOR_HPP
#define REALWORLDSENSOR_HPP

#include <random>

using namespace std;

namespace Model {
class RealWorldSensor {
public:
  RealWorldSensor(float mean, float deviation);

  virtual ~RealWorldSensor() = default;

protected:
  // Add noise to sensor val:
  float addNoise(float value);

  void setStdDeviation(float aDeviation);

  void readFromConfigFile(const string &sensor);

private:
  normal_distribution<float> normDistr;
  default_random_engine randEngine;
};
} // namespace Model

#endif // End of REALWORLDSENSOR_HPP definition
