#include "Ballet.h"
#include <iostream>

Ballet::Ballet(
    std::string_view title_,
    std::string_view director_,
    int duration_,
    int ageRestriction_,
    int dancersCount_
)
    : Performance(title_, director_, "Балет", duration_, ageRestriction_),
      dancersCount(dancersCount_) {}

int Ballet::getDancersCount() const {
    return dancersCount;
}

void Ballet::setDancersCount(int value) {
    dancersCount = value;
}

std::string Ballet::getType() const {
    return "Балет";
}

void Ballet::displayInfo() const {
    Performance::displayInfo();

    std::cout << "Количество танцоров: "
              << dancersCount << '\n';
}

void Ballet::performSpecialAction() const {
    std::cout << "\n=== Анализ типа балета ===\n";
    std::cout << "Балет: \"" << getTitle() << "\"\n";

    if (dancersCount <= 10) {
        std::cout << "Это камерный балет (миниатюра).\n";
        std::cout << "На сцене всего "
                  << dancersCount << " танцоров.\n";
    }
    else if (dancersCount <= 30) {
        std::cout << "Это классический балет.\n";
        std::cout << "Количество танцоров: "
                  << dancersCount << ".\n";
    }
    else {
        std::cout << "Это гранд-балет (масштабное представление).\n";
        std::cout << "Количество танцоров: "
                  << dancersCount << ".\n";
    }
}