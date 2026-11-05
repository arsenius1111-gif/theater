#ifndef PERFORMANCEMENU_H
#define PERFORMANCEMENU_H

#include "Performance.h"
#include "Collection.h"
#include <memory>

class PerformanceMenu {
public:
    static void showAll(
        const Collection<std::shared_ptr<Performance>>& catalog);

    static void create(
        Collection<std::shared_ptr<Performance>>& catalog);

    static void compare(
        const Collection<std::shared_ptr<Performance>>& catalog);

    static void showInheritanceDemo();

    static void manageCollection(
        Collection<std::shared_ptr<Performance>>& catalog);
};

#endif