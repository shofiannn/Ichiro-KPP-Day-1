# Ichiro Robot Soccer Simulator

Simulasi robot striker berbasis C++17 (hanya Standard Library). Program menampilkan lapangan 2D dalam grid ASCII, lalu pada setiap tick (1 tick = 1 detik) Striker menjalankan siklus **Sense → Think → Act**: mencari bola dengan kamera, mendekati bola, menyelaraskan arah ke gawang, menendang, dan mengejar bola lagi sampai gol.

## 1. Persyaratan

- Compiler C++ yang mendukung C++17, misalnya GCC/G++.
- Hanya menggunakan C++ Standard Library; tidak memerlukan library pihak ketiga.
- `config.txt` opsional dan harus berada di working directory saat program dijalankan. Jika file tidak ditemukan, program menggunakan nilai default dari `Config.h`.

## 2. Struktur proyek

```text
.
├── main.cpp
├── config.txt
├── README.md
├── class_diagram.md
├── test_all.cpp
├── include/
│   ├── Ball.h
│   ├── Config.h
│   ├── Field.h
│   ├── InvalidActionException.h
│   ├── Robot.h
│   ├── Sensor.h
│   ├── Simulator.h
│   ├── Striker.h
│   ├── StrikerState.h
│   └── Vector2.h
└── src/
    ├── AlignState.cpp
    ├── ApproachState.cpp
    ├── Ball.cpp
    ├── Config.cpp
    ├── Field.cpp
    ├── KickState.cpp
    ├── Robot.cpp
    ├── SearchState.cpp
    ├── Sensor.cpp
    ├── Simulator.cpp
    ├── Striker.cpp
    └── Vector2.cpp
```

Diagram kelas lengkap ada di [`class_diagram.md`](class_diagram.md).

## 3. Kompilasi dengan g++

Jalankan perintah dari direktori root proyek (direktori yang berisi `main.cpp`, `include/`, `src/`, dan `config.txt`).

### Windows / MSYS2 UCRT64

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp src/Vector2.cpp src/Field.cpp src/Ball.cpp src/Robot.cpp src/Sensor.cpp src/Striker.cpp src/SearchState.cpp src/ApproachState.cpp src/AlignState.cpp src/KickState.cpp src/Config.cpp src/Simulator.cpp -Iinclude -o Ichiro_KPP.exe
```

Jalankan:

```powershell
.\Ichiro_KPP.exe
```

### Linux / macOS

Gunakan perintah kompilasi yang sama, tetapi ganti nama output menjadi `Ichiro_KPP`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp src/Vector2.cpp src/Field.cpp src/Ball.cpp src/Robot.cpp src/Sensor.cpp src/Striker.cpp src/SearchState.cpp src/ApproachState.cpp src/AlignState.cpp src/KickState.cpp src/Config.cpp src/Simulator.cpp -Iinclude -o Ichiro_KPP
./Ichiro_KPP
```

## 4. Menjalankan program, konfigurasi, dan tampilan output

Program membaca `config.txt` dari working directory. Contoh konfigurasi:

```ini
field_width=9
field_height=6
goal_width=3
robot_x=-3.5
robot_y=-2.0
ball_x=3.0
ball_y=-1.0
max_ticks=400
delay_ms=150
test_respawn=0
```

Kunci yang dibaca oleh `Config::loadFromFile`: `field_width`, `field_height`, `goal_width`, `robot_x`, `robot_y`, `ball_x`, `ball_y`, `max_ticks`, `delay_ms`, dan `test_respawn`.

- Posisi awal robot dan bola otomatis dibulatkan ke **pusat petak** terdekat (`Field::snap`), karena 1 petak grid = 0,5 m.
- `test_respawn=1` memaksa robot dan bola keluar lapangan pada tick ke-3 untuk menguji mekanisme respawn.

**Tampilan output** (grid 18 × 12 petak, antar elemen dipisah spasi):

| Simbol | Arti |
|---|---|
| `R` | Robot |
| `@` | Area pandang kamera (segitiga: 3 petak ke depan, selebar 3, 5, dan 7 petak) |
| `O` | Bola |
| `.` | Area kosong |
| `#` | Gawang lawan (kolom ke-18, 6 baris = 3 m) |

## 5. Arsitektur OOP

