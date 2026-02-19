#include "signup.h"
#include "globals.h"
#include "helpers.h"
#include "ui.h"
#include <cstring>

void DrawSignupScreen() {
    DrawBackground();

    // Make card taller to fit back button inside
    Rectangle card = { SW/2-210.0f, SH/2-290.0f, 420, 580 };
    RRect(card, 0.05f, PANEL);
    RRectLines(card, 0.05f, 1.5f, BORDER);

    DrawLogo(SW/2, (int)card.y+28);

    float cx = card.x + card.width/2;
    float cy = card.y + 135;

    DrawPoppinsBold("Create your Account",
        (int)(cx - MeasurePoppins("Create your Account", 20)/2), (int)cy, 20, TXT);
    DrawPoppins("Please fill the boxes for information stored",
        (int)(cx - MeasurePoppins("Please fill the boxes for information stored", 13)/2), (int)cy+26, 13, TXT_DIM);

    // Full Name
    cy += 64;
    DrawPoppins("Full Name", (int)card.x+30, (int)cy, 13, TXT_DIM);
    Rectangle rName = { card.x+30, cy+18, card.width-60, 40 };
    if (InputBox(rName, signName, 64, signFocus==0, "Arip Sunar")) signFocus=0;

    // Username
    cy += 66;
    DrawPoppins("Username", (int)card.x+30, (int)cy, 13, TXT_DIM);
    Rectangle rUser = { card.x+30, cy+18, card.width-60, 40 };
    if (InputBox(rUser, signUser, 64, signFocus==1, "Choose a username")) signFocus=1;

    // Password
    cy += 66;
    DrawPoppins("Password", (int)card.x+30, (int)cy, 13, TXT_DIM);
    Rectangle rPass = { card.x+30, cy+18, card.width-60, 40 };
    if (PasswordBox(rPass, signPass, 64, signFocus==2, "Create password")) signFocus=2;

    // Confirm Password
    cy += 66;
    DrawPoppins("Confirm Password", (int)card.x+30, (int)cy, 13, TXT_DIM);
    Rectangle rConf = { card.x+30, cy+18, card.width-60, 40 };
    if (PasswordBox(rConf, signConf, 64, signFocus==3, "Re-enter password")) signFocus=3;

    // Create Account button
    cy += 66;
    if (Button({card.x+30, cy, card.width-60, 44}, "CREATE your ACCOUNT", ACCENT2, TXT)) {
        if (strlen(signName)==0||strlen(signUser)==0||strlen(signPass)==0||strlen(signConf)==0) {
            signError=true; signErrorMsg="Please fill the boxes for information stored"; signSuccess="";
        } else if (std::string(signPass)!=std::string(signConf)) {
            signError=true; signErrorMsg="Passwords do not match"; signSuccess="";
        } else if (UserExists(signUser)) {
            signError=true; signErrorMsg="Username already taken"; signSuccess="";
        } else {
            users.push_back({signUser,signPass,signName});
            SaveUsers();
            signError=false; signSuccess="Account created successfully ! ";
        }
    }

    // Status messages
    if (signError)
        DrawPoppins(signErrorMsg.c_str(),
            (int)(cx - MeasurePoppins(signErrorMsg.c_str(), 13)/2),
            (int)cy+52, 13, DANGER);
    if (!signSuccess.empty())
        DrawPoppins(signSuccess.c_str(),
            (int)(cx - MeasurePoppins(signSuccess.c_str(), 13)/2),
            (int)cy+52, 13, SUCCESS);

    // Divider line inside card
    cy += 68;
    GlowLine((int)card.x+30, (int)cy, (int)(card.x+card.width-30), (int)cy, BORDER);

    // Back to Login button — INSIDE the card
    cy += 14;
    DrawPoppins("Already have an account?",
        (int)(cx - MeasurePoppins("Already have an account?", 13)/2),
        (int)cy, 13, TXT_DIM);

    cy += 20;
    if (Button({card.x+30, cy, card.width-60, 40}, " BACK TO LOGIN", {30,38,60,255}, ACCENT, 0.2f))
        currentScreen=SCREEN_LOGIN;

    // Tab navigation
    if (signFocus>=0 && IsKeyPressed(KEY_TAB)) signFocus=(signFocus+1)%4;
}