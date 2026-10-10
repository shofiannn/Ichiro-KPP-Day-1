#ifndef SENSOR_H
#define SENSOR_H

#include "Vector2.h"
#include "Ball.h"

class Sensor {
private:
    double jarakDeteksi; //menyimpan jarak maksimal sensor untuk mendeteksi bola

public:
    explicit Sensor(double jarakMaksimal = 9.0); //membuat sensor dengan jarak deteksi awal 9 meter
    bool melihatBola(const Vector2& posisiRobot, const Ball& bola) const; //memeriksa apakah bola berada dalam jangkauan sensor dari posisi robot
    Vector2 bacaPosisiBola(const Ball& bola) const; //mengambil posisi bola yang terdeteksi oleh sensor
};

#endif