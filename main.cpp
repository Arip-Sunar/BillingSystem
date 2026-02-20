#include "raylib.h"
#include "globals.h"
#include "helpers.h"
#include "login.h"
#include "signup.h"
#include "billing.h"
#include "history.h"

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

    // Load logo
    logoTexture = LoadTexture("logo.png");
    SetTextureFilter(logoTexture, TEXTURE_FILTER_BILINEAR);

    // Load users into vector + rebuild hash table
    LoadUsers();
    if (users.empty()) {
        User admin = {"admin","admin123","Administrator"};
        users.push_back(admin);
        HashInsertUser(admin);  // insert into hash table
        SaveUsers();
    }

    while (!WindowShouldClose()) {
        BeginDrawing();

        switch (currentScreen) {
            case SCREEN_LOGIN:   DrawLoginScreen();   break;
            case SCREEN_SIGNUP:  DrawSignupScreen();  break;
            case SCREEN_BILLING: DrawBillingScreen(); break;
            case SCREEN_HISTORY: DrawHistoryScreen(); break;
        }

        EndDrawing();
    }

    UnloadFont(fontRegular);
    UnloadFont(fontBold);
    UnloadFont(fontSemiBold);
    UnloadTexture(logoTexture);
    CloseWindow();
    return 0;
}