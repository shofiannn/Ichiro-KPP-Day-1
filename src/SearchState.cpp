#include "../include/StrikerState.h"
#include "../include/Striker.h" 
#include "../include/Ball.h"
#include "../include/Field.h" 

//mengambil nama state pencarian bola
std::string SearchState::getName() const { return "SearchState"; }

//menjalankan perilaku striker saat mencari bola
std::string SearchState::execute(Striker& striker, Ball& ball, const Field& field) {
    (void)field;

    //memeriksa apakah bola terdeteksi oleh sensor striker
    if (striker.getSensor().melihatBola(striker.getPosisiRobot(), ball)) {
        striker.changeState(new ApproachState()); //mengganti state aktif menjadi approachstate karena bola sudah ditemukan
        return "SearchState: bola ditemukan, beralih ke ApproachState."; //mengembalikan pesan bahwa bola ditemukan dan state berubah
    }

    return "SearchState: mencari bola...";
}