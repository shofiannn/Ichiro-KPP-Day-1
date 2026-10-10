#ifndef VECTOR2_H
#define VECTOR2_H

//menyimpan koordinat x dan y
struct Vector2 {
    double x = 0.0;
    double y = 0.0;
};

//menghitung jarak dengan euclidean
double jarak(const Vector2& a, const Vector2& b);

//menghitung arah dari titik a ke titik b
double sudut(const Vector2& a, const Vector2& b);

//memastikan sudut berada di rentang -180 sampai 180 derajat
double normalisasiSudut(double nilaiSudut);

//menghasilkan vektor searah dengan vektor awal
Vector2 normalisasiVektor(const Vector2& v);

#endif
