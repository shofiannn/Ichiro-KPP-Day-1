#include "../include/Ball.h"
#include <string>

Ball::Ball() : posisiBola{0.0, 0.0}, arahGerak{0.0, 0.0},
               kecepatanBola(0), moving(false) {}

Ball::Ball(const Vector2& posisiAwalBola)
    : posisiBola(posisiAwalBola), arahGerak{0.0, 0.0},
      kecepatanBola(0), moving(false) {}

Vector2 Ball::getPosisi() const { return posisiBola; }
int Ball::getKecepatan() const { return kecepatanBola; }
bool Ball::isMoving() const { return moving; }

void Ball::setPosisi(const Vector2& posisiBaru) {
    posisiBola = posisiBaru;
}

void Ball::kick(const Vector2& target) {
    //arah dibuat berupa langkah petak (-1/0/1) supaya bola lurus atau diagonal 45 derajat di grid
    const double dx = target.x - posisiBola.x, dy = target.y - posisiBola.y;
    arahGerak = {static_cast<double>((dx > 0) - (dx < 0)), static_cast<double>((dy > 0) - (dy < 0))};
    if (arahGerak.x == 0.0 && arahGerak.y == 0.0) { moving = false; kecepatanBola = 0; return; }
    kecepatanBola = 3; // 3 m/tick
    moving = true;
}
std::string Ball::update(const Field& field) {
    if (!moving || kecepatanBola <= 0) { moving = false; kecepatanBola = 0; return "Bola berhenti."; }
    const int jumlahPetak = kecepatanBola * 2;                 // 3 m = 6 petak, 2 m = 4 petak, 1 m = 2 petak
    for (int i = 0; i < jumlahPetak; ++i) {
        posisiBola.x += arahGerak.x * UKURAN_PETAK;           
        posisiBola.y += arahGerak.y * UKURAN_PETAK;
        if (field.isInsideGoal(posisiBola)) {                 
            moving = false; kecepatanBola = 0;
            return "GOOOL! Bola melewati bukaan gawang.";
        }
        if (field.isOutOfBounds(posisiBola)) {                 // keluar lapangan -> RESPAWN
            respawn(field);
            return "Bola keluar lapangan. Bola di-respawn ke tengah lapangan.";
        }
    }
    --kecepatanBola;                                           // melambat 1 m/tick
    if (kecepatanBola <= 0) { kecepatanBola = 0; moving = false; }
    return "Bola bergerak. Kecepatan tersisa: " + std::to_string(kecepatanBola) + ".";
}
void Ball::respawn(const Field& field) {
    //mengembalikan posisi bola ke tengah lapangan
    posisiBola = field.snap(field.getTengahLapangan()); //dibulatkan ke pusat petak
    arahGerak = {0.0, 0.0};
    kecepatanBola = 0;
    moving = false;
}