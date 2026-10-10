# Ichiro Robot Soccer Simulator

Proyek C++17 untuk simulasi robot striker di lapangan 9 x 6 meter.

## Fitur
- Lapangan memakai koordinat dengan titik (0,0) di tengah.
- Gawang berada di sisi kanan dengan bukaan selebar 3 meter.
- Pergerakan robot maksimal 0,5 meter/tick.
- Jarak memakai Euclidean distance; gerak dibagi langkah 0,1 meter dan jumlah langkah dibulatkan ke bawah.
- State Pattern untuk perilaku Striker: SearchState, ApproachState, AlignState, dan KickState.
- Tendangan menuju tengah gawang, termasuk arah diagonal.
- Kecepatan bola menurun 3, 2, 1, lalu 0.
- Bola yang keluar lapangan di-respawn ke tengah lapangan.
- Lapangan ASCII dicetak setiap tick.
- Pengaturan berada di config.txt.

## Struktur
- `include/`: deklarasi kelas.
- `src/`: implementasi kelas dan state.
- `main.cpp`: program utama.
- `config.txt`: konfigurasi simulasi.

## Kompilasi (jalankan dari folder proyek)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp src/Vector2.cpp src/Field.cpp src/Ball.cpp src/Robot.cpp src/Sensor.cpp src/Striker.cpp src/SearchState.cpp src/ApproachState.cpp src/AlignState.cpp src/KickState.cpp src/Config.cpp src/Simulator.cpp -Iinclude -o Ichiro_KPP.exe
```

## Menjalankan
PowerShell:
```powershell
.\Ichiro_KPP.exe
```

Pastikan terminal berada di folder yang sama dengan `config.txt`, karena file konfigurasi dibaca dari working directory saat program dijalankan.
