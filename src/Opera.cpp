#include "Opera.h"
#include <iostream>

Opera::Opera(
    std::string_view title_,
    std::string_view director_,
    int duration_,
    int ageRestriction_,
    bool hasRecitatives_
)
    : Performance(title_, director_, "Опера", duration_, ageRestriction_),
      hasRecitatives(hasRecitatives_) {}

bool Opera::getHasRecitatives() const { return hasRecitatives; }
void Opera::setHasRecitatives(bool value) { hasRecitatives = value; }

std::string Opera::getType() const { return "Опера"; }

void Opera::displayInfo() const {
    Performance::displayInfo();
    std::cout << "Наличие речитативов: "
              << (hasRecitatives ? "есть" : "нет") << '\n';
}

void Opera::performSpecialAction() const {
    std::cout << "\n=== Анализ исполнения оперы ===\n";
    std::cout << "Опера: \"" << getTitle() << "\"\n";

    std::cout << "\n[1] Структура вокальной ткани:\n";
    if (hasRecitatives) {
        std::cout << "  - речитативы присутствуют\n";
        std::cout << "  - сюжет развивается музыкально-речевым исполнением\n";
        std::cout << "  - чередование арий, ансамблей, хоров и речитативов\n";
    } else {
        std::cout << "  - речитативы отсутствуют\n";
        std::cout << "  - опера построена из отдельных законченных номеров\n";
        std::cout << "  - между номерами возможны разговорные диалоги\n";
        std::cout << "  - акцент на вокальных партиях\n";
    }

    std::cout << "\n[2] Масштаб постановки (длительность "
              << getDuration() << " мин):\n";
    if (getDuration() >= 180) {
        std::cout << "  - большая опера (grand opera)\n";
        std::cout << "  - 4–5 актов, большой оркестр и хор\n";
    } else if (getDuration() >= 120) {
        std::cout << "  - опера в двух актах\n";
        std::cout << "  - средний оркестровый состав\n";
    } else {
        std::cout << "  - камерная постановка\n";
        std::cout << "  - малый состав исполнителей\n";
    }

    std::cout << "\n[3] Итоговая классификация:\n";
    if (!hasRecitatives && getDuration() < 120) {
        std::cout << "  -> Камерная номерная опера\n";
        std::cout << "     (короткая, без речитативов, из отдельных номеров)\n";
    } else if (!hasRecitatives) {
        std::cout << "  -> Номерная опера\n";
        std::cout << "     (полнометражная, но без речитативов)\n";
    } else if (getDuration() >= 180) {
        std::cout << "  -> Большая опера (grand opera)\n";
        std::cout << "     (полнометражная, с речитативами, крупный состав)\n";
    } else {
        std::cout << "  -> Камерная опера с речитативами\n";
        std::cout << "     (речитативы есть, но состав небольшой)\n";
    }
} 