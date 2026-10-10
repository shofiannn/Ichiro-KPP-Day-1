#include "../include/Vector2.h"
#include <cmath>

//rumus euclidean
double jarak(const Vector2& a, const Vector2& b) {
    const double dx = b.x - a.x;
    const double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

double sudut(const Vector2& a, const Vector2& b) {
    const double dx = b.x - a.x;
    const double dy = b.y - a.y;
    const double derajat = std::atan2(dy, dx) * 180.0 / 3.14159265358979323846; //menghitung sudut dalam derajat
    return normalisasiSudut(derajat);
}

double normalisasiSudut(double nilaiSudut) {
    while (nilaiSudut > 180.0) nilaiSudut -= 360.0; //mengurangi sudut jika lebih dari 180 derajat.
    while (nilaiSudut < -180.0) nilaiSudut += 360.0; //menambah sudut jika kurang dari -180 derajat.
    return nilaiSudut;
}

Vector2 normalisasiVektor(const Vector2& v) {
    const double panjang = std::sqrt(v.x * v.x + v.y * v.y);
    if (panjang == 0.0) return {0.0, 0.0};
    return {v.x / panjang, v.y / panjang};
}
//cos/sin dibulatkan
Vector2 vektorArah(double derajat) {
    const double rad = derajat * 3.14159265358979323846 / 180.0;
    return {std::round(std::cos(rad)), std::round(std::sin(rad))};
}
//selisih posisi dibagi 0.5 m lalu dibulatkan
void selisihPetak(const Vector2& a, const Vector2& b, int& dx, int& dy) {
    dx = static_cast<int>(std::lround((b.x - a.x) / UKURAN_PETAK));
    dy = static_cast<int>(std::lround((b.y - a.y) / UKURAN_PETAK));
}
//sama jika selisihnya 0 petak
bool samaPetak(const Vector2& a, const Vector2& b) {
    int dx, dy; selisihPetak(a, b, dx, dy);
    return dx == 0 && dy == 0;
}