#include "Ballet.h"
#include <iostream>

Ballet::Ballet(
    std::string_view title_,
    std::string_view director_,
    int duration_,
    int ageRestriction_,
    int dancersCount_,
    int actsCount_,
    int orchestraSize_
)
    : Performance(title_, director_, "Балет", duration_, ageRestriction_),
      dancersCount(dancersCount_),
      actsCount(actsCount_),
      orchestraSize(orchestraSize_) {}

int Ballet::getDancersCount() const {
    return dancersCount;
}

int Ballet::getActsCount() const {
    return actsCount;
}

int Ballet::getOrchestraSize() const {
    return orchestraSize;
}

void Ballet::setDancersCount(int value) {
    dancersCount = value;
}

void Ballet::setActsCount(int value) {
    actsCount = value;
}

void Ballet::setOrchestraSize(int value) {
    orchestraSize = value;
}

std::string Ballet::getType() const {
    return "Балет";
}

void Ballet::displayInfo() const {
    Performance::displayInfo();

    std::cout << "Количество танцоров: "
              << dancersCount << '\n';

    std::cout << "Количество актов: "
              << actsCount << '\n';

    std::cout << "Размер оркестра: "
              << orchestraSize << '\n';
}

void Ballet::performSpecialAction() const {

 std::cout<<"\n=== Тип баллета\"" << getTitle()<<"\"===\n";

 if (dancersCount<=10) {
    std::cout << "Это Камерный баллет(миниатюра).\n";
    std::cout << "На сцене всего"<< dancersCount << "артистов.\n";
 }

 else if (dancersCount<=30){
    std::cout <<"Этот классический баллет.\n";
 }

 else{
    std::cout<< "Этот Гранд-Балет(эпическое зрелище)!\n";
 }

}