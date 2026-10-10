#include "../include/Sensor.h"
#include <cstdlib>
void Sensor::relatif(const Vector2& robot, double arah, const Vector2& target, int& maju, int& samping) {
    int dx, dy; selisihPetak(robot, target, dx, dy);  
    const Vector2 d = vektorArah(arah);               
    maju    = static_cast<int>(dx * d.x + dy * d.y);    // proyeksi ke depan
    samping = static_cast<int>(-dx * d.y + dy * d.x);   // proyeksi ke kiri (kiri = (-d.y, d.x))
}
Vector2 Sensor::global(const Vector2& robot, double arah, int maju, int samping) {
    const Vector2 d = vektorArah(arah);
    return {robot.x + (d.x * maju - d.y * samping) * UKURAN_PETAK,
            robot.y + (d.y * maju + d.x * samping) * UKURAN_PETAK};
}
bool Sensor::petakTerlihat(int maju, int samping) {
    return maju >= 1 && maju <= 3 && std::abs(samping) <= maju;
}
bool Sensor::melihatBola(const Vector2& posisiRobot, double arahRobot, const Ball& bola) const {
    int m, s; relatif(posisiRobot, arahRobot, bola.getPosisi(), m, s);
    return petakTerlihat(m, s);
}
Vector2 Sensor::bacaPosisiBola(const Ball& bola) const { return bola.getPosisi(); }
