#include "../include/Robot.h"

//constructor
Robot::Robot(
    //implementasi constructor
    const Vector2& posisiAwalRobot,
    double arahAwalRobot
) {
    posisiRobot = posisiAwalRobot;
    arahRobot = normalisasiSudut(arahAwalRobot);
    kecepatanRobot = 0.0;
}

//mengambil posisi robot
Vector2 Robot::getPosisiRobot() const {
    return posisiRobot;
}

//mengambil arah robot
double Robot::getArahRobot() const {
    return arahRobot;
}

//mengambil kecepatan robot
double Robot::getKecepatanRobot() const {
    return kecepatanRobot;
}

//mengubah posisi robot
void Robot::setPosisiRobot(const Vector2& newPosisiRobot) {
    posisiRobot = newPosisiRobot;
}

//mengubah arah robot
void Robot::setArahRobot(double newArahRobot) {
    arahRobot = normalisasiSudut(newArahRobot);
}

//mengubah kecepatan robot
void Robot::setKecepatanRobot(double newKecepatanRobot) {
    //jika negatif => 0
    if (newKecepatanRobot < 0.0) {
        kecepatanRobot = 0.0;
    }
    //jika lebih dari 0.5 => 0m5
    else if (newKecepatanRobot > 0.5) {
        kecepatanRobot = 0.5;
    }
    //jika berada di rentang 0.0 - 0.5 => nilai tetap
    else {
        kecepatanRobot = newKecepatanRobot;
    }
}