/**
 * @file SteeringActuator.cpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SteeringActuator.hpp"
#include "Robot.hpp"

namespace Model {
SteeringActuator::SteeringActuator()
    : generator(uint32_t(
          std::chrono::system_clock::now().time_since_epoch().count())) {}
SteeringActuator::SteeringActuator(Robot *robot)
    : AbstractActuator(robot),
      generator(uint32_t(
          std::chrono::system_clock::now().time_since_epoch().count())) {}
void SteeringActuator::handleCommand(AbstractCommand &anAbstractCommand) {
  auto *command = dynamic_cast<RelativeMovementCommand *>(&anAbstractCommand);
  std::uniform_real_distribution realDistribution(0.f, 1.f);

  Point actualPosition;
  if (realDistribution(generator) <= 0.7) {
    std::uniform_int_distribution distribution(-1, 1);
    actualPosition.x =
        command->relativePositionRequest.x + distribution(generator);
    actualPosition.y =
        command->relativePositionRequest.y + distribution(generator);
  } else {
    typedef Point P;
    const uint16_t nPossiblePositions = 16;
    std::array<Point, nPossiblePositions> targetList = {
        P(-2, -2), P(-1, -2), P(0, -2), P(1, -2), P(2, -2), P(-2, -1),
        P(2, -1),  P(-2, 0),  P(2, 0),  P(-2, 1), P(2, 1),  P(-2, 2),
        P(-1, 2),  P(0, 2),   P(1, 2),  P(2, 2),
    };

    std::uniform_int_distribution distribution(0ul, targetList.size() - 1);
    Point offsetPoint = targetList[distribution(generator)];
    actualPosition.x = command->relativePositionRequest.x + offsetPoint.x;
    actualPosition.y = command->relativePositionRequest.y + offsetPoint.y;
  }
  command->relativePositionRequest =
      actualPosition; // + dynamic_cast<Robot*>(agent)->getPosition();
}
std::string SteeringActuator::asString() const { return "SteeringActuator"; }
std::string SteeringActuator::asDebugString() const { return asString(); }
} // namespace Model
