#include "../include/StrikerState.h" 
#include "../include/Striker.h"
#include "../include/Ball.h"
#include "../include/Field.h" 
#include <cmath>

std::string AlignState::getName() const { return "AlignState"; }

//menjalankan perilaku striker saat menyelaraskan arah tendangan
std::string AlignState::execute(Striker& striker, Ball& ball, const Field& field) {
    const Vector2 robotPos = striker.getPosisiRobot(); //mengambil posisi robot saat ini
    const Vector2 ballPos = ball.getPosisi(); //mengambil posisi bola saat ini

    //jika bola bergerak menjauh atau jarak robot ke bola terlalu besar, robot harus mendekat lagi
    if (jarak(robotPos, ballPos) > striker.getJarakTendang() + 0.15) {
        striker.changeState(new ApproachState());
        return "AlignState: posisi bola berubah, kembali ke ApproachState.";
    }

    //menentukan target di tengah bukaan gawang
    const Vector2 targetGawang{field.getMaxX() + 1.0, 0.0}; //menentukan koordinat target tendangan
    const double arahSeharusnya = sudut(ballPos, targetGawang); //menghitung sudut dari posisi bola menuju target gawang
    striker.setArahRobot(arahSeharusnya); //menyesuaikan arah hadap robot menuju gawang

    striker.changeState(new KickState()); //mengganti state aktif menjadi kickstate setelah arah robot diselaraskan
    return "AlignState: arah robot diselaraskan ke gawang; beralih ke KickState.";
}