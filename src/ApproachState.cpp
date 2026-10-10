#include "../include/StrikerState.h" 
#include "../include/Striker.h" 
#include "../include/Ball.h"
#include "../include/Field.h" 
#include <cmath> 

std::string ApproachState::getName() const { return "ApproachState"; }

//menjalankan perilaku striker saat mendekati bola
std::string ApproachState::execute(Striker& striker, Ball& ball, const Field& field) {
    const Vector2 robotPos = striker.getPosisiRobot(); //mengambil posisi robot saat ini
    const Vector2 ballPos = striker.getSensor().bacaPosisiBola(ball); //membaca posisi bola melalui sensor striker
    const double distance = jarak(robotPos, ballPos); //menghitung jarak antara robot dan bola

    //jika robot sudah cukup dekat, robot berhenti mendekat dan mulai menyelaraskan arah
    if (distance <= striker.getJarakTendang()) {
        striker.changeState(new AlignState()); //mengganti state aktif menjadi alignstate
        return "ApproachState: sudah dekat dengan bola, beralih ke AlignState."; //mengembalikan pesan bahwa robot sudah dekat dengan bola
    }

    //menentukan robot berhenti sedikit di belakang bola pada garis menuju tengah gawang
    const Vector2 targetGawang{field.getMaxX() + 1.0, 0.0}; //menentukan titik target di luar sisi kanan lapangan pada garis tengah
    const Vector2 arahKeGawang = normalisasiVektor(
        {targetGawang.x - ballPos.x, targetGawang.y - ballPos.y}); //menghitung arah dari bola menuju target gawang
    const Vector2 titikDekatBola{
        ballPos.x - arahKeGawang.x * striker.getJarakTendang(), //menghitung koordinat x titik berhenti di belakang bola
        ballPos.y - arahKeGawang.y * striker.getJarakTendang() //menghitung koordinat y titik berhenti di belakang bola
    };

    striker.moveToward(titikDekatBola, field); //menggerakkan robot menuju titik berhenti dengan memperhatikan batas lapangan
    return "ApproachState: robot mendekati bola."; //mengembalikan pesan bahwa robot sedang mendekati bola
}