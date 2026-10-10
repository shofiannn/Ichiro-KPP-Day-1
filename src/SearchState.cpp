#include "../include/StrikerState.h"
#include "../include/Striker.h"
#include "../include/Ball.h"
#include "../include/Field.h"
std::string SearchState::getName() const { return "SearchState"; }
std::string SearchState::execute(Striker& striker, Ball& ball, const Field& field) {
    // bola harus terlihat di segitiga kamera
    if (striker.perbaruiMemori(ball)) {
        striker.changeState(new ApproachState());
        return "SearchState: bola ditemukan, beralih ke ApproachState.";
    }
    return "SearchState: " + striker.patroli(field);
}
