#pragma once
#include <iostream>
#include <string>
#include <vector>
#ifdef  VEHICLE_EXPORTS
#define VEHICLE_API __declspec(dllexport)
#else
#define VEHICLE_API __declspec(dllimport)
#endif
class Vehicle {
protected:
    std::string name;
    double speed;
    bool isGround;

public:
    Vehicle(const std::string& name, double speed, bool isGround);
    virtual ~Vehicle() = default;

    virtual double calculateTime(double distance) const = 0;

    std::string getName() const;
    double getSpeed() const;
    bool getIsGround() const;
};