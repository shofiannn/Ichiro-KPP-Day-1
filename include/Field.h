#ifndef FIELD_H
#define FIELD_H
#include "Vector2.h"

class Field
{
private:
    //ukuran lapangan
    const double lebarLapangan = 9.0;
    const double panjangLapangan = 6.0;
    //batas titik x dan y
    const double minX = -4.5;
    const double maxX = 4.5;
    const double minY = -3.0;
    const double maxY = 3.0;
    //lebar gawang
    const double lebarGawang = 3.0;
public:
    //constructor
    Field();
    //mengambil nilai x dan y
    double getMinX() const;
    double getMaxX() const;
    double getMinY() const;
    double getMaxY() const;
    //mengambil nilai lebarGawang
    double getLebarGawang() const;
    //mengecek apakah suatu titik di lapangan atau tidak
    bool isInside(const Vector2& position) const;
    //mengecek apakah bola di gawang atau tidak
    bool isInsideGoal(const Vector2& position) const;
};
#endif