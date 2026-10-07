#ifndef STRIKER_H
#define STRIKER_H

#include "Robot.h"

class Striker : public Robot {
public:
    Striker(
        const Vector2& posisiAwalStriker,
        double arahAwalStriker = 0.0
    );

    void think() override;
};

#endif