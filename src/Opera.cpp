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

// --- Специальный метод ------------------------------------------------
// Логика:
//  * нет речитативов            -> номерная опера (арии + хоры,
//                                  разговорные диалоги вместо речитатива);
//  * есть речитативы, длинная    -> большая опера (grand opera);
//  * есть речитативы, короче 180 -> камерная опера с речитативами.
std::string Opera::getOperaType() const {
    if (!hasRecitatives) {
        return "Номерная опера";
    }
    if (getDuration() >= 180) {
        return "Большая опера (grand opera)";
    }
    return "Камерная опера с речитативами";
}
// ----------------------------------------------------------------------

std::string Opera::getType() const {
    return "Опера";
}

void Opera::displayInfo() const {
    Performance::displayInfo();

    std::cout << "Наличие речитативов: "
              << (hasRecitatives ? "есть" : "нет") << '\n';
    std::cout << "Тип оперы: "
              << getOperaType() << '\n';
}

void Opera::performSpecialAction() const {
    std::cout << "\n=== Анализ исполнения оперы ===\n";
    std::cout << "Опера: \"" << getTitle() << "\"\n";
    std::cout << "Определённый тип: " << getOperaType() << "\n\n";

    const std::string type = getOperaType();

    if (type == "Большая опера (grand opera)") {
        std::cout << "Это масштабная опера с речитативами.\n";
        std::cout << "Длительность — не менее 180 минут, обычно 4–5 актов.\n";
        std::cout << "Сюжет развивается через чередование арий, ансамблей,\n";
        std::cout << "хоров и речитативов.\n";
        std::cout << "Задействованы большой оркестр и хор.\n";
    }
    else if (type == "Камерная опера с речитативами") {
        std::cout << "В опере есть речитативы — сюжет движется\n";
        std::cout << "музыкально-речевым исполнением.\n";
        std::cout << "Спектакль короче 180 минут: один-два акта,\n";
        std::cout << "небольшой состав исполнителей.\n";
        std::cout << "Сочетает вокальные партии и речитативы.\n";
    }
    else { // Номерная опера
        std::cout << "Речитативы отсутствуют — опера построена\n";
        std::cout << "из отдельных законченных номеров (арий, дуэтов, хоров).\n";
        std::cout << "Между номерами возможны разговорные диалоги.\n";
        std::cout << "Основное внимание — вокальным партиям.\n";
    }
}