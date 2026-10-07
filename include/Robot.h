#ifndef ROBOT_H
#define ROBOT_H

#include "Vector2.h"

class Robot {
protected:
    //posisi robot
    Vector2 posisiRobot;

    //arah robot dalam derajat
    double arahRobot;

    //kecepatan robot
    double kecepatanRobot;

public:
    //constructor
    Robot(
        const Vector2& posisiAwalRobot,
        double arahAwalRobot = 0.0
    );

    //destructor
    virtual ~Robot() = default;

    Vector2 getPosisiRobot() const;
    double getArahRobot() const;
    double getKecepatanRobot() const;

    void setPosisiRobot(const Vector2& newPosisiRobot);
    void setArahRobot(double newArahRobot);
    void setKecepatanRobot(double newKecepatanRobot);

    //class turunan bisa membuat function think sendiri
    virtual void think() = 0;
};

#endif