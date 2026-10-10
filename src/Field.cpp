#include "../include/Field.h"
#include <iostream>
#include <cmath>

Field::Field() {}

double Field::getMinX() const { return minX; }
double Field::getMaxX() const { return maxX; }
double Field::getMinY() const { return minY; }
double Field::getMaxY() const { return maxY; }
double Field::getLebarLapangan() const { return lebarLapangan; }
double Field::getPanjangLapangan() const { return panjangLapangan; }
double Field::getLebarGawang() const { return lebarGawang; }
double Field::getGoalMinY() const { return -lebarGawang / 2.0; }
double Field::getGoalMaxY() const { return lebarGawang / 2.0; }
Vector2 Field::getTengahLapangan() const { return {0.0, 0.0}; }

//memeriksa apakah koordinat x dan y di lapangan atau tidak
bool Field::isInside(const Vector2& p) const {
    return p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY;
}

bool Field::isInsideGoal(const Vector2& p) const {
    //memeriksa apakah melewati sisi kanan lapangan melalui bukaan gawang
    return p.x > maxX && p.y >= getGoalMinY() && p.y <= getGoalMaxY();
}

bool Field::isOutOfBounds(const Vector2& p) const {
    //dianggap keluar jika melewati batas bawah, atas, atau kiri
    if (p.y < minY || p.y > maxY || p.x < minX) return true;
    //bola di sisi kanan tidak dianggap keluar bila melewati bukaan gawang
    if (p.x > maxX && !isInsideGoal(p)) return true;
    return false;
}

//visualisasi
void Field::render(const Vector2& robot, const Vector2& ball,
                   const std::string& status, int tick) const {
    //satu karakter mewakili 0,5 meter
    constexpr int kolom = 18;
    constexpr int baris = 12;

    //mengubah koordinat x menjadi indeks kolom di lapangan
    auto keKolom = [&](double x) {
        int c = static_cast<int>(std::round((x - minX) / lebarLapangan * kolom));
        if (c < 0) c = 0;
        if (c > kolom) c = kolom;
        return c;
    };
    //mengubah koordinat y menjadi indeks baris di lapangan
    auto keBaris = [&](double y) {
        int r = static_cast<int>(std::round((maxY - y) / panjangLapangan * baris));
        if (r < 0) r = 0;
        if (r > baris) r = baris;
        return r;
    };

    std::cout << "\n========== TICK " << tick << " ==========\n";
    std::cout << status << "\n";
    std::cout << "+";
    for (int c = 0; c <= kolom; ++c) std::cout << "--";
    std::cout << "+\n";

    for (int r = 0; r <= baris; ++r) {
        std::cout << "|";
        for (int c = 0; c <= kolom; ++c) {
            char simbol = ' ';
            // Tandai area gawang di tengah sisi kanan.
            const double yAtRow = maxY - (static_cast<double>(r) / baris) * panjangLapangan;
            const bool areaGawang = yAtRow <= getGoalMaxY() && yAtRow >= getGoalMinY();

            if (c == keKolom(robot.x) && r == keBaris(robot.y)) simbol = 'R';
            if (c == keKolom(ball.x) && r == keBaris(ball.y))
                simbol = (simbol == 'R') ? '*' : 'B';

            if (c == kolom && areaGawang && simbol == ' ') simbol = '=';
            std::cout << simbol << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "+";
    for (int c = 0; c <= kolom; ++c) std::cout << "--";
    std::cout << "+\n";
    std::cout << "R = Robot | B = Bola | * = posisi robot dan bola bertumpuk | = = bukaan gawang\n";
    std::cout << "Robot (" << robot.x << ", " << robot.y << ")"
              << " | Bola (" << ball.x << ", " << ball.y << ")\n";
}
