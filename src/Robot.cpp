#include "../include/Robot.h"
#include "../include/InvalidActionException.h"
#include <cmath>

//membuat robot dengan posisi awal, arah hadap awal, dan kecepatan awal nol
Robot::Robot(const Vector2& posisiAwalRobot, double arahAwalRobot)
    : posisiRobot(posisiAwalRobot),
      arahRobot(normalisasiSudut(arahAwalRobot)),
      kecepatanRobot(0.0) {}

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
void Robot::moveToward(const Vector2& target, const Field& field) {
    const double jarakTarget = jarak(posisiRobot, target); //menghitung jarak antara posisi robot dan target

    //menghentikan pergerakan jika robot sudah sangat dekat dengan target
    if (jarakTarget < 0.000001) {
        kecepatanRobot = 0.0;
        return;
    }

    //mengambil jarak maksimal untuk tick ini tanpa melewati target
    const double jarakMaksimal = std::min(0.5, jarakTarget);

    int jumlahLangkah = static_cast<int>(std::floor(jarakMaksimal / langkahKecil + 1e-9)); //menghitung jumlah langkah
    double jarakGerak = jumlahLangkah * langkahKecil; //menghitung total jarak

    //jika target berjarak kurang dari 0,1 meter, robot boleh langsung menyentuh target
    if (jumlahLangkah == 0 && jarakTarget <= 0.5) jarakGerak = jarakTarget; //menggunakan sisa jarak menuju target jika tidak ada langkah penuh

    //menghentikan pergerakan jika jarak gerak tidak positif
    if (jarakGerak <= 0.0) {
        kecepatanRobot = 0.0;
        return;
    }

    //menghitung vektor arah dari posisi robot menuju target
    const Vector2 arah = normalisasiVektor({target.x - posisiRobot.x,
                                             target.y - posisiRobot.y});

    //menghitung posisi baru berdasarkan arah dan jarak gerak
    const Vector2 posisiBaru{
        posisiRobot.x + arah.x * jarakGerak, 
        posisiRobot.y + arah.y * jarakGerak
    };

    //memastikan posisi baru masih berada di dalam lapangan
    if (!field.isInside(posisiBaru)) {
        throw InvalidActionException("Robot mencoba bergerak keluar dari lapangan.");
    }

    posisiRobot = posisiBaru; //memperbarui posisi robot
    kecepatanRobot = jarakGerak; //menyimpan jarak yang ditempuh
}