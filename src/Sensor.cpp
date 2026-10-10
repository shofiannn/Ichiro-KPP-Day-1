#include "../include/Sensor.h"

//membuat sensor dengan jarak deteksi sesuai nilai yang diberikan
Sensor::Sensor(double jarakMaksimal) : jarakDeteksi(jarakMaksimal) {}

//memeriksa apakah bola berada dalam jangkauan deteksi sensor
bool Sensor::melihatBola(const Vector2& posisiRobot, const Ball& bola) const {
    return jarak(posisiRobot, bola.getPosisi()) <= jarakDeteksi;
}

//membaca dan mengambil posisi bola saat ini
Vector2 Sensor::bacaPosisiBola(const Ball& bola) const {
    return bola.getPosisi(); //mengembalikan koordinat posisi bola
}