- **`Vector2`** menyimpan koordinat 2D. Fungsi matematika/navigasi dipusatkan di modul ini (prinsip DRY): `jarak`, `sudut`, `normalisasiSudut`, `normalisasiVektor`, `vektorArah`, `selisihPetak`, dan `samaPetak`.
- **`Field`** menyimpan ukuran lapangan (9 × 6 m), gawang (x = 4,5 m, lebar 3 m), pengecekan `isInside` / `isInsideGoal` / `isOutOfBounds`, pembulatan ke pusat petak (`snap`), dan visualisasi grid (`render`).
- **`Ball`** bergerak **petak demi petak** setelah ditendang: kecepatan awal 3 m/tick lalu turun 1 m/tick (6, 4, 2 petak per tick). Gol dan keluar lapangan diperiksa pada setiap petak lintasan. `respawn` mengembalikan bola ke tengah lapangan.
- **`Sensor`** adalah kamera berbentuk segitiga. `Sensor::tangkap` mengembalikan `DataSensor` yang hanya berisi bola yang **terlihat**, sehingga robot tidak membaca posisi global bola secara langsung.
- **`Robot`** adalah kelas abstrak dasar. Atribut posisi, arah, dan kecepatan bersifat `protected` dan diakses lewat getter/setter tervalidasi. `Robot` **memiliki** `Sensor` (composition / HAS-A), menyimpan `DataSensor` hasil tahap Sense dan `Aksi` hasil tahap Think, serta memiliki `respawn()`.
- **`Striker`** mewarisi `Robot` dan meng-override `think()`. `Striker` mengelola state aktif melalui `std::unique_ptr<StrikerState>`, memori posisi bola, dan rute patroli pencarian bola.
- **`StrikerState`** adalah kelas dasar abstrak State Pattern. Implementasinya: `SearchState`, `ApproachState`, `AlignState`, dan `KickState`. Setiap state hanya melakukan **Think**: memilih `Aksi` dan/atau berpindah state.
- **`Aksi`** (dengan `JenisAksi`: `DIAM`, `JALAN`, `PUTAR`, `TENDANG`, `RESPAWN_BOLA`) adalah perintah yang dikirim robot ke Simulator.
- **`Simulator`** memiliki objek `Field`, `Ball`, dan `Striker`, serta mengatur urutan tick.
- **`InvalidActionException`** dilempar oleh `Simulator::terapkanAksi` bila robot meminta tendangan atau respawn bola yang tidak memenuhi syarat, dan dilempar oleh `Robot::setPosisiRobot` bila posisi bernilai NaN/inf. Exception ditangkap dengan `try-catch` di `Simulator::run` dan `main`.

**Alur tiap tick (Sense – Think – Act):**

1. **Sense** — `Simulator` memanggil `striker.sense(ball)`; kamera (`Sensor`) menghasilkan `DataSensor`.
2. **Think** — `Simulator` memanggil `striker.think()`; state aktif memilih `Aksi`.
3. **Act** — `Simulator::terapkanAksi` memvalidasi aksi lalu menjalankannya (memutar, melangkah 1 petak = 0,5 m, menendang bola, atau me-respawn bola).
4. Bola yang sedang meluncur diperbarui (`Ball::update`), lalu `Simulator` memeriksa gol, bola keluar, dan robot keluar (respawn), kemudian mencetak grid.

## 6. Alur state kecerdasan Striker

State awal adalah `SearchState`. Pada setiap tick, `Striker::think()` meneruskan ke `think()` milik state aktif.

