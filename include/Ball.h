#ifndef BALL_H
#define BALL_H

#include "Vector2.h"

class Ball {
private:
    Vector2 posisiBola;
    Vector2 kecepatanBola;
    bool moving;

public:
    Ball();
    Ball(const Vector2& posisiAwalBola);

    Vector2 getPosisi() const;
    Vector2 getKecepatan() const;

    bool isMoving() const;

    //mengubah posisi bola
    void setPosisi(const Vector2& posisiBaru);


    void kick(const Vector2& arahTendangan);

    //mengubah posisi bola berdasarkan velocity
    void update();
};

#endif