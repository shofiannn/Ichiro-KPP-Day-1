#include <iostream>

#include "include/Vector2.h"
#include "include/Field.h"
#include "include/Ball.h"
#include "include/Striker.h"

int main() {

    // ==========================================
    // 1. Membuat Field
    // ==========================================

    Field field;

    std::cout << "=== FIELD ===\n";

    std::cout << "X : "
              << field.getMinX()
              << " sampai "
              << field.getMaxX()
              << "\n";

    std::cout << "Y : "
              << field.getMinY()
              << " sampai "
              << field.getMaxY()
              << "\n";


    // ==========================================
    // 2. Membuat Ball
    // ==========================================

    Vector2 ballStart = {2.0, 0.0};

    Ball ball(ballStart);

    Vector2 ballPosition = ball.getPosisi();

    std::cout << "\n=== BALL ===\n";

    std::cout << "Position: ("
              << ballPosition.x
              << ", "
              << ballPosition.y
              << ")\n";


    // ==========================================
    // 3. Membuat Striker
    // ==========================================

    Vector2 strikerStart = {0.0, 0.0};

    Striker striker(strikerStart, 0.0);

    Vector2 strikerPosition = striker.getPosisiRobot();

    std::cout << "\n=== STRIKER ===\n";

    std::cout << "Position: ("
              << strikerPosition.x
              << ", "
              << strikerPosition.y
              << ")\n";

    std::cout << "Orientation: "
              << striker.getArahRobot()
              << " degree\n";

    std::cout << "Speed: "
              << striker.getKecepatanRobot()
              << " m/tick\n";


    // ==========================================
    // 4. Testing Vector2
    // ==========================================

    double distanceToBall =
        jarak(
            striker.getPosisiRobot(),
            ball.getPosisi()
        );

    std::cout << "\n=== MATH TEST ===\n";

    std::cout << "Distance Striker -> Ball: "
              << distanceToBall
              << " meter\n";


    // ==========================================
    // 5. Testing setter speed
    // ==========================================

    striker.setKecepatanRobot(0.5);

    std::cout << "\nSpeed after setSpeed(0.5): "
              << striker.getKecepatanRobot()
              << " m/tick\n";


    return 0;
}