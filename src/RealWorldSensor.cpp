/**
 * @file RealWorldSensor.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <chrono>

#include "MainApplication.hpp"
#include "RealWorldSensor.hpp"

using namespace std;

namespace Model {
RealWorldSensor::RealWorldSensor(float mean, float deviation)
    : normDistr(mean, deviation),
      randEngine(
          uint32_t(chrono::system_clock::now().time_since_epoch().count())) {}

float RealWorldSensor::addNoise(float value) {
  return value + normDistr(randEngine);
}

void RealWorldSensor::setStdDeviation(float deviation) {
  normDistr = normal_distribution<float>(normDistr.mean(), deviation);
}

void RealWorldSensor::readFromConfigFile(const string &sensor) {
  if (Application::MainApplication::isArgGiven(sensor)) {
    float stdDeviation =
        stod(Application::MainApplication::getArg(sensor).value);
    setStdDeviation(stdDeviation);
  }
}

} // namespace Model