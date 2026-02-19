/*
 * BillingSystem — C++ Raylib GUI
 *
 * File Structure:
 *   main.cpp      — Entry point (this file)
 *   globals.h/cpp — Shared state, structs, constants
 *   ui.h/cpp      — Shared UI helpers (Button, InputBox, etc.)
 *   helpers.h/cpp — User auth & data helpers
 *   login.h/cpp   — Login screen
 *   signup.h/cpp  — Signup screen
 *   billing.h/cpp — Billing screen
 *
 /*
 * BillingSystem — C++ Raylib GUI
 *
 * Build (Windows MinGW):
 *   g++ main.cpp globals.cpp ui.cpp helpers.cpp login.cpp signup.cpp billing.cpp ^
 *       -o BillingSystem.exe -I"C:/raylib-5.0_win64_mingw-w64/include" ^
 *       -L"C:/raylib-5.0_win64_mingw-w64/lib" -lraylib -lopengl32 -lgdi32 -lwinmm
 */

#include "raylib.h"
#include "globals.h"
#include "helpers.h"
#include "login.h"
#include "signup.h"
#include "billing.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SW, SH, "BillingSystem");
    SetTargetFPS(60);

    // Load Poppins fonts
    fontRegular  = LoadFontEx("Poppins-Regular.ttf",  64, 0, 250);
    fontBold     = LoadFontEx("Poppins-Bold.ttf",     64, 0, 250);
    fontSemiBold = LoadFontEx("Poppins-SemiBold.ttf", 64, 0, 250);
    SetTextureFilter(fontRegular.texture,  TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fontBold.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fontSemiBold.texture, TEXTURE_FILTER_BILINEAR);

    // Load logo image
    logoTexture = LoadTexture("logo.png");
    SetTextureFilter(logoTexture, TEXTURE_FILTER_BILINEAR);

    // Load saved users; create default admin if none exist
    LoadUsers();
    if (users.empty()) {
        users.push_back({ "admin", "admin123", "Administrator" });
        SaveUsers();
    }

    while (!WindowShouldClose()) {
        BeginDrawing();

        switch (currentScreen) {
            case SCREEN_LOGIN:   DrawLoginScreen();   break;
            case SCREEN_SIGNUP:  DrawSignupScreen();  break;
            case SCREEN_BILLING: DrawBillingScreen(); break;
        }

        EndDrawing();
    }

    // Cleanup
    UnloadFont(fontRegular);
    UnloadFont(fontBold);
    UnloadFont(fontSemiBold);
    UnloadTexture(logoTexture);
    CloseWindow();
    return 0;
}