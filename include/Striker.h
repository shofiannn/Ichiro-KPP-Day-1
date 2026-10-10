#ifndef STRIKER_H
#define STRIKER_H

#include "Robot.h"
#include "Sensor.h"
#include "StrikerState.h"
#include <memory> 

class Striker : public Robot {
private:
    Sensor sensor; //menyimpan sensor yang digunakan oleh striker
    std::unique_ptr<StrikerState> state; //menyimpan state perilaku striker yang sedang aktif
    bool sudahMenendang; //menandai apakah striker sudah melakukan tendangan
    const double jarakTendang = 0.55; //menentukan jarak maksimal striker untuk melakukan tendangan

public:
    Striker(const Vector2& posisiAwalStriker, double arahAwalStriker = 0.0); //membuat striker dengan posisi dan arah hadap awal
    ~Striker() override; //menghancurkan objek striker dengan benar

    void think() override; //menjalankan perilaku berpikir striker

    //menjalankan aksi state aktif pada tick ini
    std::string update(Ball& bola, const Field& field);

    void changeState(StrikerState* stateBaru); //mengganti state aktif dengan state baru
    std::string getNamaState() const; //mengambil nama state yang sedang aktif

    Sensor& getSensor(); //mengembalikan referensi ke sensor milik striker
    double getJarakTendang() const; //mengambil jarak tendang striker
    bool hasKicked() const; //memeriksa apakah striker sudah menendang
    void setSudahMenendang(bool nilai); //mengubah status apakah striker sudah menendang
};

#endif