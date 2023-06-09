/**
 * @file ParticleFilter.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "ParticleFilter.hpp"

#include "MainApplication.hpp"

#include "CompassSensor.hpp"
#include "LidarSensor.hpp"

#include "Logger.hpp"
#include "MathUtils.hpp"

#include <chrono>

using namespace std;

namespace Model {
ParticleFilter::ParticleFilter()
    : AbstractFilter(eFilterType::PARTICLE_FILTER), gridSize(32),
      numParticles(gridSize * gridSize) {
  if (Application::MainApplication::isArgGiven("-particles")) {
    gridSize =
        (int32_t)stoi(Application::MainApplication::getArg("-particles").value);
    numParticles = gridSize * gridSize;
  }

  random_device randomDevice;
  randomEngine = mt19937(randomDevice());

  initParticles();
}

void ParticleFilter::initParticles() {
  uniform_int_distribution<uint8_t> distribution(
      0, static_cast<uint8_t>(gridSize));
  uint32_t stepSize = 1024 / gridSize;

  for (size_t i = 0; i < numParticles; ++i) {
    // Set all weights to default value:
    weights.emplace_back(1);

    // Set all locations to random locations:
    int32_t locationX =
        (int32_t)stepSize * (int32_t)round(distribution(randomEngine));
    int32_t locationY =
        (int32_t)stepSize * (int32_t)round(distribution(randomEngine));

    // Create the particle:
    Particle particle = {Point(locationX, locationY), weights[i]};

    // Add the particle to the vector:
    particles.emplace_back(particle);
  }
}

void ParticleFilter::iterate(Point &perceivedPos, const Point &destPos,
                             vector<AbstractSensorPtr> &sensors) {
  // First, do the control update:
  controlUpdate(perceivedPos, destPos);

  // Secondly do the measurement update:
  measurementUpdate(sensors);

  // Thirdly, resample the particles:
  resampleParticles();

  // Fourthly, calculate the new position:
  perceivedPos = calcNewPos();
}

void ParticleFilter::controlUpdate(const Point &perceivedPos,
                                   const Point &destPos) {
  uint8_t stdDeviation = 2;
  normal_distribution<double> distribution(0, stdDeviation);

  // Calculate the relative movement:
  int32_t relativeMovementX = (int32_t)(destPos.x - perceivedPos.x) +
                              (int32_t)distribution(randomEngine);
  int32_t relativeMovementY = (int32_t)(destPos.y - perceivedPos.y) +
                              (int32_t)distribution(randomEngine);

  // Update the particles:
  for (Particle &particle : particles) {
    particle.location += Point(relativeMovementX, relativeMovementY);
  }
}

void ParticleFilter::measurementUpdate(vector<AbstractSensorPtr> &sensors) {
  double orientation;
  LidarData lidarDataRobot;

  for (AbstractSensorPtr &sensor : sensors) {
    if (sensor.get()->asString() == "CompassSensor") {
      CompassSensor *compass = dynamic_cast<CompassSensor *>(sensor.get());
      shared_ptr<AbstractStimulus> stimulus = compass->getStimulus();
      shared_ptr<AbstractPercept> percept = compass->getPerceptFor(stimulus);

      orientation = dynamic_cast<CompassPercept *>(percept.get())->orientation;
    } else if (sensor.get()->asString() == "LidarSensor") {
      LidarSensor *odometer = dynamic_cast<LidarSensor *>(sensor.get());
      shared_ptr<AbstractStimulus> stimulus = odometer->getStimulus();
      shared_ptr<AbstractPercept> percept = odometer->getPerceptFor(stimulus);

      lidarDataRobot =
          dynamic_cast<LidarPercept *>(percept.get())->measurements;
    }
  }

  for (size_t i = 0; i < particles.size(); ++i) // x32^2
  {
    LidarData lidarDataParticle = LidarSensor::getReadingFromLocation(
        particles[i].location, orientation); // 180 readings

    double totalDistanceDelta = 0;
    for (size_t j = 0; j < lidarDataRobot.size(); ++j) // x180
    {
      totalDistanceDelta +=
          abs(lidarDataRobot[j].distance - lidarDataParticle[j].distance);
    }

    double newWeight = (totalDistanceDelta > Utils::ALMOST_ZERO)
                           ? (1.0 / totalDistanceDelta)
                           : 1;
    particles[i].weight = weights[i] = newWeight;
  } // total of 184320 readings taken and compared per iteration. (approx 100
    // ms)
}

void ParticleFilter::resampleParticles() {
  decltype(particles) selectedParticles;
  discrete_distribution<uint16_t> discreteDistribution(weights.begin(),
                                                       weights.end());

  for (size_t i = 0; i < numParticles; ++i) {
    selectedParticles.emplace_back(
        particles[discreteDistribution(randomEngine)]);
  }
  particles = selectedParticles;
}

Point ParticleFilter::calcNewPos() {
  Particle bestParticle;
  double highestWeight = 0;

  // for_each(particles.begin(), particles.end(), [&bestParticle,
  // &greatestWeight](const Particle& particle) {
  //     if (particle.weight > greatestWeight)
  //     {
  //         greatestWeight = particle.weight;
  //         bestParticle = particle;
  //     }
  // });

  for (Particle &particle : particles) {
    if (particle.weight > highestWeight) {
      highestWeight = particle.weight;
      bestParticle = particle;
    }
  }

  return bestParticle.location;
}

string ParticleFilter::asString() const { return "ParticleFilter"; }

} // End of namespace Model