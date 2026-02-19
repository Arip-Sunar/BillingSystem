# BillingSystem — C++ Raylib GUI Application

A complete billing management desktop application built with C++ and Raylib.

---

## Features

| Screen | Features |
|--------|----------|
| **Login** | Username/password auth, validation, error messages |
| **Signup** | Full name, username, password confirmation, duplicate check |
| **Billing** | Add/delete items, qty & price, running total, print receipt |

- Data persisted in `users.dat` (plain text)
- Receipts saved to `receipt.txt`
- Default account: `admin` / `admin123`

---

## Build Instructions

### Linux / macOS
```bash
# Install raylib first:
# Ubuntu/Debian:
sudo apt install libraylib-dev
# Or build from source: https://github.com/raysan5/raylib

# Compile:
g++ main.cpp -o BillingSystem -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Run:
./BillingSystem
```

### Windows (MinGW)
```bash
# Download raylib from https://github.com/raysan5/raylib/releases
# Extract, then:
g++ main.cpp -o BillingSystem.exe -I./raylib/include -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
BillingSystem.exe
```

### Windows (MSVC)
```
cl main.cpp /I"raylib\include" /link "raylib\lib\raylib.lib" opengl32.lib gdi32.lib winmm.lib /out:BillingSystem.exe
```

### macOS (Homebrew)
```bash
brew install raylib
g++ main.cpp -o BillingSystem -lraylib -framework OpenGL -framework Cocoa -framework IOKit
./BillingSystem
```

---

## Controls

- **Tab** — Switch between input fields
- **Enter** — Submit login/action
- **Mouse Wheel** — Scroll bill items list
- **Click** — Focus fields / press buttons

---

## Project Structure

```
BillingSystem/
├── main.cpp        ← All source code (single file)
├── README.md       ← This file
├── users.dat       ← Auto-generated user database
└── receipt.txt     ← Auto-generated on "PRINT BILL"
```

---

## UI Theme

- **Dark cyberpunk aesthetic** — deep navy/midnight backgrounds
- **Neon cyan (#40BEFF)** and **electric purple (#7850FF)** accents
- Glowing line decorations, gradient blobs, subtle grid
- Rounded panels with border glow on hover/focus
