#include "include/Config.h"
#include "include/Simulator.h"
#include "include/InvalidActionException.h"
#include <exception>
#include <iostream>

int main() {
    try {
        // Membaca konfigurasi. Jika config.txt tidak ada, nilai default digunakan.
        const Config config = Config::loadFromFile("config.txt");

        // Simulator mengelola lapangan, bola, robot, dan semua tick.
        Simulator simulator(config);
        simulator.run();
    } catch (const InvalidActionException& error) {
        std::cerr << "Aksi tidak valid: " << error.what() << "\n";
        return 1;
    } catch (const std::exception& error) {
        std::cerr << "Terjadi kesalahan: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
