#include "../include/Robot.h"
#include "../include/InvalidActionException.h"
#include <cmath>
#include <cstdlib>

//membuat robot dengan posisi awal, arah hadap awal, dan kecepatan awal nol
Robot::Robot(const Vector2& posisiAwalRobot, double arahAwalRobot)
    : posisiRobot(posisiAwalRobot),
      arahRobot(normalisasiSudut(arahAwalRobot)),
      kecepatanRobot(0.0),
      posisiAwal(posisiAwalRobot), //[BARU] simpan titik respawn
      arahAwal(normalisasiSudut(arahAwalRobot)) {}
//RESPAWN ROBOT: posisi, arah, kecepatan kembali ke nilai awal
void Robot::respawn() {
    posisiRobot = posisiAwal;
    arahRobot = arahAwal;
    kecepatanRobot = 0.0;
}

//mengembalikan posisi robot saat ini
Vector2 Robot::getPosisiRobot() const { return posisiRobot; }

//mengembalikan arah hadap robot saat ini
double Robot::getArahRobot() const { return arahRobot; }

//mengembalikan kecepatan robot saat ini
double Robot::getKecepatanRobot() const { return kecepatanRobot; }

//mengubah posisi robot menjadi posisi baru
void Robot::setPosisiRobot(const Vector2& posisiBaru) {
    posisiRobot = posisiBaru;
}

//mengubah arah hadap robot setelah menormalkan sudutnya
void Robot::setArahRobot(double arahBaru) {
    arahRobot = normalisasiSudut(arahBaru);
}

//mengatur kecepatan robot agar tetap berada dalam rentang 0 hingga 0,5 meter per tick
void Robot::setKecepatanRobot(double kecepatanBaru) {
    //kecepatan tidak boleh negatif atau melebihi 0,5 meter per tick
    if (kecepatanBaru < 0.0) kecepatanRobot = 0.0; //mengatur kecepatan menjadi nol jika nilainya negatif
    else if (kecepatanBaru > 0.5) kecepatanRobot = 0.5; //membatasi kecepatan maksimal menjadi 0,5 meter per tick
    else kecepatanRobot = kecepatanBaru;
}

//menggerakkan robot menuju target
void Robot::moveToward(const Vector2& target, const Field& field, const Vector2* halangan) {
    (void)field;
    int dx, dy; selisihPetak(posisiRobot, target, dx, dy);           // jarak ke target dalam petak
    if (dx == 0 && dy == 0) { kecepatanRobot = 0.0; return; }        // sudah sampai
    bool geserX = std::abs(dx) >= std::abs(dy);                      // pilih sumbu dengan selisih terbesar
    auto langkah = [&](bool sumbuX) {                                // vektor 1 petak pada sumbu yang dipilih
        return Vector2{sumbuX ? ((dx > 0) - (dx < 0)) * UKURAN_PETAK : 0.0,
                       sumbuX ? 0.0 : ((dy > 0) - (dy < 0)) * UKURAN_PETAK};
    };
    Vector2 s = langkah(geserX);
    Vector2 baru{posisiRobot.x + s.x, posisiRobot.y + s.y};
    if (halangan && samaPetak(baru, *halangan)) {                    // terhalang bola -> menyamping 1 petak
        s = geserX ? Vector2{0.0, (posisiRobot.y + UKURAN_PETAK <= field.getMaxY()) ? UKURAN_PETAK : -UKURAN_PETAK}
                   : Vector2{(dx >= 0 ? UKURAN_PETAK : -UKURAN_PETAK), 0.0};
        baru = {posisiRobot.x + s.x, posisiRobot.y + s.y};
    }
    arahRobot = normalisasiSudut(sudut({0.0, 0.0}, s));              // hadap ke arah jalan (sudut dari modul math, DRY)
    posisiRobot = baru;
    kecepatanRobot = UKURAN_PETAK;                                   // 0,5 m/tick
}
