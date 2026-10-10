#include "../include/Simulator.h"
#include "../include/InvalidActionException.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/StrikerState.h"

//membuat simulator berdasarkan konfigurasi yang diberikan
Simulator::Simulator(const Config& config)
    : field(), //membuat objek lapangan menggunakan nilai default
      ball(field.snap(config.posisiAwalBola)), 
      striker(field.snap(config.posisiAwalRobot)), 
      maksimalTick(config.maksimalTick), //menyimpan batas maksimal tick simulasi
      jedaMilidetik(config.jedaMilidetik), //menyimpan jeda waktu antar tick
      golTerjadi(false),
      ujiRespawn(config.ujiRespawn) {} //menandai bahwa belum ada gol yang terjadi

//menjalankan seluruh proses simulasi robot sepak bola
void Simulator::run() {
    std::cout << "=== ICHIRO ROBOT SOCCER SIMULATOR ===\n"; //menampilkan judul simulasi
    std::cout << "Lapangan 9 x 6 meter | Gawang kanan selebar 3 meter\n"; //menampilkan informasi ukuran lapangan dan gawang
    std::cout << "Tekan Ctrl+C jika ingin menghentikan program.\n"; //memberi tahu cara menghentikan program

    //mengulang simulasi dari tick pertama hingga batas maksimal
    for (int tick = 1; tick <= maksimalTick; ++tick) {
        std::string status; //menyimpan informasi aktivitas yang terjadi pada tick ini

        try {
            if (ujiRespawn && tick == 3) {                       //paksa keluar lapangan untuk uji respawn
                striker.setPosisiRobot({10.25, 0.25});
                ball.setPosisi({-9.75, 0.25});
                std::cout << "\n>>> UJI RESPAWN: robot & bola dipindah paksa keluar lapangan\n";
            }
            const std::string namaState = striker.getNamaState(); //ambil nama SEBELUM update
            status = "[" + namaState + "] " + striker.update(ball, field);
            if (ball.isMoving()) {
                const std::string s = ball.update(field);
                status += " | " + s;
                if (s.find("GOOOL!") != std::string::npos) golTerjadi = true;
            }
        } catch (const InvalidActionException& error) {
            //aksi tidak valid: cukup dilaporkan
            std::cerr << "Aksi tidak valid: " << error.what() << "\n";
            status = std::string("Aksi tidak valid: ") + error.what();
        }
        //robot keluar lapangan -> RESPAWN ROBOT
        if (!field.isInside(striker.getPosisiRobot())) {
            striker.respawn();
            status += " | Robot keluar lapangan -> RESPAWN ROBOT.";
        }
        //bola keluar lapangan -> RESPAWN BOLA
        if (!golTerjadi && field.isOutOfBounds(ball.getPosisi())) {
            ball.respawn(field);
            status += " | Bola keluar lapangan -> RESPAWN BOLA.";
        }
        field.render(striker.getPosisiRobot(), striker.getArahRobot(), ball.getPosisi(), status, tick);
        //mengakhiri simulasi jika gol sudah terjadi
        if (golTerjadi) {
            std::cout << "\nSIMULASI SELESAI: ICHIRO BERHASIL MENCETAK GOL!\n"; //menampilkan pesan keberhasilan simulasi
            return; //menghentikan fungsi run
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(jedaMilidetik)); //memberi jeda sebelum menjalankan tick berikutnya
    }

    std::cout << "\nSimulasi selesai karena batas tick tercapai.\n"; //menampilkan pesan jika simulasi berakhir karena batas tick
}