#include "Hall.h"
#include <iostream>
#include <utility>

Hall::Hall(int number_, int capacity_)
    : number(number_), capacity(capacity_) {}

int Hall::getNumber() const {
    return number;
}

int Hall::getCapacity() const {
    return capacity;
}

int Hall::getTicketsSold() const {
    return ticketsSold;
}

void Hall::setCapacity(int newCapacity) {
    if (newCapacity <= 0) {
        std::cout << "Вместимость должна быть положительной.\n";
        return;
    }

    if (newCapacity < ticketsSold) {
        std::cout << "Нельзя установить вместимость меньше "
                     "количества проданных билетов.\n";
        return;
    }

    capacity = newCapacity;
    std::cout << "Вместимость зала изменена.\n";
}

bool Hall::sellTickets(int count) {
    if (count <= 0) {
        std::cout << "Количество билетов должно быть положительным.\n";
        return false;
    }

    if (ticketsSold + count > capacity) {
        std::cout << "Нельзя продать столько билетов: "
                     "превышена вместимость зала.\n";
        return false;
    }

    ticketsSold += count;
    std::cout << "Билеты успешно проданы.\n";
    return true;
}

bool Hall::addPerformance(std::shared_ptr<Performance> p) {
    if (!p) {
        std::cout << "Не удалось добавить спектакль.\n";
        return false;
    }

    std::size_t initialCount = performances.size();
    *this += std::move(p);
    return performances.size() > initialCount;
}

const Collection<std::shared_ptr<Performance>>&
Hall::getPerformances() const {
    return performances;
}

Collection<std::shared_ptr<Performance>>&
Hall::getPerformances() {
    return performances;
}

void Hall::displayFullInfo() const {
    std::cout << "\nЗал №" << number << '\n';
    std::cout << "Вместимость: " << capacity << '\n';
    std::cout << "Продано билетов: " << ticketsSold << '\n';
    std::cout << "Свободных мест: " << capacity - ticketsSold << '\n';
    std::cout << "Репертуар:\n";

    if (performances.empty()) {
        std::cout << "Репертуар пуст.\n";
        return;
    }

    for (std::size_t i = 0; i < performances.size(); ++i) {
        std::cout << "\n" << i + 1 << ".\n";

        if (performances[i]) {
            performances[i]->displayInfo();
        }
    }
}

Hall& Hall::operator+=(std::shared_ptr<Performance> p) {
    if (!p) {
        std::cout << "Не удалось добавить спектакль.\n";
        return *this;
    }

    int totalDuration = p->getDuration();

    for (const auto& performance : performances) {
        if (performance) {
            totalDuration += performance->getDuration();
        }
    }

    if (totalDuration > 480) {
        std::cout << "Нельзя добавить спектакль: общая длительность "
                     "репертуара превысит 480 минут.\n";
        return *this;
    }

    performances.add(std::move(p));
    std::cout << "Спектакль добавлен в репертуар.\n";
    return *this;
}

Hall& Hall::operator-=(const Performance& p) {
    const auto index = findByPredicate(
        performances,
        [&p](const std::shared_ptr<Performance>& performance) {
            return performance && *performance == p;
        });

    if (!index) {
        std::cout << "Такого спектакля нет в репертуаре.\n";
        return *this;
    }

    performances.removeAt(*index);
    std::cout << "Спектакль удалён из репертуара.\n";
    return *this;
}

void printHallAnalytics(const Hall& hall) {
    double occupancy = 0.0;

    if (hall.capacity > 0) {
        occupancy = static_cast<double>(hall.ticketsSold)
            / hall.capacity * 100.0;
    }

    int totalDuration = 0;

    for (const auto& performance : hall.performances) {
        if (performance) {
            totalDuration += performance->getDuration();
        }
    }

    std::cout << "\nАналитика зала №" << hall.number << '\n';
    std::cout << "Продано билетов: " << hall.ticketsSold
              << " из " << hall.capacity << '\n';
    std::cout << "Заполняемость: " << occupancy << "%\n";
    std::cout << "Количество спектаклей: "
              << hall.performances.size() << '\n';
              std::cout << "Общая длительность репертуара: "
              << totalDuration << " мин.\n";
}