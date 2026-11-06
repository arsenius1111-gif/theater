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

bool Musical::getHasLiveBand() const { return hasLiveBand; }
void Musical::setHasLiveBand(bool value) { hasLiveBand = value; }
   
std::string Musical::getMusicalType() const {
    if (!hasLiveBand) {
        return "Фонограммный мюзикл";
    }
    if (getDuration() >= 150) {
        return "Большой сценический мюзикл";
    }
    return "Камерный живой мюзикл";
}

std::string Musical::getType() const {
    return "Мюзикл";
}

void Musical::displayInfo() const {
    Performance::displayInfo();

    std::cout << "Живая музыкальная группа: "
              << (hasLiveBand ? "есть" : "нет") << '\n';
    std::cout << "Тип мюзикла: "
              << getMusicalType() << '\n';
}

void Musical::performSpecialAction() const {
    std::cout << "\n=== Анализ музыкального сопровождения ===\n";
    std::cout << "Мюзикл: \"" << getTitle() << "\"\n";

    std::cout << "\n[1] Характер сопровождения:\n";
    if (hasLiveBand) {
        std::cout << "  - живая группа на сцене\n";
        std::cout << "  - инструменты звучат непосредственно во время спектакля\n";
    } else {
        std::cout << "  - фонограмма, записанное сопровождение\n";
        std::cout << "  - живой состав не задействован\n";
    }

    const int dur = getDuration();
    std::cout << "\n[2] Масштаб (длительность " << dur << " мин):\n";
    if (dur >= 150) {
        std::cout << "  - два акта с антрактом\n";
        std::cout << "  - большой сценический формат\n";
    } else {
        std::cout << "  - компактный одноактный формат\n";
    }

    std::cout << "\n[3] Итоговая классификация:\n";
    if (!hasLiveBand && dur < 150)
        std::cout << "  -> Компактный фонограммный мюзикл\n";
    else if (!hasLiveBand)
        std::cout << "  -> Полнометражный фонограммный мюзикл\n";
    else if (dur >= 150)
        std::cout << "  -> Большой сценический мюзикл с живой группой\n";
    else
        std::cout << "  -> Камерный живой мюзикл\n";
}