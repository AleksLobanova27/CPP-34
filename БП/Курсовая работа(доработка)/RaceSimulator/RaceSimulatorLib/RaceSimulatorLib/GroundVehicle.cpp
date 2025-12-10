#include "GroundVehicle.h"

// Верблюд
Camel::Camel() : Vehicle("Верблюд", 10, true) {}

double Camel::calculateTime(double distance) const {
    const double driveTimeBeforeRest = 30.0;
    const double firstRest = 5.0;
    const double subsequentRest = 8.0;

    double totalTime = distance / speed;
    int restCount = static_cast<int>(totalTime / driveTimeBeforeRest);

    if (restCount > 0) {
        totalTime += firstRest + (restCount - 1) * subsequentRest;
    }

    return totalTime;
}

// Верблюд-быстроход
FastCamel::FastCamel() : Vehicle("Верблюд-быстроход", 40, true) {}

double FastCamel::calculateTime(double distance) const {
    const double driveTimeBeforeRest = 10.0;
    const double firstRest = 5.0;
    const double secondRest = 6.5;
    const double subsequentRest = 8.0;

    double totalTime = distance / speed;
    int restCount = static_cast<int>(totalTime / driveTimeBeforeRest);

    if (restCount > 0) {
        if (restCount == 1) {
            totalTime += firstRest;
        }
        else if (restCount == 2) {
            totalTime += firstRest + secondRest;
        }
        else {
            totalTime += firstRest + secondRest + (restCount - 2) * subsequentRest;
        }
    }

    return totalTime;
}

// Кентавр
Centaur::Centaur() : Vehicle("Кентавр", 15, true) {}

double Centaur::calculateTime(double distance) const {
    const double driveTimeBeforeRest = 8.0;
    const double restTime = 2.0;

    double totalTime = distance / speed;
    int restCount = static_cast<int>(totalTime / driveTimeBeforeRest);

    return totalTime + restCount * restTime;
}

// Ботинки-вездеходы
AllTerrainBoots::AllTerrainBoots() : Vehicle("Ботинки-вездеходы", 6, true) {}

double AllTerrainBoots::calculateTime(double distance) const {
    const double driveTimeBeforeRest = 60.0;
    const double firstRest = 10.0;
    const double subsequentRest = 5.0;

    double totalTime = distance / speed;
    int restCount = static_cast<int>(totalTime / driveTimeBeforeRest);

    if (restCount > 0) {
        totalTime += firstRest + (restCount - 1) * subsequentRest;
    }

    return totalTime;
}