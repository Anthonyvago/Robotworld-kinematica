/**
 * @file ParticleFilter.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PARTICLEFILTER_HPP
#define PARTICLEFILTER_HPP

#include "AbstractFilter.hpp"

#include <random>

using namespace std;

namespace Model {
typedef struct {
  Point location;
  double weight = 1;
} Particle;

class ParticleFilter : public AbstractFilter {
public:
  ParticleFilter();

  ~ParticleFilter() override = default;

  void iterate(Point &perceivedPos, const Point &destPos,
               vector<AbstractSensorPtr> &sensors) override;

  string asString() const override;

private:
  // FUNCTIONS:
  void initParticles();

  void controlUpdate(const Point &perceivedPos, const Point &destPos);

  void measurementUpdate(vector<AbstractSensorPtr> &sensors);

  void resampleParticles();

  Point calcNewPos();

  // VARIABLES:
  uint32_t gridSize;
  uint32_t numParticles;

  vector<Particle> particles;
  vector<double> weights;

  mt19937 randomEngine;
};
} // End of namespace Model

#endif // End of PARTICLEFILTER_HPP
