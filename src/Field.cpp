#include "../include/Field.h"

Field::Field(){}

double Field::getMinX() const{return minX;}
double Field::getMaxX() const{return maxX;}
double Field::getMinY() const{return minY;}
double Field::getMaxY() const{return maxY;}
double Field::getLebarGawang() const{return lebarGawang;}

//mengecek apakah posisi di
bool Field::isInside(const Vector2& position) const{
    double goalMinY = -lebarGawang / 2.0;
    double goalMaxY = lebarGawang / 2.0;
    return {
        position.x == maxX &&
        position.y >= goalMinY &&
        position.y <= goalMaxY
    };
}