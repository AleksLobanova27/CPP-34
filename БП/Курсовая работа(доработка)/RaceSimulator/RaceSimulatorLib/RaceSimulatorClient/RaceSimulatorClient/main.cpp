#include <iostream>
#include <memory>
#include <vector>
#include "Vehicle.h"
#include "GroundVehicle.h"
#include "AirVehicle.h"
#include "Race.h"

void printMainMenu() {
    std::cout << "\n=== Гоночный симулятор ===";
    std::cout << "\n1. Гонка для наземного транспорта";
    std::cout << "\n2. Гонка для воздушного транспорта";
    std::cout << "\n3. Гонка для всех типов транспорта";
    std::cout << "\n0. Выход";
    std::cout << "\nВыберите тип гонки: ";
}

void printRaceMenu(const Race& race) {
    std::cout << "\n=== Гонка ===";
    std::cout << "\nТип: " << (race.getAllowGround() ? "Наземная" : "")
        << (race.getAllowAir() ? " Воздушная" : "");
    std::cout << "\nДистанция: " << race.getDistance() << " км";
    std::cout << "\nЗарегистрированные ТС: ";
    race.printRegisteredVehicles();
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаём все доступные ТС
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    vehicles.push_back(std::make_unique<Camel>());
    vehicles.push_back(std::make_unique<FastCamel>());
    vehicles.push_back(std::make_unique<Centaur>());
    vehicles.push_back(std::make_unique<AllTerrainBoots>());
    vehicles.push_back(std::make_unique<MagicCarpet>());
    vehicles.push_back(std::make_unique<Eagle>());
    vehicles.push_back(std::make_unique<Broom>());

    while (true) {
        printMainMenu();
        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        double distance;
        std::cout << "Укажите длину дистанции (Должна быть положительной): ";
        std::cin >> distance;

        Race race(distance, (choice == 1 || choice == 3),(choice == 2 || choice == 3));

        // Регистрация ТС
        while (true) {
            printRaceMenu(race);
            std::cout << "\n1. Зарегистрировать ТС\n2. Начать гонку\nВыберите действие: ";
            int action;
            std::cin >> action;

            if (action == 2) {
                if (race.hasEnoughParticipants()) {
                    race.runRace();
                    break;
                }
                else {
                    std::cout << "Недостаточно участников! Нужно минимум 2.\n";
                }
            }
            else {
                // Вывод списка доступных ТС
                for (size_t i = 0; i < vehicles.size(); ++i) {
                    std::cout << i + 1 << ". " << vehicles[i]->getName() << "\n";
                }
                std::cout << "Выберите ТС (0 для отмены): ";
                int vehicleChoice;
                std::cin >> vehicleChoice;

                if (vehicleChoice > 0 && vehicleChoice <= vehicles.size()) {
                    if (race.registerVehicle(vehicles[vehicleChoice - 1].get())) {
                        std::cout << vehicles[vehicleChoice - 1]->getName() << " зарегистрирован!\n";
                    }
                    else {
                        std::cout << "Ошибка: ТС уже зарегистрирован или не подходит для гонки.\n";
                    }
                }
            }
        }

        // Предложение провести еще одну гонку
        std::cout << "\n1. Провести ещё одну гонку\n2. Выйти\nВыберите действие: ";
        std::cin >> choice;
        if (choice == 2) break;
    }

    return 0;
}