#include "../include/Vector2.h"
#include <cmath>

double jarak(const Vector2& a, const Vector2& b){
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

double sudut(const Vector2& a, const Vector2& b){
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double sudut = std::atan2(dy, dx) * 180.0 / M_PI;
    return normalisasiSudut(sudut);
}

double normalisasiSudut(double sudut){
    if(sudut > 180.0) sudut -= 360.0;
    else if(sudut < -180.0) sudut += 360.0;
    return sudut;
}