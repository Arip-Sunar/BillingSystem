#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <unordered_map>


//  WINDOW SIZE

const int SW = 1100;
const int SH = 700;


//  THEME COLORS

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


//  DATA STRUCTURES

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


//  LINKED LIST — Bill History
//  Each node stores one complete saved bill

struct BillNode {
    std::vector<BillItem> items;   // all items in this bill
    float                 total;   // grand total
    std::string           cashier; // who made the bill
    std::string           date;    // when bill was made
    BillNode*             next;    // pointer to next bill

    BillNode(std::vector<BillItem> i, float t, std::string c, std::string d)
        : items(i), total(t), cashier(c), date(d), next(nullptr) {}
};

// Linked List class to manage bill history
struct BillHistory {
    BillNode* head;
    int       count;

    BillHistory() : head(nullptr), count(0) {}

    // Add new bill at the front (most recent first)
    void push(std::vector<BillItem> items, float total,
              std::string cashier, std::string date) {
        BillNode* node = new BillNode(items, total, cashier, date);
        node->next = head;
        head = node;
        count++;
    }

    // Free all nodes
    void clear() {
        BillNode* cur = head;
        while (cur) {
            BillNode* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = nullptr;
        count = 0;
    }

    ~BillHistory() { clear(); }
};


//  HASH TABLE — User Lookup
//  unordered_map gives O(1) average lookup
//  Key = username, Value = User struct

// Declared in globals.cpp
extern std::unordered_map<std::string, User> userHashTable;

// Hash table helper functions
void   HashInsertUser  (const User& u);
bool   HashUserExists  (const std::string& username);
bool   HashCheckLogin  (const std::string& username, const std::string& password);
void   HashRebuild     ();   // rebuild from users vector

enum Screen { SCREEN_LOGIN, SCREEN_SIGNUP, SCREEN_BILLING, SCREEN_HISTORY };


//  FONTS

extern Font fontRegular;
extern Font fontBold;
extern Font fontSemiBold;


//  LOGO TEXTURE

extern Texture2D logoTexture;


//  POPPINS DRAW HELPERS

void DrawPoppins    (const char* text, int x, int y, float size, Color color);
void DrawPoppinsBold(const char* text, int x, int y, float size, Color color);
void DrawPoppinsSemi(const char* text, int x, int y, float size, Color color);
int  MeasurePoppins (const char* text, float size);


//  GLOBAL STATE

extern Screen             currentScreen;
extern std::vector<User>  users;
extern std::string        loggedUser;
extern BillHistory        billHistory;

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

// History screen state
extern float       histScroll;