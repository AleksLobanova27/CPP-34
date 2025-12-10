#pragma once
#include "Vehicle.h"
#ifdef  GROUNDVEHICLE_EXPORTS
#define GROUNDVEHICLE_API __declspec(dllexport)
#else
#define GROUNDVEHICLE_API __declspec(dllimport)
#endif
class Camel : public Vehicle {
public:
    Camel();
    double calculateTime(double distance) const override;
};

class FastCamel : public Vehicle {
public:
    FastCamel();
    double calculateTime(double distance) const override;
};

class Centaur : public Vehicle {
public:
    Centaur();
    double calculateTime(double distance) const override;
};

class AllTerrainBoots : public Vehicle {
public:
    AllTerrainBoots();
    double calculateTime(double distance) const override;
};