#ifndef MAINMENU_H
#define MAINMENU_H

#include "Hall.h"
#include "Performance.h"
#include "Collection.h"
#include <memory>

class MainMenu {
private:
    Collection<Hall> halls;
    Collection<std::shared_ptr<Performance>> catalog;

    void initDatabase();
    void clearInput() const;

public:
    MainMenu();
    void run();
};

#endif