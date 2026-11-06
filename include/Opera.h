#ifndef OPERA_H
#define OPERA_H

#include "Performance.h"

class Opera : public Performance {
private:
    bool hasRecitatives = false;

public:
    Opera(
        std::string_view title_,
        std::string_view director_,
        int duration_,
        int ageRestriction_,
        bool hasRecitatives_
    );

    bool getHasRecitatives() const;
    void setHasRecitatives(bool value);

    std::string getType() const override;
    void displayInfo() const override;
    void performSpecialAction() const override;
};

#endif