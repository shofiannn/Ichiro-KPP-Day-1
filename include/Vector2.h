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

// [BARU] 1 petak grid ASCII = 0.5 m
const double UKURAN_PETAK = 0.5;
// [BARU] sudut kelipatan 90 derajat -> vektor arah (1,0),(0,1),(-1,0),(0,-1)
Vector2 vektorArah(double derajat);
// [BARU] selisih a->b dalam jumlah petak (bilangan bulat)
void selisihPetak(const Vector2& a, const Vector2& b, int& dx, int& dy);
// [BARU] true jika a dan b ada di petak yang sama
bool samaPetak(const Vector2& a, const Vector2& b);
#endif