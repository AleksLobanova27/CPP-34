#pragma once
#include "Vehicle.h"
#ifdef  AIRVEHICLE_EXPORTS
#define AIRVEHICLE_API __declspec(dllexport)
#else
#define AIRVEHICLE_API __declspec(dllimport)
#endif
class MagicCarpet : public Vehicle {
public:
    MagicCarpet();
    double calculateTime(double distance) const override;
};

class Eagle : public Vehicle {
public:
    Eagle();
    double calculateTime(double distance) const override;
};

class Broom : public Vehicle {
public:
    Broom();
    double calculateTime(double distance) const override;
};