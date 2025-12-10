cmake_minimum_required(VERSION 3.22.0)
project(RaceSimulator)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем библиотеку и приложение
add_subdirectory(RaceSimulatorLib)
add_subdirectory(RaceSimulatorApp)

target_compile_definitions(VehicleLib PRIVATE VEHICLE_EXPORTS)\
target_compile_definitions(AirVehicleLib PRIVATE AIRVEHICLE_EXPORTS)
target_compile_definitions(GroundVehicleLib PRIVATE GROUNDVEHICLE_EXPORTS)
target_compile_definitions(RaceLib PRIVATE RACE_EXPORTS)