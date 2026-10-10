#include "../include/Simulator.h"
#include "../include/InvalidActionException.h"
#include <iostream>
#include <thread>
#include <chrono>

//membuat simulator berdasarkan konfigurasi yang diberikan
Simulator::Simulator(const Config& config)
    : field(), //membuat objek lapangan menggunakan nilai default
      ball(config.posisiAwalBola), //membuat bola pada posisi awal dari konfigurasi
      striker(config.posisiAwalRobot), //membuat striker pada posisi awal dari konfigurasi
      maksimalTick(config.maksimalTick), //menyimpan batas maksimal tick simulasi
      jedaMilidetik(config.jedaMilidetik), //menyimpan jeda waktu antar tick
      golTerjadi(false) {} //menandai bahwa belum ada gol yang terjadi

//menjalankan seluruh proses simulasi robot sepak bola
void Simulator::run() {
    std::cout << "=== ICHIRO ROBOT SOCCER SIMULATOR ===\n"; //menampilkan judul simulasi
    std::cout << "Lapangan 9 x 6 meter | Gawang kanan selebar 3 meter\n"; //menampilkan informasi ukuran lapangan dan gawang
    std::cout << "Tekan Ctrl+C jika ingin menghentikan program.\n"; //memberi tahu cara menghentikan program

    //mengulang simulasi dari tick pertama hingga batas maksimal
    for (int tick = 1; tick <= maksimalTick; ++tick) {
        std::string status; //menyimpan informasi aktivitas yang terjadi pada tick ini

        try {
            //sebelum menendang, striker menjalankan state search, approach, align, atau kick
            if (!striker.hasKicked()) {
                status = "[" + striker.getNamaState() + "] " + striker.update(ball, field); //menjalankan state aktif striker dan menyimpan hasilnya
            } else if (ball.isMoving()) {
                //setelah ditendang, setiap tick memperbarui posisi bola
                status = ball.update(field); //memperbarui gerakan bola dan menyimpan statusnya
                if (status.find("GOOOL!") != std::string::npos) {
                    golTerjadi = true; //menandai bahwa gol berhasil terjadi jika pesan menunjukkan gol
                }
            } else {
                status = "Bola berhenti; simulasi tidak memiliki gerakan baru."; //menampilkan pesan jika bola sudah berhenti
            }

            field.render(striker.getPosisiRobot(), ball.getPosisi(), status, tick); //menampilkan kondisi lapangan, posisi robot, bola, status, dan tick
        } catch (const InvalidActionException& error) {
            //jika aksi melanggar aturan, tampilkan kesalahan dan pulihkan posisi bola
            std::cerr << "Aksi tidak valid: " << error.what() << "\n"; //menampilkan pesan kesalahan
            ball.respawn(field); //mengembalikan bola ke posisi respawn pada lapangan
            field.render(striker.getPosisiRobot(), ball.getPosisi(),
                         "Aksi gagal. Bola di-respawn ke tengah lapangan.", tick); //menampilkan kondisi lapangan setelah bola di-respawn
        }

        //mengakhiri simulasi jika gol sudah terjadi
        if (golTerjadi) {
            std::cout << "\nSIMULASI SELESAI: ICHIRO BERHASIL MENCETAK GOL!\n"; //menampilkan pesan keberhasilan simulasi
            return; //menghentikan fungsi run
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(jedaMilidetik)); //memberi jeda sebelum menjalankan tick berikutnya
    }

    std::cout << "\nSimulasi selesai karena batas tick tercapai.\n"; //menampilkan pesan jika simulasi berakhir karena batas tick
}