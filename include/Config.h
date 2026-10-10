#ifndef CONFIG_H
#define CONFIG_H

#include "Vector2.h"
#include <string>

//inisialisasi nilai awal
struct Config {
    double lebarLapangan = 9.0;
    double panjangLapangan = 6.0;
    double lebarGawang = 3.0;
    Vector2 posisiAwalRobot{-3.5, -2.0};
    Vector2 posisiAwalBola{2.5, -1.0};
    int maksimalTick = 80;
    int jedaMilidetik = 300;

    static Config loadFromFile(const std::string& namaFile);
};

#endif
