#include "../include/Field.h"

Field::Field(){}

double Field::getMinX() const{return minX;}
double Field::getMaxX() const{return maxX;}
double Field::getMinY() const{return minY;}
double Field::getMaxY() const{return maxY;}
double Field::getLebarGawang() const{return lebarGawang;}

//mengecek apakah posisi di
bool Field::isInside(const Vector2& posisi) const{
    double goalMinY = -lebarGawang / 2.0;
    double goalMaxY = lebarGawang / 2.0;
    return {
        posisi.x == maxX &&
        posisi.y >= goalMinY &&
        posisi.y <= goalMaxY
    };
}