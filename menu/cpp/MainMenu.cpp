#include "MainMenu.h"
#include "HallMenu.h"
#include "PerformanceMenu.h"
#include "Ballet.h"
#include "Musical.h"
#include "Opera.h"
#include <iostream>
#include <memory>
#include <limits>

MainMenu::MainMenu() {
    initDatabase();
}

void MainMenu::clearInput() const {
    std::cin.clear();
    std::cin.ignore(
        (std::numeric_limits<std::streamsize>::max)(), '\n');
}

void MainMenu::initDatabase() {
    halls.emplace(1, 100);
    halls.emplace(2, 50);

    catalog.add(std::make_shared<Opera>(
        "Гамлет", "Уильям Шекспир", 150, 16, true));

    catalog.add(std::make_shared<Ballet>(
        "Щелкунчик", "Пётр Чайковский", 120, 6, 24, 2, 30));

    catalog.add(std::make_shared<Musical>(
        "Ревизор", "Николай Гоголь", 140, 12, false));

    catalog.add(std::make_shared<Opera>(
        "Мастер и Маргарита", "Михаил Булгаков", 180, 16, false));

    halls[0] += catalog[0];
    halls[0] += catalog[1];
}

void MainMenu::run() {
    bool running = true;

    while (running) {
        int choice = -1;

        std::cout << "\n========== ТЕАТР ==========\n";
        std::cout << "1. Просмотреть каталог спектаклей\n";
        std::cout << "2. Управление залами\n";
        std::cout << "3. Сравнить спектакли\n";
        std::cout << "4. Добавить спектакль в каталог\n";
        std::cout << "5. Создать зал\n";
        std::cout << "6. Демонстрация полиморфизма\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Ошибка ввода. Введите число.\n";
            continue;
        }

        if (choice == 1) {
            PerformanceMenu::showAll(catalog);
        } else if (choice == 2) {
            HallMenu::manage(halls, catalog);
        } else if (choice == 3) {
            PerformanceMenu::compare(catalog);
        } else if (choice == 4) {
            PerformanceMenu::create(catalog);
        } else if (choice == 5) {
            HallMenu::create(halls);
        } else if (choice == 6) {
            PerformanceMenu::showInheritanceDemo();
        } else if (choice == 0) {
            running = false;
            std::cout << "Программа завершена.\n";
        } else {
            std::cout << "Такого пункта меню нет.\n";
        }
    }
}