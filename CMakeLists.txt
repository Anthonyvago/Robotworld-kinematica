cmake_minimum_required(VERSION 3.16)
project(Kinematica_assignment)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(Boost_USE_MULTITHREADED TRUE)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(wxWidgets REQUIRED)

include(${wxWidgets_USE_FILE})

include_directories(src/)
include_directories(include/)

set(EXE kinematica)

set(HEADERS_CONFIG
        include/config.h.in
        include/Config.hpp
)
set(HEADERS_APPLICATION
        include/Button.hpp
        include/CommandlineArgument.hpp
        include/CommunicationService.hpp
        include/Logger.hpp
        include/LogTextCtrl.hpp
        include/MainApplication.hpp
        include/MainFrameWindow.hpp
        include/WidgetTraceFunction.hpp
        # From here on are the new files for this assigment:
        include/ButtonToggle.hpp
        include/Slider.hpp
)
set(HEADERS_BASE
        include/FileTraceFunction.hpp
        include/ITraceFunction.hpp
        include/NotificationEvent.hpp
        include/NotificationHandler.hpp
        include/Notifier.hpp
        include/ObjectId.hpp
        include/Observer.hpp
        include/Queue.hpp
        include/StdOutTraceFunction.hpp
        include/Trace.hpp
        include/NotificationFunctionTypeTraits.hpp
)
set(HEADERS_MESSAGING
        include/Client.hpp
        include/Message.hpp
        include/MessageHandler.hpp
        include/MessageTypes.hpp
        include/Server.hpp
        include/Session.hpp
)
set(HEADERS_MODEL
        include/AbstractActuator.hpp
        include/AbstractAgent.hpp
        include/AbstractSensor.hpp
        include/BoundedVector.hpp
        include/Goal.hpp
        include/LaserDistanceSensor.hpp
        include/ModelObject.hpp
        include/Robot.hpp
        include/RobotWorld.hpp
        include/SteeringActuator.hpp
        include/Wall.hpp
        include/WayPoint.hpp
        include/CompassSensor.hpp
        include/RealWorldSensor.hpp
        include/OdometerSensor.hpp
        include/LidarSensor.hpp
        include/AbstractFilter.hpp
        include/Path.hpp
        include/KalmanFilter.hpp
        include/ParticleFilter.hpp
)
set(HEADERS_PATH_ALGORITHM
        include/AStar.hpp)
set(HEADERS_VIEW
        include/GoalShape.hpp
        include/LineShape.hpp
        include/RectangleShape.hpp
        include/RobotShape.hpp
        include/RobotWorldCanvas.hpp
        include/Shape.hpp
        include/ViewObject.hpp
        include/WallShape.hpp
        include/WayPointShape.hpp
        # From here on are the new files for this assigment:
        include/PathShape.hpp
)
set(HEADERS_UTILS
        include/MathUtils.hpp
        include/Shape2DUtils.hpp
        include/TimeStamp.hpp
        include/TypeInfo.hpp
        # From here on are the new files for this assigment:
        include/Matrix.hpp
        include/FileIO.hpp
        include/StringUtils.hpp
)
set(HEADERS_WIDGETS
        include/Point.hpp
        include/Region.hpp
        include/Size.hpp
        include/Widgets.hpp
)

set(HEADERS
        ${HEADERS_APPLICATION}
        ${HEADERS_BASE}
        ${HEADERS_CONFIG}
        ${HEADERS_MESSAGING}
        ${HEADERS_MODEL}
        ${HEADERS_PATH_ALGORITHM}
        ${HEADERS_UTILS}
        ${HEADERS_VIEW}
        ${HEADERS_WIDGETS})

set(SOURCES
        src/AbstractActuator.cpp
        src/AbstractAgent.cpp
        src/AbstractSensor.cpp
        src/AStar.cpp
        src/BoundedVector.cpp
        src/CommunicationService.cpp
        src/FileTraceFunction.cpp
        src/Goal.cpp
        src/GoalShape.cpp
        src/LaserDistanceSensor.cpp
        src/LineShape.cpp
        src/Logger.cpp
        src/LogTextCtrl.cpp
        src/Main.cpp
        src/MainApplication.cpp
        src/MainFrameWindow.cpp
        src/MathUtils.cpp
        src/ModelObject.cpp
        src/NotificationHandler.cpp
        src/Notifier.cpp
        src/ObjectId.cpp
        src/Observer.cpp
        src/RectangleShape.cpp
        src/Robot.cpp
        src/RobotShape.cpp
        src/RobotWorld.cpp
        src/RobotWorldCanvas.cpp
        src/Server.cpp
        src/Shape2DUtils.cpp
        src/StdOutTraceFunction.cpp
        src/SteeringActuator.cpp
        src/Trace.cpp
        src/ViewObject.cpp
        src/Wall.cpp
        src/WallShape.cpp
        src/WayPoint.cpp
        src/WayPointShape.cpp
        src/Widgets.cpp
        src/WidgetTraceFunction.cpp
        # From here on are the new files for this assigment:
        src/CompassSensor.cpp
        src/RealWorldSensor.cpp
        src/OdometerSensor.cpp
        src/LidarSensor.cpp
        src/AbstractFilter.cpp
        src/Path.cpp
        src/Matrix.inc
        src/KalmanFilter.cpp
        src/ParticleFilter.cpp
        # src/NotificationFunctionTypeTraits.cpp
        src/FileIO.cpp
        src/PathShape.cpp
        src/StringUtils.cpp
        
)

add_executable(${EXE} ${SOURCES} ${HEADERS})

target_link_libraries(${EXE} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${EXE} ${wxWidgets_LIBRARIES})
target_link_libraries(${EXE} ${Boost_LIBRARIES})

install(TARGETS ${EXE} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR})
