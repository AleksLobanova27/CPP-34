project(RaceSimulatorLib)

# Заголовочные файлы
set(HEADERS 
    Vehicle.h
    GroundVehicle.h
    AirVehicle.h
    Race.h
)

# Исходные файлы
set(SOURCES
    Vehicle.cpp
    GroundVehicle.cpp
    AirVehicle.cpp
    Race.cpp
)
add_library(RaceSimulatorLib SHARED 
    Vehicle.h Vehicle.cpp 
    GroundVehicle.h GroundVehicle.cpp 
    AirVehicle.h AirVehicle.cpp 
    Race.h Race.cpp 
)

target_link_libraries(RaceSimulator RaceSimulatorLib)