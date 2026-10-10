#include "../include/StrikerState.h"
#include "../include/Striker.h"
#include "../include/Ball.h"
#include "../include/Field.h"
#include "../include/InvalidActionException.h"
#include <cstdlib>
std::string KickState::getName() const { return "KickState"; }
std::string KickState::execute(Striker& striker, Ball& ball, const Field& field) {
    (void)field;
    //SYARAT TENDANG: bola harus tepat di 1 dari 3 petak depan robot (lurus / depan-atas / depan-bawah)
    int maju, samping;
    Sensor::relatif(striker.getPosisiRobot(), striker.getArahRobot(), ball.getPosisi(), maju, samping);
    if (maju != 1 || std::abs(samping) > 1) {
        striker.changeState(new SearchState());
        throw InvalidActionException("Tendangan ditolak: bola tidak berada di 3 petak depan robot.");
    }
    // arah tendangan = arah robot -> bola (lurus, miring atas, atau miring bawah)
    const Vector2 p = ball.getPosisi(), r = striker.getPosisiRobot();
    ball.kick({p.x + (p.x - r.x), p.y + (p.y - r.y)});
    striker.setSudahMenendang(true);
    striker.lupakanBola();                     
    striker.changeState(new SearchState());      
    return "KickState: bola ditendang!";
}
