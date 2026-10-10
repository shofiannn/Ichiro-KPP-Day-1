#ifndef BALL_H
#define BALL_H

#include "Vector2.h"
#include "Field.h"

class Ball {
private:
    Vector2 posisiBola;
    Vector2 arahGerak;
    int kecepatanBola;
    bool moving;

public:
    Ball();
    explicit Ball(const Vector2& posisiAwalBola);

    Vector2 getPosisi() const;
    int getKecepatan() const;
    bool isMoving() const;
    void setPosisi(const Vector2& posisiBaru);

    //mengarahkan tendangan ke gawang
    void kick(const Vector2& target);

    //memeriksa tiap perpindahan bola apakah gol atau bola keluar lapangan
    std::string update(const Field& field);

    //nge respawn bola ke tengah lapangan
    void respawn(const Field& field);
};

#endif
