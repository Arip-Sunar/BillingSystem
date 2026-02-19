#include "helpers.h"
#include "globals.h"
#include <fstream>
#include <sstream>

// ─────────────────────────────────────────────
//  USER FILE I/O
// ─────────────────────────────────────────────
void SaveUsers() {
    std::ofstream f("users.dat");
    for (auto& u : users)
        f << u.username << "|" << u.password << "|" << u.fullname << "\n";
}

void LoadUsers() {
    users.clear();
    std::ifstream f("users.dat");
    std::string line;
    while (std::getline(f, line)) {
        auto p1 = line.find('|');
        auto p2 = line.find('|', p1 + 1);
        if (p1 == std::string::npos) continue;
        User u;
        u.username = line.substr(0, p1);
        u.password = line.substr(p1 + 1, p2 - p1 - 1);
        u.fullname = (p2 != std::string::npos) ? line.substr(p2 + 1) : "";
        users.push_back(u);
    }
}

// ─────────────────────────────────────────────
//  LOOKUPS
// ─────────────────────────────────────────────
bool UserExists(const std::string& name) {
    for (auto& u : users) if (u.username == name) return true;
    return false;
}

bool CheckLogin(const std::string& name, const std::string& pass) {
    for (auto& u : users) if (u.username == name && u.password == pass) return true;
    return false;
}

// ─────────────────────────────────────────────
//  CART TOTAL
// ─────────────────────────────────────────────
float CartTotal() {
    float t = 0;
    for (auto& i : cart) t += i.qty * i.price;
    return t;
}