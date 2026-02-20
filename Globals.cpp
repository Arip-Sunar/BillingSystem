#include "globals.h"
#include <cstring>


//  FONTS

Font fontRegular  = {};
Font fontBold     = {};
Font fontSemiBold = {};


//  LOGO

Texture2D logoTexture = {};


//  HASH TABLE — User store

std::unordered_map<std::string, User> userHashTable;

void HashInsertUser(const User& u) {
    userHashTable[u.username] = u;
}

bool HashUserExists(const std::string& username) {
    return userHashTable.find(username) != userHashTable.end();
}

bool HashCheckLogin(const std::string& username, const std::string& password) {
    auto it = userHashTable.find(username);
    if (it != userHashTable.end())
        return it->second.password == password;
    return false;
}

void HashRebuild() {
    userHashTable.clear();
    for (auto& u : users)
        userHashTable[u.username] = u;
}


//  POPPINS HELPERS

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


//  GLOBAL STATE DEFINITIONS

Screen             currentScreen = SCREEN_LOGIN;
std::vector<User>  users;
std::string        loggedUser    = "";
BillHistory        billHistory;

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

// History
float       histScroll     = 0;