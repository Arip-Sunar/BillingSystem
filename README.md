# 🧾 BillingSystem

A desktop billing management application built with **C++** and **Raylib GUI**.
Features a dark cyberpunk theme with Poppins font and custom logo support.

---

## 📁 Project Structure

```
BillingSystem/
│
├── main.cpp          → Entry point (window init, game loop)
│
├── globals.h         → Shared structs, enums, colors, extern declarations
├── globals.cpp       → Global variable definitions + Poppins draw helpers
│
├── ui.h              → UI helper declarations
├── ui.cpp            → Button, InputBox, PasswordBox, GlowLine, Background, Logo
│
├── helpers.h         → Auth & data function declarations
├── helpers.cpp       → LoadUsers, SaveUsers, UserExists, CheckLogin, CartTotal
│
├── login.h           → Login screen declaration
├── login.cpp         → Login screen implementation
│
├── signup.h          → Signup screen declaration
├── signup.cpp        → Signup screen implementation
│
├── billing.h         → Billing screen declaration
├── billing.cpp       → Billing screen implementation
│
├── logo.png          → Your custom logo (place in this folder)
│
├── Poppins-Regular.ttf   → Poppins Regular font
├── Poppins-Bold.ttf      → Poppins Bold font
├── Poppins-SemiBold.ttf  → Poppins SemiBold font
│
├── users.dat         → Auto-generated user database
└── receipt.txt       → Auto-generated receipt on Print Bill
```

---

## ✨ Features

### 🔐 Login Screen
- Username and password fields
- Error message on wrong credentials
- Tab key to switch between fields
- Enter key to submit
- Custom logo image display
- Link to Signup screen

### 📝 Signup Screen
- Full name, username, password, confirm password
- Validates all fields are filled
- Checks passwords match
- Checks for duplicate usernames
- Back to Login button inside the card

### 🧾 Billing Screen
- Add items with name, quantity and price
- Scrollable bill table (mouse wheel)
- Delete individual items
- Running grand total
- Print Bill → saves receipt to `receipt.txt`
- Clear Bill to reset
- Logout button

---

## 🛠️ Requirements

| Tool | Version |
|------|---------|
| C++ Compiler | GCC 14+ (w64devkit) |
| Raylib | 5.0 |
| OS | Windows / Linux / macOS |

---

## 🚀 Build Instructions

### Windows (MinGW / w64devkit)

**Step 1 — Set compiler path (run every time you open CMD):**
```bash
set PATH=C:\raylib\w64devkit\bin;%PATH%
```

**Step 2 — Go to project folder:**
```bash
cd C:\BillingSystem
```

**Step 3 — Compile:**
```bash
g++ main.cpp globals.cpp ui.cpp helpers.cpp login.cpp signup.cpp billing.cpp history.cpp -o BillingSystem.exe -I"C:/raylib-5.0_win64_mingw-w64/include" -L"C:/raylib-5.0_win64_mingw-w64/lib" -lraylib -lopengl32 -lgdi32 -lwinmm
```

**Step 4 — Run:**
```bash
BillingSystem.exe
```

---

### Linux

```bash
sudo apt install libraylib-dev

g++ main.cpp globals.cpp ui.cpp helpers.cpp login.cpp signup.cpp billing.cpp \
    -o BillingSystem -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

./BillingSystem
```

### macOS

```bash
brew install raylib

g++ main.cpp globals.cpp ui.cpp helpers.cpp login.cpp signup.cpp billing.cpp \
    -o BillingSystem -lraylib -framework OpenGL -framework Cocoa -framework IOKit

./BillingSystem
```

---

## 🎮 Controls

| Key / Action | Effect |
|--------------|--------|
| `Tab` | Switch between input fields |
| `Enter` | Submit login form |
| `Mouse Wheel` | Scroll bill items list |
| `Click` | Focus fields / press buttons |

---

## 👤 Default Account

| Field | Value |
|-------|-------|
| Username | `admin` |
| Password | `admin123` |

A default admin account is created automatically on first run if no users exist.

---

## 🎨 UI Theme

- **Background:** Deep midnight navy with subtle grid
- **Accent:** Neon cyan `#40BEFF`
- **Accent 2:** Electric purple `#7850FF`
- **Font:** Poppins (Regular, Bold, SemiBold)
- **Effects:** Glowing lines, gradient blobs, rounded panels

---

## 📄 Receipt Format

When you click **PRINT BILL**, a `receipt.txt` file is saved in your project folder:

```
============================================
             BillingSystem Receipt
============================================
Date: Thu Feb 19 22:00:00 2026
Cashier: admin
--------------------------------------------
Item                  Qty   Price       Total
--------------------------------------------
Laptop                1     999.99      999.99
Mouse                 2     25.00       50.00
============================================
GRAND TOTAL: Rs. 1049.99
============================================
       Thank you for your business!
```

---

## 🔧 Troubleshooting

| Problem | Solution |
|---------|----------|
| `g++ not recognized` | Run `set PATH=C:\raylib\w64devkit\bin;%PATH%` |
| `undefined reference` | Make sure PATH is set before compiling |
| `No such file or directory` | Run `cd C:\BillingSystem` first |
| Logo not showing | Make sure `logo.png` is in `C:\BillingSystem\` |
| Font looks wrong | Make sure all 3 Poppins `.ttf` files are in project
## 👨‍💻 Built With

- [C++17](https://isocpp.org/)
- [Raylib 5.0](https://www.raylib.com/)
- [Poppins Font](https://fonts.google.com/specimen/Poppins)
- [w64devkit](https://github.com/skeeto/w64devkit)
