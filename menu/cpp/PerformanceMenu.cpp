#include "PerformanceMenu.h"
#include "Ballet.h"
#include "Musical.h"
#include "Opera.h"
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>

namespace {
    bool readChoice(int& choice) {
        if (std::cin >> choice) {
            return true;
        }

        std::cin.clear();
        std::cin.ignore(
            (std::numeric_limits<std::streamsize>::max)(), '\n');

        std::cout << "Ошибка ввода. Введите число.\n";
        return false;
    }

    std::shared_ptr<Performance> createPerformance() {
        int type = 0;

        std::cout << "\nВыберите тип спектакля:\n";
        std::cout << "1. Балет\n";
        std::cout << "2. Опера\n";
        std::cout << "3. Мюзикл\n";
        std::cout << "Ваш выбор: ";

        if (!readChoice(type)) {
            return nullptr;
        }

        std::string title;
        std::string director;
        int duration = 0;
        int ageRestriction = 0;

        std::cout << "Введите название: ";
        std::cin >> std::ws;
        std::getline(std::cin, title);

        if (title.empty()) {
            std::cout << "Название не может быть пустым.\n";
            return nullptr;
        }

        std::cout << "Введите режиссёра: ";
        std::getline(std::cin, director);

        if (director.empty()) {
            std::cout << "Режиссёр не может быть пустым.\n";
            return nullptr;
        }

        std::cout << "Введите длительность в минутах: ";

        if (!readChoice(duration) || duration <= 0) {
            std::cout << "Длительность должна быть положительной.\n";
            return nullptr;
        }

        std::cout << "Введите возрастное ограничение: ";

        if (!readChoice(ageRestriction) || ageRestriction < 0) {
            std::cout << "Возрастное ограничение не может быть отрицательным.\n";
            return nullptr;
        }

        switch (type) {
        case 1: {
            int dancersCount = 0;

            std::cout << "Введите количество танцоров: ";

            if (!readChoice(dancersCount) || dancersCount <= 0) {
                std::cout << "Количество танцоров должно быть положительным.\n";
                return nullptr;
            }

            return std::make_shared<Ballet>(
                title, director, duration, ageRestriction, dancersCount);
        }

        case 2: {
            int recitatives = 0;

            std::cout << "Есть ли речитативы? (1 — да, 0 — нет): ";

            if (!readChoice(recitatives) ||
                (recitatives != 0 && recitatives != 1)) {
                std::cout << "Введите 1 или 0.\n";
                return nullptr;
            }

            return std::make_shared<Opera>(
                title, director, duration, ageRestriction,
                recitatives == 1);
        }

        case 3: {
            int liveBand = 0;

            std::cout << "Есть ли живая музыкальная группа? (1 — да, 0 — нет): ";

            if (!readChoice(liveBand) ||
                (liveBand != 0 && liveBand != 1)) {
                std::cout << "Введите 1 или 0.\n";
                return nullptr;
            }

            return std::make_shared<Musical>(
                title, director, duration, ageRestriction,
                liveBand == 1);
        }

        default:
            std::cout << "Такого типа спектакля нет.\n";
            return nullptr;
        }
    }

    void managePerformance(Performance& performance) {
        bool running = true;

        while (running) {
            std::cout << "\n========== УПРАВЛЕНИЕ: "
                      << performance.getType() << " ==========\n";
            std::cout << "1. Показать информацию\n";
            std::cout << "2. Выполнить специальное действие\n";
            std::cout << "3. Изменить название\n";
            std::cout << "0. Назад\n";
            std::cout << "Ваш выбор: ";

            int action = -1;

            if (!readChoice(action)) {
                continue;
            }

            switch (action) {
            case 1:
                performance.displayInfo();
                break;

            case 2:
                performance.performSpecialAction();
                break;

            case 3: {
                std::string title;

                std::cout << "Введите новое название: ";
                std::cin >> std::ws;
                std::getline(std::cin, title);

                if (title.empty()) {
                    std::cout << "Название не может быть пустым.\n";
                } else {
                    performance.setTitle(title);
                    std::cout << "Название успешно изменено.\n";
                }

                break;
            }

            case 0:
                running = false;
                break;

            default:
                std::cout << "Такого пункта меню нет.\n";
            }
        }
    }
}

void PerformanceMenu::showAll(
    const Collection<std::shared_ptr<Performance>>& catalog) {

    std::cout << "\n========== КАТАЛОГ СПЕКТАКЛЕЙ ==========\n";

    if (catalog.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }

    for (std::size_t i = 0; i < catalog.size(); ++i) {
        std::cout << "\n" << i + 1 << ".\n";

        if (catalog[i]) {
            catalog[i]->displayInfo();
        }
    }
}

void PerformanceMenu::create(
    Collection<std::shared_ptr<Performance>>& catalog) {

    std::cout << "\n========== ДОБАВЛЕНИЕ СПЕКТАКЛЯ ==========\n";

    std::shared_ptr<Performance> performance = createPerformance();

    if (!performance) {
        std::cout << "Спектакль не добавлен.\n";
        return;
    }

    catalog.add(std::move(performance));
    std::cout << "Спектакль добавлен в каталог.\n";
}

