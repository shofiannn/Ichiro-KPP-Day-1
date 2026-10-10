#include "../include/Striker.h"
#include "../include/StrikerState.h" 
#include "../include/Ball.h"
#include "../include/Field.h"

Striker::Striker(const Vector2& posisiAwalStriker, double arahAwalStriker)
    : Robot(posisiAwalStriker, arahAwalStriker), //memanggil konstruktor kelas dasar robot
      sensor(), //sensor segitiga
      state(std::make_unique<SearchState>()), //mengatur state awal striker menjadi searchstate
      sudahMenendang(false) {}

//menggunakan destructor default untuk membersihkan objek striker
Striker::~Striker() = default;

//menjalankan fungsi think yang diwajibkan oleh kelas robot
void Striker::think() {
}

//memperbarui perilaku striker berdasarkan state yang sedang aktif
std::string Striker::update(Ball& bola, const Field& field) {
    if (!state) return "Striker sudah selesai menjalankan perilakunya.";
    return state->execute(*this, bola, field);
}

//mengganti state perilaku striker dengan state baru
void Striker::changeState(StrikerState* stateBaru) {
    state.reset(stateBaru);
}

//mengambil nama state yang sedang aktif
std::string Striker::getNamaState() const {
    return state ? state->getName() : "Finished";
}

//mengembalikan referensi ke sensor milik striker
Sensor& Striker::getSensor() { return sensor; }

//mengambil jarak tendang striker
double Striker::getJarakTendang() const { return jarakTendang; }

//memeriksa apakah striker sudah melakukan tendangan
bool Striker::hasKicked() const { return sudahMenendang; }

//mengubah status tendangan striker
void Striker::setSudahMenendang(bool nilai) { sudahMenendang = nilai; }
static const Vector2 WAYPOINT[] = {{-2.75, 2.25}, {0.25, 2.25}, {3.25, 2.25}, {3.25, 0.25}, {0.25, 0.25},
                                   {-2.75, 0.25}, {-2.75, -2.25}, {0.25, -2.25}, {3.25, -2.25}};
bool Striker::perbaruiMemori(const Ball& bola) {
    if (sensor.melihatBola(posisiRobot, arahRobot, bola)) {
        memoriBola = sensor.bacaPosisiBola(bola); adaMemori = true; return true;
    }
    if (adaMemori) {
        int m, s; Sensor::relatif(posisiRobot, arahRobot, memoriBola, m, s);
        if (Sensor::petakTerlihat(m, s)) adaMemori = false;
    }
    return adaMemori;
}
Vector2 Striker::getMemoriBola() const { return memoriBola; }
void Striker::lupakanBola() { adaMemori = false; jumlahPutar = 0; }
std::string Striker::patroli(const Field& field) {
    if (jumlahPutar < 4) { setArahRobot(arahRobot + 90.0); ++jumlahPutar; return "memutar badan 90 derajat untuk scan."; }
    const Vector2 tujuan = WAYPOINT[indeksWaypoint];
    if (samaPetak(posisiRobot, tujuan)) { indeksWaypoint = (indeksWaypoint + 1) % 9; jumlahPutar = 0; return "tiba di waypoint, scan ulang."; }
    moveToward(tujuan, field);
    return "berjalan ke waypoint patroli.";
}
//RESPAWN STRIKER: posisi (dari Robot) + state kembali SearchState + lupa bola
void Striker::respawn() {
    Robot::respawn();
    changeState(new SearchState());
    sudahMenendang = false;
    adaMemori = false; jumlahPutar = 0; indeksWaypoint = 0;
}