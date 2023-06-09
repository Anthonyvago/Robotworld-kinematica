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

#include "AbstractFilter.hpp"

using namespace std;

namespace Model {
AbstractFilter::AbstractFilter(eFilterType aFilterType)
    : filterType(aFilterType) {}

eFilterType AbstractFilter::getFilterType() const { return filterType; }

string AbstractFilter::asDebugString() const { return asString(); }

bool AbstractFilter::operator==(const AbstractFilter &other) const {
  return other.filterType == filterType;
}
} // namespace Model