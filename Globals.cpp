#include "globals.h"
#include <cstring>

// ─────────────────────────────────────────────
//  FONTS
// ─────────────────────────────────────────────
Font fontRegular  = {};
Font fontBold     = {};
Font fontSemiBold = {};

// ─────────────────────────────────────────────
//  LOGO TEXTURE
// ─────────────────────────────────────────────
Texture2D logoTexture = {};

// ─────────────────────────────────────────────
//  POPPINS DRAW HELPERS
// ─────────────────────────────────────────────
void DrawPoppins(const char* text, int x, int y, float size, Color color) {
    DrawTextEx(fontRegular, text, {(float)x,(float)y}, size, size*0.04f, color);
}
void DrawPoppinsBold(const char* text, int x, int y, float size, Color color) {
    DrawTextEx(fontBold, text, {(float)x,(float)y}, size, size*0.04f, color);
}
void DrawPoppinsSemi(const char* text, int x, int y, float size, Color color) {
    DrawTextEx(fontSemiBold, text, {(float)x,(float)y}, size, size*0.04f, color);
}
int MeasurePoppins(const char* text, float size) {
    return (int)MeasureTextEx(fontRegular, text, size, size*0.04f).x;
}

// ─────────────────────────────────────────────
//  GLOBAL STATE DEFINITIONS
// ─────────────────────────────────────────────
Screen             currentScreen = SCREEN_LOGIN;
std::vector<User>  users;
std::string        loggedUser    = "";

// Login
char        loginUser[64]  = "";
char        loginPass[64]  = "";
int         loginFocus     = -1;
bool        loginError     = false;
std::string loginErrorMsg  = "";

// Signup
char        signUser[64]   = "";
char        signPass[64]   = "";
char        signConf[64]   = "";
char        signName[64]   = "";
int         signFocus      = -1;
bool        signError      = false;
std::string signErrorMsg   = "";
std::string signSuccess    = "";

// Billing
std::vector<BillItem> cart;
char        itemName[64]   = "";
char        itemQty[16]    = "";
char        itemPrice[16]  = "";
int         billFocus      = -1;
std::string billMsg        = "";
bool        billMsgOk      = false;
float       billScroll     = 0;