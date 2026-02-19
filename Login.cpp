#include "login.h"
#include "globals.h"
#include "helpers.h"
#include "ui.h"
#include <cstring>

void DrawLoginScreen() {
    DrawBackground();

    // Card
    Rectangle card = { SW/2-200.0f, SH/2-240.0f, 400, 480 };
    RRect(card, 0.06f, PANEL);
    RRectLines(card, 0.06f, 1.5f, BORDER);

    float cx = card.x + card.width/2;
    float cy = card.y + 20;

    // ── Logo Image ────────────────────────────
    if (logoTexture.id > 0) {
        // Scale logo to fit nicely (max 180px wide, 80px tall)
        float maxW = 180, maxH = 80;
        float scaleW = maxW / logoTexture.width;
        float scaleH = maxH / logoTexture.height;
        float scale  = (scaleW < scaleH) ? scaleW : scaleH;
        float lw = logoTexture.width  * scale;
        float lh = logoTexture.height * scale;
        DrawTextureEx(logoTexture,
                      { cx - lw/2, cy },
                      0.0f, scale, WHITE);
        cy += lh + 16;
    } else {
        // Fallback if logo not found
        DrawLogo((int)cx, (int)cy);
        cy += 80;
    }

    // Glow line under logo
    GlowLine((int)(cx-60), (int)cy, (int)(cx+60), (int)cy, ACCENT);
    cy += 16;

    // Title
    DrawPoppinsBold("Welcome to NEPSys",
        (int)(cx - MeasurePoppins("Welcome to NEPSys", 20)/2), (int)cy, 20, TXT);
    DrawPoppins("Fill the boxes for Signin",
        (int)(cx - MeasurePoppins("Fill the boxes for Signin", 13)/2), (int)cy+26, 13, TXT_DIM);

    // Username
    cy += 64;
    DrawPoppins("Username", (int)card.x+30, (int)cy, 13, TXT_DIM);
    Rectangle rUser = { card.x+30, cy+18, card.width-60, 42 };
    if (InputBox(rUser, loginUser, 64, loginFocus==0, "Enter username")) loginFocus=0;

    // Password
    cy += 78;
    DrawPoppins("Password", (int)card.x+30, (int)cy, 13, TXT_DIM);
    Rectangle rPass = { card.x+30, cy+18, card.width-60, 42 };
    if (PasswordBox(rPass, loginPass, 64, loginFocus==1, "Enter password")) loginFocus=1;

    // Sign In button
    cy += 80;
    auto tryLogin = [&]() {
        if (CheckLogin(loginUser, loginPass)) {
            loggedUser=loginUser; currentScreen=SCREEN_BILLING;
            billMsg=""; cart.clear(); loginError=false;
        } else { loginError=true; loginErrorMsg="Invalid username or password"; }
    };

    if (Button({card.x+30, cy, card.width-60, 44}, "SIGN IN", ACCENT, BG)) tryLogin();

    if (loginError)
        DrawPoppins(loginErrorMsg.c_str(),
            (int)(cx - MeasurePoppins(loginErrorMsg.c_str(), 13)/2),
            (int)cy+52, 13, DANGER);

    // Signup link
    cy += 70;
    DrawPoppins("Don't have an account?",
        (int)(cx - MeasurePoppins("Don't have an account?", 13)/2), (int)cy, 13, TXT_DIM);

    if (Button({cx-60, cy+20, 120, 32}, "SIGN UP", {30,38,60,200}, ACCENT, 0.25f)) {
        currentScreen=SCREEN_SIGNUP;
        loginFocus=-1; loginError=false;
        memset(loginUser,0,sizeof(loginUser));
        memset(loginPass,0,sizeof(loginPass));
        signFocus=-1; signError=false; signSuccess="";
        memset(signUser,0,sizeof(signUser));
        memset(signPass,0,sizeof(signPass));
        memset(signConf,0,sizeof(signConf));
        memset(signName,0,sizeof(signName));
    }

    // Keyboard shortcuts
    if (loginFocus>=0 && IsKeyPressed(KEY_TAB)) loginFocus=(loginFocus+1)%2;
    if (IsKeyPressed(KEY_ENTER) && loginFocus>=0) tryLogin();
}