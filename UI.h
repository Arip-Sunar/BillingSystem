#pragma once
#include "raylib.h"

// ─────────────────────────────────────────────
//  UI HELPER DECLARATIONS
// ─────────────────────────────────────────────

void  RRect      (Rectangle r, float round, Color c);
void  RRectLines (Rectangle r, float round, float thick, Color c);
bool  Button     (Rectangle r, const char* label, Color bg, Color fg, float round = 0.15f);
bool  InputBox   (Rectangle r, char* buf, int maxLen, bool focused, const char* placeholder);
bool  PasswordBox(Rectangle r, char* buf, int maxLen, bool focused, const char* placeholder);
void  GlowLine   (int x1, int y1, int x2, int y2, Color c);
void  DrawBackground();
void  DrawLogo   (int cx, int y);