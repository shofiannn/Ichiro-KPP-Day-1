#ifndef SENSOR_H
#define SENSOR_H
#include "Vector2.h"
#include "Ball.h"

class Sensor {
public:
    static void relatif(const Vector2& robot, double arah, const Vector2& target, int& maju, int& samping);
    static Vector2 global(const Vector2& robot, double arah, int maju, int samping);
    static bool petakTerlihat(int maju, int samping);
    //cek apakah bola di dalam segitiga
    bool melihatBola(const Vector2& posisiRobot, double arahRobot, const Ball& bola) const;
    Vector2 bacaPosisiBola(const Ball& bola) const; // hanya dipanggil setelah melihatBola() true
};
#endif