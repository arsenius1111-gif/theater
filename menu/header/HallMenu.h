#ifndef HALLMENU_H
#define HALLMENU_H

#include "Hall.h"
#include "Performance.h"
#include "Collection.h"
#include <memory>

class HallMenu {
public:
    static void create(Collection<Hall>& halls);

    static void manage(
        Collection<Hall>& halls,
        const Collection<std::shared_ptr<Performance>>& catalog);
};

#endif