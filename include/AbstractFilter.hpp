/**
 * @file AbstractFilter.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include <memory>
#include <vector>

#include "Point.hpp"

using namespace std;

namespace Model {
class AbstractSensor;
typedef shared_ptr<AbstractSensor> AbstractSensorPtr;

enum class eFilterType { KALMAN_FILTER, PARTICLE_FILTER };

class AbstractFilter {
public:
  explicit AbstractFilter(eFilterType aFilterType);

  virtual ~AbstractFilter() = default;

  virtual void iterate(Point &perceivedPosition, const Point &destPos,
                       vector<AbstractSensorPtr> &sensors) = 0;

  virtual string asString() const = 0;

  virtual string asDebugString() const;

  bool operator==(const AbstractFilter &other) const;

  eFilterType getFilterType() const;

protected:
  eFilterType filterType;
};
} // End of namespace Model

#endif // End of ABSTRACTFILTER_H
