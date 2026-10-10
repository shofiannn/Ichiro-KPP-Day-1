#include "../include/Field.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "../include/Sensor.h"

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

Vector2 Field::snap(const Vector2& p) const {
    const double k = std::floor((p.x - minX) / UKURAN_PETAK);
    const double b = std::floor((maxY - p.y) / UKURAN_PETAK);
    return {minX + (k + 0.5) * UKURAN_PETAK, maxY - (b + 0.5) * UKURAN_PETAK};
}
//visualisasi
void Field::render(const Vector2& robot, double arah, const Vector2& ball,
                   const std::string& status, int tick) const {
    constexpr int K = 18, B = 12;                              
    std::vector<std::string> g(B, std::string(K, '.'));    // semua petak kosong '.', kolom ke-K khusus gawang
    auto taruh = [&](const Vector2& p, char s) {
        const int c = static_cast<int>(std::floor((p.x - minX) / UKURAN_PETAK));
        const int r = static_cast<int>(std::floor((maxY - p.y) / UKURAN_PETAK));
        if (r >= 0 && r < B && c >= 0 && c <= K) g[r][c] = s;
    };
    for (int r = 0; r < B; ++r) {                              // gawang '#'
        const double y = maxY - (r + 0.5) * UKURAN_PETAK;
        g[r][K] = (y >= getGoalMinY() && y <= getGoalMaxY()) ? '#' : ' ';
    }
    for (int f = 1; f <= 3; ++f)                               // area pandang '@'
        for (int l = -f; l <= f; ++l) {
            const Vector2 q = Sensor::global(robot, arah, f, l);
            if (isInside(q)) taruh(q, '@');
        }
    taruh(ball, 'O');                                         
    if (isInside(robot)) taruh(robot, 'R');                   
    std::cout << "\n========== TICK " << tick << " ==========\n" << status << "\n";
    for (const auto& baris : g) {                             
        std::string out;
        for (char ch : baris) { out += ch; out += ' '; }
        std::cout << out << "\n";
    }
    std::cout << "R=Robot @=Area pandang O=Bola .=Kosong #=Gawang\n";
    std::cout << "Robot (" << robot.x << ", " << robot.y << ") arah " << arah
              << " | Bola (" << ball.x << ", " << ball.y << ")\n";
}