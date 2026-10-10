#include "../include/StrikerState.h"
#include "../include/Striker.h"
#include "../include/Ball.h"
#include "../include/Field.h"
std::string ApproachState::getName() const { return "ApproachState"; }
std::string ApproachState::execute(Striker& striker, Ball& ball, const Field& field) {
    if (!striker.perbaruiMemori(ball)) {                    
        striker.changeState(new SearchState());
        return "ApproachState: bola hilang, kembali ke SearchState.";
    }
    const Vector2 bola = striker.getMemoriBola();
    const int dy = bola.y > 1.0 ? -1 : (bola.y < -1.0 ? 1 : 0);
    Vector2 posisiTendang{bola.x - UKURAN_PETAK, bola.y - dy * UKURAN_PETAK};
    if (!field.isInside(posisiTendang)) posisiTendang = {bola.x - UKURAN_PETAK, bola.y}; // diagonal di luar lapangan -> lurus
    if (!field.isInside(posisiTendang)) {                        // bola menempel dinding kiri: tidak ada tempat berdiri
        ball.respawn(field);                                    
        striker.lupakanBola();
        striker.changeState(new SearchState());
        return "ApproachState: bola menempel dinding kiri, bola di-respawn.";
    }
    if (samaPetak(striker.getPosisiRobot(), posisiTendang)) {
        striker.changeState(new AlignState());
        return "ApproachState: sudah di posisi tendang, beralih ke AlignState.";
    }
    striker.moveToward(posisiTendang, field, &bola);           
    return "ApproachState: robot mendekati posisi tendang.";
}
