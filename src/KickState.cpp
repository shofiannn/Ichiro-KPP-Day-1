#include "../include/StrikerState.h"
#include "../include/Striker.h"
#include "../include/Ball.h"
#include "../include/Field.h"

std::string KickState::getName() const { return "KickState"; }

//menjalankan perilaku striker saat menendang bola
std::string KickState::execute(Striker& striker, Ball& ball, const Field& field) {
    (void)striker;

    //menendang bola menuju gawang
    const Vector2 targetGawang{field.getMaxX() + 1.0, 0.0}; //menentukan target tendangan di luar sisi kanan lapangan pada garis tengah
    ball.kick(targetGawang); //menendang bola menuju target gawang

    striker.setSudahMenendang(true); //menandai bahwa striker sudah melakukan tendangan
    striker.changeState(nullptr); //menghapus state aktif karena nullptr menandakan perilaku robot sudah selesai

    return "KickState: bola ditendang menuju gawang!";
}