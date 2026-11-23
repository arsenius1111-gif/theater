#include "MainMenu.h"
#include "HallMenu.h"
#include "PerformanceMenu.h"
#include "Ballet.h"
#include "Musical.h"
#include "Opera.h"

#include "../../Exceptions/InvalidDataException.h"
#include "../../Exceptions/DuplicateHallException.h"
#include "../../Exceptions/CapacityExceededException.h"
#include "../../Exceptions/NotFoundException.h"
#include "../../Exceptions/OutOfRangeException.h"
#include "../../Exceptions/InvalidOperationException.h"

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
    "Щелкунчик", "Пётр Чайковский", 120, 6, 24));

catalog.add(std::make_shared<Musical>(
    "Ревизор", "Николай Гоголь", 140, 12, false));

catalog.add(std::make_shared<Opera>(
    "Мастер и Маргарита", "Михаил Булгаков", 180, 16, false));

halls[0] += catalog[0];
halls[0] += catalog[1];
}

namespace {
void processMainMenuChoice(
int choice,
Collection<Hall>& halls,
Collection<std::shared_ptr<Performance>>& catalog,
bool& running) {

switch (choice) {
case 1:
    PerformanceMenu::showAll(catalog);
    break;
case 2:
    HallMenu::manage(halls, catalog);
    break;
case 3:
    PerformanceMenu::compare(catalog);
    break;
case 4:
    PerformanceMenu::create(catalog);
    break;
case 5:
    HallMenu::create(halls);
    break;
case 6:
    PerformanceMenu::showInheritanceDemo();
    break;
case 7:
    PerformanceMenu::manageCollection(catalog);
    break;
case 0:
    running = false;
    std::cout << "Программа завершена.\n";
    break;
default:
    std::cout << "Такого пункта меню нет.\n";
}
}
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
    std::cout << "7. Работа с коллекцией спектаклей\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";

    if (!(std::cin >> choice)) {
        clearInput();
        std::cout << "Ошибка ввода. Введите число.\n";
        continue;
    }

    try {
        processMainMenuChoice(choice, halls, catalog, running);
    }
    catch (const InvalidDataException& e) {
        std::cout << "Ошибка данных: " << e.what() << '\n';
    }
    catch (const DuplicateHallException& e) {
        std::cout << "Ошибка создания зала: " << e.what() << '\n';
    }
    catch (const CapacityExceededException& e) {
        std::cout << "Превышена вместимость зала: "
                  << e.what() << '\n';
    }
    catch (const NotFoundException& e) {
        std::cout << "Элемент не найден: " << e.what() << '\n';
    }
    catch (const OutOfRangeException& e) {
        std::cout << "Выход за границы коллекции: "
                  << e.what() << '\n';
    }
    catch (const InvalidOperationException& e) {
        std::cout << "Недопустимая операция: " << e.what() << '\n';
    }
}
}