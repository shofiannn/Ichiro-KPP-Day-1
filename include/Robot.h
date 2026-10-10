#ifndef ROBOT_H
#define ROBOT_H

#include "Vector2.h"
#include "Field.h"

class Robot {
protected:
    Vector2 posisiRobot; //posisi robot
    double arahRobot; //arah robot 
    double kecepatanRobot; //kecepatan robot
    Vector2 posisiAwal; //[BARU] titik respawn robot
    double arahAwal;    //[BARU] arah saat respawn

public:
    Robot(const Vector2& posisiAwalRobot, double arahAwalRobot = 0.0);
    virtual ~Robot() = default; //memungkinkan objek turunan dihancurkan dengan benar melalui pointer robot

    Vector2 getPosisiRobot() const; //mengambil posisi robot saat ini
    double getArahRobot() const; //mengambil arah hadap robot saat ini
    double getKecepatanRobot() const; //mengambil kecepatan robot saat ini

    void setPosisiRobot(const Vector2& posisiBaru); //mengubah posisi robot
    void setArahRobot(double arahBaru); //mengubah arah hadap robot
    void setKecepatanRobot(double kecepatanBaru); //mengubah kecepatan robot

    //melangkah 1 petak (0,5 m) menuju target
    void moveToward(const Vector2& target, const Field& field, const Vector2* halangan = nullptr);
    virtual void respawn(); //[BARU] mengembalikan robot ke posisi & arah awal

    //setiap jenis robot wajib memiliki perilaku think sendiri
    virtual void think() = 0; //mewajibkan kelas turunan membuat implementasi perilaku robot

};

#endif