1. **SearchState** — jika kamera melihat bola (atau robot masih mengingat posisinya), pindah ke `ApproachState`. Jika tidak, robot memutar badan 90° sebanyak 4 kali (scan 360°), lalu berjalan ke titik patroli berikutnya dan memindai lagi di sana.
2. **ApproachState** — robot menentukan posisi tendang: di **kiri bola** (tendangan lurus), atau **diagonal kiri-atas / kiri-bawah bola** (tendangan miring) agar bola mengarah ke tengah lapangan. Robot berjalan 1 petak per tick ke posisi itu tanpa menginjak bola. Jika sudah sampai, pindah ke `AlignState`. Jika bola hilang dari ingatan, kembali ke `SearchState`. Jika bola menempel dinding kiri (tidak ada petak untuk berdiri), robot meminta `RESPAWN_BOLA`.
3. **AlignState** — robot memutar badan menghadap gawang (arah 0°), lalu pindah ke `KickState`.
4. **KickState** — robot hanya menendang jika kamera melihat bola tepat di 1 dari 3 petak depan (lurus, diagonal atas, diagonal bawah). Jika tidak, kembali ke `ApproachState`. Setelah menendang, robot kembali ke `SearchState` untuk mengejar bola.
5. **Setelah tendangan** — `Simulator` memperbarui bola tiap tick. Jika bola melewati bukaan gawang, simulasi berhenti dengan pesan gol. Jika bola keluar lapangan, bola di-respawn ke tengah lapangan. Jika robot keluar lapangan, robot di-respawn ke posisi awal. Jika batas tick tercapai lebih dahulu, simulasi berhenti.

Alur ringkas:

```text
SearchState ── bola terlihat / teringat ──► ApproachState
    ▲                                           │ sampai di posisi tendang
    │ bola hilang                               ▼
    ├────────────────────────────────────── AlignState
    │                                           │ menghadap gawang
    │                                           ▼
    │   bola tidak di 3 petak depan        KickState
    │   (kembali ke ApproachState) ◄────────────┤
    │                                           │ bola di 3 petak depan -> TENDANG
    └───────────────────────────────────────────┘
Simulator memperbarui bola ──► Gol / bola keluar -> respawn bola / robot keluar -> respawn robot / batas tick
```

## 7. Skenario uji

### Unit test otomatis

`tests/test_all.cpp` berisi 36 pemeriksaan: aturan lapangan, kecepatan robot dan bola, kamera segitiga, syarat tendang, siklus Sense–Think–Act, format output grid, level 1–3, respawn, dan simulasi penuh sampai gol. Compile dan jalankan dari root proyek:

```bash
g++ -std=c++17 test_all.cpp src/Vector2.cpp src/Field.cpp src/Ball.cpp src/Robot.cpp src/Sensor.cpp src/Striker.cpp src/Config.cpp src/Simulator.cpp src/SearchState.cpp src/ApproachState.cpp src/AlignState.cpp src/KickState.cpp -o test_all
./test_all
```

Hasil yang diharapkan: `HASIL: 36 lulus, 0 gagal`.

### Skenario manual

| No. | Skenario | Cara menguji | Hasil yang diharapkan |
|---|---|---|---|
| 1 | Kompilasi bersih | Jalankan perintah g++ pada bagian 3 | Kompilasi selesai tanpa error maupun warning; executable terbentuk. |
| 2 | Konfigurasi default | Jalankan program dari root proyek dengan `config.txt` tersedia | Program menampilkan judul simulator dan grid 18 × 12 per tick; Striker akhirnya mencetak gol. |
| 3 | File konfigurasi tidak ditemukan | Jalankan executable dari direktori kerja yang tidak memiliki `config.txt` | Nilai default pada `Config.h` digunakan. |
| 4 | Bola terdeteksi kamera | Biarkan robot berpatroli sampai bola masuk segitiga `@` | State beralih dari `SearchState` ke `ApproachState`. |
| 5 | Posisi tendang tercapai | Amati robot mendekati bola | `ApproachState` → `AlignState` → `KickState`. |
| 6 | Tendangan dan gol | Jalankan skenario default | Bola melewati bukaan gawang, muncul pesan gol, simulasi berhenti. |
| 7 | Bola keluar lapangan | Tendang bola di baris di luar lebar gawang atau pada lintasan yang keluar batas | Bola di-respawn ke tengah lapangan. |
| 8 | Robot keluar lapangan | Set `test_respawn=1` di `config.txt` | Robot di-respawn ke posisi awal, bola di-respawn ke tengah, lalu simulasi berlanjut sampai gol. |
| 9 | Batas tick | Atur `max_ticks` ke nilai kecil yang positif | Simulasi berhenti ketika batas tick tercapai jika gol belum terjadi. |
| 10 | Aksi tidak valid | Jalankan `tests/test_all.cpp` (pengujian posisi NaN/inf pada `setPosisiRobot`) | `InvalidActionException` dilempar dan ditangkap `try-catch`. |