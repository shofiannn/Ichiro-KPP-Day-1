#ifndef STRIKER_STATE_H
#define STRIKER_STATE_H

#include <string> 

class Striker; 
class Ball;
class Field;

//membuat kelas dasar state pattern untuk menentukan aksi striker pada setiap tick
class StrikerState {
public:
    virtual ~StrikerState() = default; //memungkinkan objek state turunan dihancurkan dengan benar melalui pointer kelas dasar
    virtual std::string getName() const = 0; //mewajibkan setiap state memberikan nama state
    virtual std::string execute(Striker& striker, Ball& ball, const Field& field) = 0; //mewajibkan setiap state menjalankan perilakunya pada striker
};

//mendefinisikan empat state perilaku striker sesuai spesifikasi
class SearchState : public StrikerState {
public:
    std::string getName() const override; //mengambil nama state pencarian bola
    std::string execute(Striker& striker, Ball& ball, const Field& field) override; //menjalankan perilaku striker saat mencari bola
};

class ApproachState : public StrikerState {
public:
    std::string getName() const override; //mengambil nama state mendekati bola
    std::string execute(Striker& striker, Ball& ball, const Field& field) override; //menjalankan perilaku striker saat mendekati bola
};

class AlignState : public StrikerState {
public:
    std::string getName() const override; //mengambil nama state menyelaraskan arah tendangan
    std::string execute(Striker& striker, Ball& ball, const Field& field) override; //menjalankan perilaku striker saat menyelaraskan arah terhadap bola dan target
};

class KickState : public StrikerState {
public:
    std::string getName() const override; //mengambil nama state menendang bola
    std::string execute(Striker& striker, Ball& ball, const Field& field) override; //menjalankan perilaku striker saat menendang bola
};

#endif