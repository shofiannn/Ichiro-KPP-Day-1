#ifndef FIELD_H
#define FIELD_H

#include "Vector2.h"
#include <string>

class Field {
private:
    const double lebarLapangan = 9.0;
    const double panjangLapangan = 6.0;
    const double minX = -4.5;
    const double maxX = 4.5;
    const double minY = -3.0;
    const double maxY = 3.0;
    const double lebarGawang = 3.0;

public:
    Field();

    double getMinX() const;
    double getMaxX() const;
    double getMinY() const;
    double getMaxY() const;
    double getLebarLapangan() const;
    double getPanjangLapangan() const;
    double getLebarGawang() const;
    double getGoalMinY() const;
    double getGoalMaxY() const;
    Vector2 getTengahLapangan() const;

    //mengecek apakah titik masih berada di dalam batas lapangan
    bool isInside(const Vector2& posisi) const;

    //mengecek apakah bola sudah di area gawang
    bool isInsideGoal(const Vector2& posisi) const;

    //mengecek apakah bola keluar dari lapangan
    bool isOutOfBounds(const Vector2& posisi) const;

    //visualisasi lapangan
    void render(const Vector2& posisiRobot, double arahRobot, const Vector2& posisiBola,
                const std::string& status, int tick) const;
    Vector2 snap(const Vector2& p) const;
};

#endif
