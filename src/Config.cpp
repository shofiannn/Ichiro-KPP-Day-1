#include "../include/Config.h"
#include <fstream>
#include <sstream>
#include <string>

Config Config::loadFromFile(const std::string& namaFile) {
    Config config;
    std::ifstream file(namaFile);

    // Jika file belum ada, gunakan semua nilai default di Config.h.
    if (!file.is_open()) return config;

    std::string baris;
    while (std::getline(file, baris)) {
        // Abaikan baris kosong dan komentar yang dimulai dengan tanda #.
        if (baris.empty() || baris[0] == '#') continue;

        std::istringstream input(baris);
        std::string kunci, nilai;
        if (!std::getline(input, kunci, '=')) continue;
        if (!std::getline(input, nilai)) continue;

        std::istringstream angka(nilai);
        if (kunci == "field_width") angka >> config.lebarLapangan;
        else if (kunci == "field_height") angka >> config.panjangLapangan;
        else if (kunci == "goal_width") angka >> config.lebarGawang;
        else if (kunci == "robot_x") angka >> config.posisiAwalRobot.x;
        else if (kunci == "robot_y") angka >> config.posisiAwalRobot.y;
        else if (kunci == "ball_x") angka >> config.posisiAwalBola.x;
        else if (kunci == "ball_y") angka >> config.posisiAwalBola.y;
        else if (kunci == "max_ticks") angka >> config.maksimalTick;
        else if (kunci == "delay_ms") angka >> config.jedaMilidetik;
        else if (kunci == "test_respawn") { int v = 0; angka >> v; config.ujiRespawn = (v != 0); } 
    }
    return config;
}
