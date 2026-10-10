#include "../include/StrikerState.h"
#include "../include/Striker.h"
#include "../include/Ball.h"
#include "../include/Field.h"
std::string AlignState::getName() const { return "AlignState"; }
std::string AlignState::execute(Striker& striker, Ball& ball, const Field& field) {
    (void)field;
    striker.setArahRobot(sudut(striker.getPosisiRobot(), {field.getMaxX() + 1.0, striker.getPosisiRobot().y}));
    (void)ball;
    striker.changeState(new KickState());
    return "AlignState: robot menghadap gawang; beralih ke KickState.";
}
