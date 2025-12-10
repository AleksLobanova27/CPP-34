#pragma once
#include <vector>
#include <memory>
#include "Vehicle.h"

#ifdef RACE_EXPORTS
#define RACE_API __declspec(dllexport)
#else
#define RACE_API __declspec(dllimport)
#endif
class Race {
private:
    std::vector<Vehicle*> registeredVehicles;
    double distance;
    bool allowGround;
    bool allowAir;

public:
    Race(double distance, bool allowGround, bool allowAir);

    bool registerVehicle(Vehicle* vehicle);
    bool isVehicleRegistered(const std::string& name) const;
    void runRace() const;
    void printRegisteredVehicles() const;
    bool hasEnoughParticipants() const;

    double getDistance() const { return distance; }
    bool getAllowGround() const { return allowGround; }
    bool getAllowAir() const { return allowAir; }
};