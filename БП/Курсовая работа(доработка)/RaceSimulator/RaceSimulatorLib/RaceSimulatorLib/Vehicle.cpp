#include "Vehicle.h"

Vehicle::Vehicle(const std::string& name, double speed, bool isGround)
    : name(name), speed(speed), isGround(isGround) {
}

std::string Vehicle::getName() const {
    return name;
}

double Vehicle::getSpeed() const {
    return speed;
}

bool Vehicle::getIsGround() const {
    return isGround;
}