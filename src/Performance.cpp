#include "Performance.h"
#include "../exceptions/InvalidDataException.h"

Performance::Performance()
: title(""), director(""), genre("") {}

Performance::Performance(std::string_view title_,
std::string_view director_, std::string_view genre_,
int duration_, int ageRestriction_)
: title(title_),
director(director_),
genre(genre_),
duration(duration_),
ageRestriction(ageRestriction_) {

if (duration_ <= 0) {
    throw InvalidDataException(
        "Длительность спектакля должна быть положительной.");
}

if (ageRestriction_ < 0) {
    throw InvalidDataException(
        "Возрастное ограничение не может быть отрицательным.");
}
}

std::string Performance::getTitle() const {
return title;
}

std::string Performance::getDirector() const {
return director;
}

std::string Performance::getGenre() const {
return genre;
}

int Performance::getDuration() const {
return duration;
}

int Performance::getAgeRestriction() const {
return ageRestriction;
}

void Performance::setTitle(std::string_view title_) {
title = title_;
}

void Performance::setDirector(std::string_view director_) {
director = director_;
}

void Performance::setGenre(std::string_view genre_) {
genre = genre_;
}

void Performance::setDuration(int duration_) {
if (duration_ <= 0) {
throw InvalidDataException(
"Длительность спектакля должна быть положительной.");
}

duration = duration_;
}

void Performance::setAgeRestriction(int ageRestriction_) {
if (ageRestriction_ < 0) {
throw InvalidDataException(
"Возрастное ограничение не может быть отрицательным.");
}

ageRestriction = ageRestriction_;
}

std::string Performance::getType() const {
return "Спектакль";
}

void Performance::displayInfo() const {
std::cout << "Тип: " << getType() << '\n';
std::cout << "Название: " << title << '\n';
std::cout << "Режиссёр: " << director << '\n';
std::cout << "Жанр: " << genre << '\n';
std::cout << "Длительность: " << duration << " мин.\n";
std::cout << "Возрастное ограничение: "
<< ageRestriction << "+\n";
}

bool Performance::operator==(const Performance& other) const {
return title == other.title;
}

std::strong_ordering Performance::operator<=>(
const Performance& other) const {
return duration <=> other.duration;
}

void printPerformanceSecretDetails(const Performance& p) {
std::cout << "Закрытая информация о спектакле:\n";
std::cout << "Название: " << p.title << '\n';
std::cout << "Режиссёр: " << p.director << '\n';
std::cout << "Длительность: " << p.duration << " мин.\n";
}