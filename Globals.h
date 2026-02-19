#pragma once
#include "raylib.h"
#include <string>
#include <vector>

// ─────────────────────────────────────────────
//  WINDOW SIZE
// ─────────────────────────────────────────────
const int SW = 1100;
const int SH = 700;

// ─────────────────────────────────────────────
//  THEME COLORS
// ─────────────────────────────────────────────
const Color BG      = { 10,  12,  20, 255 };
const Color PANEL   = { 18,  22,  36, 255 };
const Color ACCENT  = { 64, 190, 255, 255 };
const Color ACCENT2 = {120,  80, 255, 255 };
const Color SUCCESS = { 50, 220, 120, 255 };
const Color DANGER  = {255,  75,  75, 255 };
const Color MUTED   = { 90, 100, 130, 255 };
const Color TXT     = {220, 225, 240, 255 };
const Color TXT_DIM = {120, 130, 160, 255 };
const Color BORDER  = { 40,  50,  80, 255 };
const Color INP_BG  = { 22,  28,  45, 255 };

// ─────────────────────────────────────────────
//  DATA STRUCTURES
// ─────────────────────────────────────────────
struct User {
    std::string username;
    std::string password;
    std::string fullname;
};

struct BillItem {
    std::string name;
    int         qty;
    float       price;
};

enum Screen { SCREEN_LOGIN, SCREEN_SIGNUP, SCREEN_BILLING };

// ─────────────────────────────────────────────
//  FONTS (defined in globals.cpp)
// ─────────────────────────────────────────────
extern Font fontRegular;
extern Font fontBold;
extern Font fontSemiBold;

// ─────────────────────────────────────────────
//  LOGO TEXTURE (defined in globals.cpp)
// ─────────────────────────────────────────────
extern Texture2D logoTexture;

// ─────────────────────────────────────────────
//  POPPINS DRAW HELPERS
// ─────────────────────────────────────────────
void DrawPoppins    (const char* text, int x, int y, float size, Color color);
void DrawPoppinsBold(const char* text, int x, int y, float size, Color color);
void DrawPoppinsSemi(const char* text, int x, int y, float size, Color color);
int  MeasurePoppins (const char* text, float size);

// ─────────────────────────────────────────────
//  GLOBAL STATE (defined in globals.cpp)
// ─────────────────────────────────────────────
extern Screen             currentScreen;
extern std::vector<User>  users;
extern std::string        loggedUser;

// Login state
extern char        loginUser[64];
extern char        loginPass[64];
extern int         loginFocus;
extern bool        loginError;
extern std::string loginErrorMsg;

// Signup state
extern char        signUser[64];
extern char        signPass[64];
extern char        signConf[64];
extern char        signName[64];
extern int         signFocus;
extern bool        signError;
extern std::string signErrorMsg;
extern std::string signSuccess;

// Billing state
extern std::vector<BillItem> cart;
extern char        itemName[64];
extern char        itemQty[16];
extern char        itemPrice[16];
extern int         billFocus;
extern std::string billMsg;
extern bool        billMsgOk;
extern float       billScroll;