#include "../include/Ball.h"

Ball::Ball(){
    posisiBola = {0.0, 0.0};
    kecepatanBola = {0.0, 0.0};
    moving = false;
}

Ball::Ball(const Vector2& posisiAwalBola){
    posisiBola = posisiAwalBola;
    kecepatanBola = {0.0, 0.0};
    moving = false; 
}

Vector2 Ball::getPosisi() const{
    return posisiBola;
}

Vector2 Ball::getKecepatan() const{
    return kecepatanBola;
}

bool Ball::isMoving() const{
    return moving;
}

//mengubah posisi bola yang lama menjadi posisi bola yang baru
void Ball::setPosisi(const Vector2& posisiBaru) {
    posisiBola = posisiBaru;
}

void Ball::kick(const Vector2& arahTendangan){
    kecepatanBola = arahTendangan;
    moving = true;
}

//mengubah posisi bola berdasarkan kecepatan saat ditendang
void Ball::update(){
    posisiBola.x += kecepatanBola.x;
    posisiBola.y += kecepatanBola.y;
} 