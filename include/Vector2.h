#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2{
    double x;
    double y;
};

double jarak(const Vector2& a, const Vector2& b);
double sudut(const Vector2& a, const Vector2& b);
double normalisasiSudut(double sudut);

#endif