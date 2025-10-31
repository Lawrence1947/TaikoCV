# 🎵 TaikoCV
*A minimal rhythm-game engine built with OpenCV and C++.*

TaikoCV is a simple **Taiko-style rhythm game** written from scratch in C++.
It uses **OpenCV** for rendering, **Miniaudio** for sound playback, and a lightweight **JSON beatmap** format.
The project was created as an educational experiment in building a simple game engine with no external game frameworks.

## 🕹️ Gameplay Overview

Players hit keys in rhythm as colored circles (notes) fly toward the hit zone:

- 🔴 **Red notes** → hit with `J` / `K`
- 🔵 **Blue notes** → hit with `D` / `F`
- 🟠 **Big notes** → hit with both keys of the same color simultaneously

The game displays:
- Current score
- Combo counter
- Animated notes synced to the music

## 🧩 Features

- 🎧 Real-time MP3 playback via [**Miniaudio**](https://github.com/mackron/miniaudio)
- 🎨 2D rendering using **OpenCV**
- 🗺️ Custom JSON beatmap format (offset, scroll speed, and note timing)
- 💥 Smooth transitions between main menu → gameplay → results
- 🧠 Frame-based logic with adjustable hit detection and offset calibration
- ⚙️ Modular architecture (ENGINE / SYSTEM / GAME layers)

## ⚙️ Dependencies

### Core libraries
| Library | Purpose | License |
|----------|----------|---------|
| [OpenCV 4.x](https://opencv.org/) | Rendering, text, drawing, timing | Apache 2.0 |
| [Miniaudio](https://github.com/mackron/miniaudio) | Sound playback (MP3/WAV) | Public domain / Unlicense |
| [nlohmann/json](https://github.com/nlohmann/json) | Beatmap parsing | MIT |

### Build tools
- CMake ≥ 3.16
- C++17 compiler (GCC / Clang / MSVC)
- Linux, macOS, or WSL2 environment recommended

## 🏗️ Build Instructions

```bash
git clone https://github.com/Lawrence1947/TaikoCV.git
cd TaikoCV
mkdir build && cd build
cmake ..
make
./src/TaikoCV
```

If OpenCV linking issues occur:
```bash
sudo apt install libopencv-dev
```

If X11 linking issues occur:
```bash
sudo apt update
sudo apt install libx11-dev libxrandr-dev
```

If using WSL:
```bash
sudo apt install x11-apps
export DISPLAY=:0
```

## 🎶 Beatmap Format

```json
{
  "audio": "../maps/test_map/test_song_short.mp3",
  "offset_ms": -70,
  "scroll_speed_px_s": 520.0,
  "lead_margin_px": 90,
  "notes": [
    { "t": 0, "color": "red", "size": "small" },
    { "t": 531, "color": "blue", "size": "small" },
    { "t": 1062, "color": "red", "size": "small" }
  ]
}
```

## 🪄 Future Plans

- Configurable hit windows
- Background animations
- Song selection menu
- On-the-fly offset calibration
- Cross-platform builds
