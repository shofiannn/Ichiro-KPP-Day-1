# Ichiro Robot Soccer Simulator

Simulasi robot striker sederhana berbasis C++17. Program menampilkan lapangan 2D dalam ASCII, menggerakkan robot mendekati bola, menyelaraskan arah ke gawang, lalu menendang bola.

## 1. Persyaratan

- Compiler C++ yang mendukung C++17, misalnya GCC/G++.
- Hanya menggunakan C++ Standard Library; tidak memerlukan library pihak ketiga.
- `config.txt` opsional dan harus berada di working directory saat program dijalankan. Jika file tidak ditemukan, program menggunakan nilai default dari `Config.h`.

## 2. Struktur proyek

```text
.
├── main.cpp
├── config.txt
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

## 4. Menjalankan program dan konfigurasi

Program membaca `config.txt` dari working directory. Contoh konfigurasi:

```ini
robot_x=-3.5
robot_y=-2.0
ball_x=2.5
ball_y=-1.0
```

## 5. Arsitektur OOP

Lihat diagram kelas pada [`CLASS_DIAGRAM.md`](CLASS_DIAGRAM.md). Secara ringkas:

- `Robot` adalah kelas abstrak dasar untuk robot yang menyimpan posisi, arah, dan kecepatan.
- `Striker` mewarisi `Robot` dan mengelola `Sensor` serta state aktif melalui `std::unique_ptr<StrikerState>`.
- `StrikerState` adalah kelas dasar abstrak untuk State Pattern. Implementasinya adalah `SearchState`, `ApproachState`, `AlignState`, dan `KickState`.
- `Simulator` mengatur urutan tick serta memiliki objek `Field`, `Ball`, dan `Striker`.
- `Vector2` menyimpan koordinat 2D; fungsi geometri seperti `jarak`, `sudut`, `normalisasiSudut`, dan `normalisasiVektor` didefinisikan di `Vector2.cpp`.
- `InvalidActionException` dipakai ketika robot mencoba bergerak keluar dari batas lapangan.

## 6. Alur state kecerdasan Striker

State awal adalah `SearchState`. Pada setiap tick, `Simulator` meminta `Striker` menjalankan state aktif.

1. **SearchState** — sensor memeriksa apakah bola berada dalam jangkauan deteksi. Jika terlihat, pindah ke `ApproachState`.
2. **ApproachState** — striker menghitung jarak ke bola. Jika cukup dekat (maksimal `jarakTendang`, 0,55 meter), pindah ke `AlignState`; jika belum, bergerak menuju titik di belakang bola yang mengarah ke gawang.
3. **AlignState** — memeriksa kembali jarak ke bola. Jika terlalu jauh, kembali ke `ApproachState`; jika cukup dekat, arah robot diselaraskan menuju tengah gawang dan state berpindah ke `KickState`.
4. **KickState** — bola ditendang menuju titik tengah gawang. Striker menandai bahwa tendangan telah dilakukan dan tidak menjalankan state pencarian lagi.
5. **Setelah tendangan** — `Simulator` memperbarui pergerakan bola tiap tick. Jika bola melewati bukaan gawang, simulasi berhenti dengan pesan gol; jika bola keluar lapangan, bola dikembalikan ke tengah. Jika batas tick tercapai lebih dahulu, simulasi berhenti.

Alur ringkas:

```text
SearchState
    │ bola terlihat
    ▼
ApproachState ── belum dekat ──► tetap ApproachState / bergerak mendekat
    │ cukup dekat
    ▼
AlignState ── jarak terlalu jauh ──► ApproachState
    │ arah diselaraskan
    ▼
KickState
    │ tendang
    ▼
Simulator memperbarui bola ──► Gol / bola keluar dan respawn / batas tick tercapai
```

## 7. Skenario uji manual

Proyek ini belum menyertakan unit-test otomatis. Skenario berikut adalah pemeriksaan manual yang dapat dilakukan saat menjalankan program. Hasil aktual bergantung pada konfigurasi dan posisi awal.

| No. | Skenario | Cara menguji | Hasil yang diharapkan |
|---|---|---|---|
| 1 | Kompilasi bersih | Jalankan perintah g++ pada bagian 3 | Kompilasi selesai tanpa error; executable terbentuk. |
| 2 | Konfigurasi default | Jalankan program dari root proyek dengan `config.txt` tersedia | Program menampilkan judul simulator dan gambar lapangan per tick. |
| 3 | File konfigurasi tidak ditemukan | Jalankan executable dari direktori kerja yang tidak memiliki `config.txt` | Nilai default pada `Config.h` digunakan. |
| 4 | Bola terdeteksi | Gunakan posisi awal yang membuat bola berada dalam jangkauan sensor 9 meter | State beralih dari `SearchState` ke `ApproachState`. |
| 5 | Bola cukup dekat | Atur posisi awal robot dekat dengan bola | State `ApproachState` beralih ke `AlignState`, lalu ke `KickState` jika jarak tetap sesuai. |
| 6 | Tendangan dan gol | Uji posisi bola serta arah tendangan yang lintasannya melewati bukaan gawang | Simulator menampilkan pesan gol dan berhenti. |
| 7 | Bola keluar lapangan | Uji lintasan yang tidak melewati bukaan gawang dan keluar batas | Bola di-respawn ke tengah lapangan. |
| 8 | Batas tick | Atur `max_ticks` ke nilai kecil yang positif | Simulasi berhenti ketika batas tick tercapai jika gol belum terjadi. |
| 9 | Aksi robot tidak valid | Uji kondisi yang membuat gerakan robot akan melewati batas lapangan | `InvalidActionException` ditangani oleh simulator dan pesan kesalahan ditampilkan. |

## 8. Pernyataan penggunaan AI

Bantuan AI digunakan dalam proses peninjauan kode dan penyusunan dokumentasi untuk tugas ini, termasuk pemeriksaan pesan kompilasi, perapian README, dan penyusunan diagram kelas berdasarkan struktur source code yang tersedia.