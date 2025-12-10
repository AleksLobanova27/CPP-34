#include "AirVehicle.h"

// Ковёр-самолёт
MagicCarpet::MagicCarpet() : Vehicle("Ковёр-самолёт", 10, false) {}

double MagicCarpet::calculateTime(double distance) const {
    double reduction = 0.0;

    if (distance < 1000) {
        reduction = 0.0;
    }
    else if (distance < 5000) {
        reduction = 0.03;
    }
    else if (distance < 10000) {
        reduction = 0.10;
    }
    else {
        reduction = 0.05;
    }

    return distance * (1 - reduction) / speed;
}

// Орёл
Eagle::Eagle() : Vehicle("Орёл", 8, false) {}

double Eagle::calculateTime(double distance) const {
    const double reduction = 0.06;
    return distance * (1 - reduction) / speed;
}

// Метла
Broom::Broom() : Vehicle("Метла", 20, false) {}

double Broom::calculateTime(double distance) const {
    double reduction = 0.01 * floor(distance / 1000);
    return distance * (1 - reduction) / speed;
}