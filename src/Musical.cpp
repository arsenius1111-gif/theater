#include "Musical.h"
#include <iostream>

Musical::Musical(
    std::string_view title_,
    std::string_view director_,
    int duration_,
    int ageRestriction_,
    bool hasLiveBand_
)
    : Performance(title_, director_, "Мюзикл", duration_, ageRestriction_),
      hasLiveBand(hasLiveBand_) {}

bool Musical::getHasLiveBand() const {
    return hasLiveBand;
}

void Musical::setHasLiveBand(bool value) {
    hasLiveBand = value;
}

std::string Musical::getType() const {
    return "Мюзикл";
}

void Musical::displayInfo() const {
    Performance::displayInfo();

    std::cout << "Живая музыкальная группа: "
              << (hasLiveBand ? "есть" : "нет") << '\n';
}

void Musical::performSpecialAction() const {
    std::cout << "\n=== Анализ музыкального сопровождения ===\n";
    std::cout << "Мюзикл: \"" << getTitle() << "\"\n";

    if (hasLiveBand) {
        std::cout << "Музыкальное сопровождение исполняется живой группой.\n";
        std::cout << "На сцене используются инструменты и живое исполнение.\n";
        std::cout << "Музыкальное сопровождение создаётся непосредственно во время спектакля.\n";
    }
    else {
        std::cout << "Живая музыкальная группа отсутствует.\n";
        std::cout << "Для сопровождения используются заранее подготовленные записи.\n";
        std::cout << "Музыкальные композиции воспроизводятся с фонограммы.\n";
    }
}