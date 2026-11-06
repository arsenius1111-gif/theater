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

// --- Специальный метод ------------------------------------------------
// Логика: если группа есть и спектакль длинный (>= 150 мин) —
// это "большой" мюзикл (обычно 2 акта + антракт). Если группа есть,
// но спектакль короткий — камерный. Если группы нет — фонограмма.
std::string Musical::getMusicalType() const {
    if (!hasLiveBand) {
        return "Фонограммный мюзикл";
    }
    if (getDuration() >= 150) {
        return "Большой сценический мюзикл";
    }
    return "Камерный живой мюзикл";
}
// ----------------------------------------------------------------------

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
    std::cout << "Определённый тип: " << getMusicalType() << "\n\n";

    // Разбор по типу — теперь логика не «if/else по флагу»,
    // а «switch по типу»
    const std::string type = getMusicalType();

    if (type == "Большой сценический мюзикл") {
        std::cout << "Это масштабная постановка с живым оркестром/группой.\n";
        std::cout << "Длительность спектакля — не менее 150 минут (2 акта + антракт).\n";
        std::cout << "Музыка звучит вживую, номеров много, задействован большой состав.\n";
    }
    else if (type == "Камерный живой мюзикл") {
        std::cout << "Это компактная постановка с живым музыкальным составом.\n";
        std::cout << "Спектакль короче 150 минут — один акт без большого антракта.\n";
        std::cout << "Музыка исполняется живьём небольшой группой.\n";
    }
    else { // Фонограммный мюзикл
        std::cout << "Живая группа не задействована.\n";
        std::cout << "Сопровождение воспроизводится с фонограммы.\n";
        std::cout << "Это упрощает гастроли и снижает стоимость постановки.\n";
    }
}