#include "Race.h"
#include <algorithm>
#include <iostream>

Race::Race(double distance, bool allowGround, bool allowAir)
    : distance(distance), allowGround(allowGround), allowAir(allowAir) {
}

bool Race::registerVehicle(Vehicle* vehicle) {
    if ((vehicle->getIsGround() && !allowGround) ||
        (!vehicle->getIsGround() && !allowAir)) {
        return false;
    }

    for (const auto& v : registeredVehicles) {
        if (v->getName() == vehicle->getName()) {
            return false;
        }
    }

    registeredVehicles.push_back(vehicle);
    return true;
}

bool Race::isVehicleRegistered(const std::string& name) const {
    for (const auto& v : registeredVehicles) {
        if (v->getName() == name) {
            return true;
        }
    }
    return false;
}

void Race::runRace() const {
    std::vector<std::pair<double, std::string>> results;

    for (const auto& vehicle : registeredVehicles) {
        results.emplace_back(vehicle->calculateTime(distance), vehicle->getName());
    }

    std::sort(results.begin(), results.end());

    std::cout << "\nРезультаты гонки:\n";
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << i + 1 << ". " << results[i].second
            << ": " << results[i].first << " ч\n";
    }
}

void Race::printRegisteredVehicles() const {
    if (registeredVehicles.empty()) {
        std::cout << "Нет";
        return;
    }

    for (size_t i = 0; i < registeredVehicles.size(); ++i) {
        if (i != 0) std::cout << ", ";
        std::cout << registeredVehicles[i]->getName();
    }
}

bool Race::hasEnoughParticipants() const {
    return registeredVehicles.size() >= 2;
}