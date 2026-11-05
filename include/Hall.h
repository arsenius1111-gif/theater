#ifndef HALL_H
#define HALL_H

#include "Performance.h"
#include "Collection.h"
#include <memory>

class Hall {
private:
    int number = 0;
    int capacity = 0;
    int ticketsSold = 0;
    Collection<std::shared_ptr<Performance>> performances;

public:
    Hall(int number_, int capacity_);

    int getNumber() const;
    int getCapacity() const;
    int getTicketsSold() const;

    void setCapacity(int newCapacity);

    bool sellTickets(int count);
    bool addPerformance(std::shared_ptr<Performance> p);

    const Collection<std::shared_ptr<Performance>>&
        getPerformances() const;

    Collection<std::shared_ptr<Performance>>&
        getPerformances();

    void displayFullInfo() const;

    Hall& operator+=(std::shared_ptr<Performance> p);
    Hall& operator-=(const Performance& p);

    friend void printHallAnalytics(const Hall& hall);
};

#endif