#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Field.h"
#include "Ball.h"
#include "Striker.h"
#include "Config.h"

//mengatur dan menjalankan seluruh proses simulasi
class Simulator {
private:
    Field field; //menyimpan objek lapangan yang digunakan dalam simulasi
    Ball ball; //menyimpan objek bola yang digunakan dalam simulasi
    Striker striker; //menyimpan objek robot penyerang dalam simulasi
    int maksimalTick; //menyimpan jumlah tick maksimal simulasi
    int jedaMilidetik; //menyimpan jeda waktu antar tick dalam milidetik
    bool golTerjadi; //menandai apakah gol sudah terjadi

public:
    explicit Simulator(const Config& config); //membuat simulator berdasarkan konfigurasi yang diberikan
    void run(); //menjalankan proses simulasi
};

#endif