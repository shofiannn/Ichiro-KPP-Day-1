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
    //menghitung arah bola
    arahGerak = normalisasiVektor({target.x - posisiBola.x, target.y - posisiBola.y});

    //menghentikan bola jika target berada tepat di posisi bola
    if (arahGerak.x == 0.0 && arahGerak.y == 0.0) {
        moving = false;
        kecepatanBola = 0;
        return;
    }

    //mengatur kecepatan awal bola
    kecepatanBola = 3;
    moving = true;
}

std::string Ball::update(const Field& field) {
    //menghentikan bola jika kecepatannya habis
    if (!moving || kecepatanBola <= 0) {
        moving = false;
        kecepatanBola = 0;
        return "Bola berhenti.";
    }

    //menyimpan posisi lama bola
    const Vector2 lama = posisiBola;

    //memperbarui posisi bola berdasarkan arah gerak dan kecepatannya
    posisiBola.x += arahGerak.x * kecepatanBola;
    posisiBola.y += arahGerak.y * kecepatanBola;

    //memeriksa apakah lintasan bola melewati garis gawang
    if (arahGerak.x > 0.0 && lama.x <= field.getMaxX() && posisiBola.x >= field.getMaxX()) {
        //menghitung posisi perpotongan bola dengan garis gawang
        const double t = (field.getMaxX() - lama.x) / (posisiBola.x - lama.x);
        const double ySaatGawang = lama.y + t * (posisiBola.y - lama.y);

        //memeriksa apakah bola melewati bukaan gawang
        if (ySaatGawang >= field.getGoalMinY() && ySaatGawang <= field.getGoalMaxY()) {
            //Memindahkan bola sedikit melewati garis gawang
            posisiBola = {field.getMaxX() + 0.01, ySaatGawang};

            //menghentikan bola setelah berhasil mencetak gol
            moving = false;
            kecepatanBola = 0;
            return "GOOOL! Bola melewati bukaan gawang.";
        }
    }

    //memeriksa apakah bola keluar dari batas lapangan
    if (field.isOutOfBounds(posisiBola)) {
        //Mengembalikan bola ke tengah lapangan jika keluar batas
        respawn(field);
        return "Bola keluar lapangan. Bola di-respawn ke tengah lapangan.";
    }

    //mengurangi kecepatan bola satu tingkat setiap tick
    --kecepatanBola;

    //menghentikan bola jika kecepatannya sudah habis
    if (kecepatanBola <= 0) {
        kecepatanBola = 0;
        moving = false;
    }

    //mengembalikan status pergerakan dan sisa kecepatan bola
    return "Bola bergerak. Kecepatan tersisa: " + std::to_string(kecepatanBola) + ".";
}

void Ball::respawn(const Field& field) {
    //mengembalikan posisi bola ke tengah lapangan
    posisiBola = field.getTengahLapangan();
    arahGerak = {0.0, 0.0};
    kecepatanBola = 0;
    moving = false;
}