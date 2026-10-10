#include "../include/Striker.h"
#include "../include/StrikerState.h" 
#include "../include/Ball.h"
#include "../include/Field.h"

Striker::Striker(const Vector2& posisiAwalStriker, double arahAwalStriker)
    : Robot(posisiAwalStriker, arahAwalStriker), //memanggil konstruktor kelas dasar robot
      sensor(9.0), //membuat sensor dengan jangkauan 9 meter
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