void PerformanceMenu::compare(
    const Collection<std::shared_ptr<Performance>>& catalog) {

    if (catalog.size() < 2) {
        std::cout << "Для сравнения нужны минимум два спектакля.\n";
        return;
    }

    showAll(catalog);

    int i1 = 0;
    int i2 = 0;

    std::cout << "\nВведите номер первого спектакля: ";

    if (!readChoice(i1)) {
        return;
    }

    std::cout << "Введите номер второго спектакля: ";

    if (!readChoice(i2)) {
        return;
    }

    if (i1 < 1  || i1 > static_cast<int>(catalog.size())|| 
        i2 < 1 || i2 > static_cast<int>(catalog.size())) {
        std::cout << "Указан неверный номер спектакля.\n";
        return;
    }

    const auto& first = catalog[static_cast<std::size_t>(i1 - 1)];
    const auto& second = catalog[static_cast<std::size_t>(i2 - 1)];

    if (!first || !second) {
        std::cout << "Не удалось сравнить спектакли.\n";
        return;
    }

    std::cout << "\nРезультат сравнения:\n";

    if (*first == *second) {
        std::cout << "Спектакли имеют одинаковое название.\n";
    } else {
        std::cout << "Названия спектаклей различаются.\n";
    }

    if (*first < *second) {
        std::cout << "Первый спектакль короче второго.\n";
    } else if (*first > *second) {
        std::cout << "Первый спектакль длиннее второго.\n";
    } else {
        std::cout << "Длительности спектаклей равны.\n";
    }
}

void PerformanceMenu::showInheritanceDemo() {
    Collection<std::shared_ptr<Performance>> performances;

    performances.add(std::make_shared<Ballet>(
        "Лебединое озеро", "Мариус Петипа",
        140, 6, 24));

    performances.add(std::make_shared<Opera>(
        "Евгений Онегин", "Константин Сергеев",
        160, 12, true));

    performances.add(std::make_shared<Musical>(
        "Чикаго", "Боб Фосси",
        150, 16, true));

    bool running = true;

    while (running) {
        std::cout << "\n========== РАБОТА СО СПЕКТАКЛЯМИ ==========\n";
        std::cout << "1. Выбрать балет\n";
        std::cout << "2. Выбрать оперу\n";
        std::cout << "3. Выбрать мюзикл\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш выбор: ";

        int choice = -1;

        if (!readChoice(choice)) {
            continue;
        }

        if (choice == 0) {
            running = false;
            continue;
        }

        if (choice < 1 || choice > 3) {
            std::cout << "Такого пункта меню нет.\n";
            continue;
        }

        const std::shared_ptr<Performance>& performance =
            performances[static_cast<std::size_t>(choice - 1)];

        managePerformance(*performance);
    }
}

void PerformanceMenu::manageCollection(
    Collection<std::shared_ptr<Performance>>& catalog) {

    bool running = true;

    while (running) {
        std::cout << "\n========== РАБОТА С КОЛЛЕКЦИЕЙ ==========\n";
        std::cout << "1. Показать все элементы\n";
        std::cout << "2. Добавить элемент\n";
        std::cout << "3. Найти спектакль по названию\n";
        std::cout << "4. Удалить элемент по номеру\n";
        std::cout << "5. Получить элемент по индексу\n";
        std::cout << "6. Показать размер коллекции\n";
        std::cout << "7. Перебрать элементы итераторами\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш выбор: ";

        int choice = -1;

        if (!readChoice(choice)) {
            continue;
        }

        switch (choice) {
        case 1:
            showAll(catalog);
            break;

        case 2:
            create(catalog);
            break;

        case 3: {
            std::string title;

            std::cout << "Введите название спектакля для поиска: ";
            std::cin >> std::ws;
            std::getline(std::cin, title);

            auto result = catalog.findIf(
                [&title](const std::shared_ptr<Performance>& performance) {
                    return performance && performance->getTitle() == title;
                });

            if (result.has_value()) {
                std::cout << "Спектакль найден. Номер: "
                          << *result + 1 << "\n";

                catalog.get(*result)->displayInfo();
            } else {
                std::cout << "Спектакль не найден.\n";
            }

            break;
        }

        case 4: {
            if (catalog.empty()) {
                std::cout << "Коллекция пуста.\n";
                break;
            }

            showAll(catalog);

            int index = 0;

            std::cout << "Введите номер элемента для удаления: ";

            if (!readChoice(index)) {
                break;
            }

            if (index < 1 || index > static_cast<int>(catalog.size())) {
                std::cout << "Неверный номер элемента.\n";
                break;
            }

            if (catalog.removeAt(static_cast<std::size_t>(index - 1))) {
                std::cout << "Элемент успешно удалён.\n";
            }

            break;
        }

        case 5: {
            if (catalog.empty()) {
                std::cout << "Коллекция пуста.\n";
                break;
            }

            int index = 0;

            std::cout << "Введите индекс элемента (начиная с 1): ";

            if (!readChoice(index)) {
                break;
            }

            if (index < 1 || index > static_cast<int>(catalog.size())) {
                std::cout << "Неверный индекс.\n";
                break;
            }

            const auto& performance =
                catalog.get(static_cast<std::size_t>(index - 1));

            if (performance) {
                performance->displayInfo();
            } else {
                std::cout << "Элемент не содержит спектакль.\n";
            }

            break;
        }

        case 6:
            std::cout << "Количество элементов в коллекции: "
                      << catalog.size() << "\n";
            break;

        case 7: {
            if (catalog.empty()) {
                std::cout << "Коллекция пуста.\n";
                break;
            }

            std::cout << "\nПеребор коллекции с помощью итераторов:\n";

            std::size_t index = 1;

            for (auto it = catalog.begin(); it != catalog.end(); ++it) {
                std::cout << "\nЭлемент " << index++ << ":\n";

                if (*it) {
                    (*it)->displayInfo();
                }
            }

            break;
        }

        case 0:
        running = false;
            break;

        default:
            std::cout << "Такого пункта меню нет.\n";
        }
    }
}