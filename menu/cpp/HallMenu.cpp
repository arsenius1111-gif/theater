#include "HallMenu.h"
#include <iostream>
#include <limits>
#include <memory>

namespace {
    bool readNumber(int& value) {
        if (std::cin >> value) {
            return true;
        }

        std::cin.clear();
        std::cin.ignore(
            (std::numeric_limits<std::streamsize>::max)(), '\n');

        std::cout << "Ошибка ввода. Введите целое число.\n";
        return false;
    }

    bool selectHall(const Collection<Hall>& halls, int& index) {
        if (halls.empty()) {
            std::cout << "Залов пока нет.\n";
            return false;
        }

        std::cout << "\nДоступные залы:\n";

        for (std::size_t i = 0; i < halls.size(); ++i) {
            std::cout << i + 1 << ". Зал №"
                      << halls[i].getNumber()
                      << ", вместимость: "
                      << halls[i].getCapacity() << '\n';
        }

        std::cout << "Выберите номер зала: ";

        if (!readNumber(index)) {
            return false;
        }

        if (index < 1 || index > static_cast<int>(halls.size())) {
            std::cout << "Такого зала нет.\n";
            return false;
        }

        --index;
        return true;
    }

    bool selectPerformance(
        const Collection<std::shared_ptr<Performance>>& catalog,
        int& index) {
        if (catalog.empty()) {
            std::cout << "Каталог спектаклей пуст.\n";
            return false;
        }

        std::cout << "\nКаталог спектаклей:\n";

        for (std::size_t i = 0; i < catalog.size(); ++i) {
            if (catalog[i]) {
                std::cout << i + 1 << ". "
                          << catalog[i]->getTitle() << " — "
                          << catalog[i]->getDuration() << " мин. ("
                          << catalog[i]->getType() << ")\n";
            }
        }

        std::cout << "Выберите номер спектакля: ";

        if (!readNumber(index)) {
            return false;
        }

        if (index < 1 || index > static_cast<int>(catalog.size())) {
            std::cout << "Такого спектакля нет.\n";
            return false;
        }

        --index;

        if (!catalog[static_cast<std::size_t>(index)]) {
            std::cout << "Не удалось получить спектакль.\n";
            return false;
        }

        return true;
    }

    void sellTickets(Hall& hall) {
        int count = 0;
        std::cout << "Сколько билетов продать: ";

        if (readNumber(count)) {
            hall.sellTickets(count);
        }
    }

    void addPerformance(
        Hall& hall,
        const Collection<std::shared_ptr<Performance>>& catalog) {
        int index = 0;

        if (selectPerformance(catalog, index)) {
            hall += catalog[static_cast<std::size_t>(index)];
        }
    }

    void removePerformance(Hall& hall) {
        const auto& performances = hall.getPerformances();

        if (performances.empty()) {
            std::cout << "Репертуар пуст.\n";
            return;
        }

        std::cout << "\nРепертуар зала:\n";

        for (std::size_t i = 0; i < performances.size(); ++i) {
            if (performances[i]) {
                std::cout << i + 1 << ". "
                          << performances[i]->getTitle() << " ("
                          << performances[i]->getType() << ")\n";
            }
        }

        int index = 0;
        std::cout << "Выберите номер спектакля для удаления: ";

        if (!readNumber(index)) {
            return;
        }

        if (index < 1 || index > static_cast<int>(performances.size())) {
            std::cout << "Указан неверный номер спектакля.\n";
            return;
        }

        const auto& selected =
            performances[static_cast<std::size_t>(index - 1)];

        if (!selected) {
            std::cout << "Не удалось получить спектакль.\n";
            return;
        }

        hall -= *selected;
    }

    void changeCapacity(Hall& hall) {
        int capacity = 0;
        std::cout << "Введите новую вместимость: ";

        if (readNumber(capacity)) {
            hall.setCapacity(capacity);
            }
    }

    void showHallMenu() {
        std::cout << "\n1. Показать информацию о зале\n";
        std::cout << "2. Продать билеты\n";
        std::cout << "3. Добавить спектакль в репертуар\n";
        std::cout << "4. Удалить спектакль из репертуара\n";
        std::cout << "5. Изменить вместимость зала\n";
        std::cout << "6. Аналитика зала\n";
        std::cout << "0. Назад\n";
        std::cout << "Выберите действие: ";
    }

    void processHallChoice(
        int choice,
        Hall& hall,
        const Collection<std::shared_ptr<Performance>>& catalog,
        bool& running) {
        switch (choice) {
        case 1:
            hall.displayFullInfo();
            break;
        case 2:
            sellTickets(hall);
            break;
        case 3:
            addPerformance(hall, catalog);
            break;
        case 4:
            removePerformance(hall);
            break;
        case 5:
            changeCapacity(hall);
            break;
        case 6:
            printHallAnalytics(hall);
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Такого пункта меню нет.\n";
        }
    }
}

void HallMenu::create(Collection<Hall>& halls) {
    int number = 0;
    int capacity = 0;

    std::cout << "\n========== СОЗДАНИЕ ЗАЛА ==========\n";
    std::cout << "Введите номер зала: ";

    if (!readNumber(number)) {
        return;
    }

    if (number <= 0) {
        std::cout << "Номер зала должен быть положительным.\n";
        return;
    }

    for (const Hall& hall : halls) {
        if (hall.getNumber() == number) {
            std::cout << "Зал с таким номером уже существует.\n";
            return;
        }
    }

    std::cout << "Введите вместимость зала: ";

    if (!readNumber(capacity)) {
        return;
    }

    if (capacity <= 0) {
        std::cout << "Вместимость должна быть положительной.\n";
        return;
    }

    halls.emplace(number, capacity);
    std::cout << "Зал успешно создан.\n";
}

void HallMenu::manage(
    Collection<Hall>& halls,
    const Collection<std::shared_ptr<Performance>>& catalog) {
    int index = 0;

    if (!selectHall(halls, index)) {
        return;
    }

    Hall& hall = halls[static_cast<std::size_t>(index)];
    bool running = true;

    while (running) {
        int choice = -1;

        std::cout << "\n========== УПРАВЛЕНИЕ ЗАЛОМ №"
                  << hall.getNumber() << " ==========\n";

        showHallMenu();

        if (!readNumber(choice)) {
            continue;
        }

        processHallChoice(choice, hall, catalog, running);
    }
}