#include "ui.h"
#include "globals.h"
#include <string>
#include <cstring>

void RRect(Rectangle r, float round, Color c) {
    DrawRectangleRounded(r, round, 8, c);
}
void RRectLines(Rectangle r, float round, float thick, Color c) {
    DrawRectangleRoundedLines(r, round, 8, thick, c);
}

bool Button(Rectangle r, const char* label, Color bg, Color fg, float round) {
    Vector2 mouse = GetMousePosition();
    bool hov = CheckCollisionPointRec(mouse, r);
    Color col = hov ? ColorBrightness(bg, 0.25f) : bg;
    RRect(r, round, col);
    if (hov) RRectLines(r, round, 1.5f, ACCENT);
    float fs = r.height * 0.38f;
    Vector2 ts = MeasureTextEx(fontSemiBold, label, fs, fs * 0.04f);
    DrawTextEx(fontSemiBold, label,
               { r.x + r.width / 2 - ts.x / 2, r.y + r.height / 2 - ts.y / 2 },
               fs, fs * 0.04f, fg);
    return hov && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

bool InputBox(Rectangle r, char* buf, int maxLen, bool focused, const char* placeholder) {
    bool hov = CheckCollisionPointRec(GetMousePosition(), r);
    RRect(r, 0.12f, INP_BG);
    RRectLines(r, 0.12f, focused ? 2.0f : 1.0f, focused ? ACCENT : BORDER);
    float fs = 15;
    bool empty = (strlen(buf) == 0);
    DrawTextEx(fontRegular, empty ? placeholder : buf,
               { r.x + 14, r.y + r.height / 2 - fs / 2 }, fs, fs * 0.04f, empty ? TXT_DIM : TXT);
    if (focused) {
        if (((int)(GetTime() * 2)) % 2 == 0) {
            Vector2 tw = MeasureTextEx(fontRegular, buf, fs, fs * 0.04f);
            DrawLine((int)r.x + 14 + (int)tw.x, (int)r.y + 8,
                     (int)r.x + 14 + (int)tw.x, (int)(r.y + r.height - 8), ACCENT);
        }
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && (int)strlen(buf) < maxLen - 1) {
                int len = strlen(buf); buf[len] = (char)key; buf[len+1] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(buf) > 0) buf[strlen(buf)-1] = '\0';
    }
    return hov && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

bool PasswordBox(Rectangle r, char* buf, int maxLen, bool focused, const char* placeholder) {
    bool hov = CheckCollisionPointRec(GetMousePosition(), r);
    RRect(r, 0.12f, INP_BG);
    RRectLines(r, 0.12f, focused ? 2.0f : 1.0f, focused ? ACCENT : BORDER);
    float fs = 15;
    bool empty = (strlen(buf) == 0);
    if (empty) {
        DrawTextEx(fontRegular, placeholder,
                   { r.x+14, r.y+r.height/2-fs/2 }, fs, fs*0.04f, TXT_DIM);
    } else {
        std::string stars(strlen(buf), '*');
        DrawTextEx(fontRegular, stars.c_str(),
                   { r.x+14, r.y+r.height/2-fs/2 }, fs, fs*0.04f, TXT);
    }
    if (focused) {
        if (((int)(GetTime()*2))%2==0) {
            std::string stars(strlen(buf),'*');
            Vector2 tw = MeasureTextEx(fontRegular, stars.c_str(), fs, fs*0.04f);
            DrawLine((int)r.x+14+(int)tw.x,(int)r.y+8,
                     (int)r.x+14+(int)tw.x,(int)(r.y+r.height-8),ACCENT);
        }
        int key = GetCharPressed();
        while (key > 0) {
            if (key>=32 && (int)strlen(buf)<maxLen-1) {
                int len=strlen(buf); buf[len]=(char)key; buf[len+1]='\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(buf)>0) buf[strlen(buf)-1]='\0';
    }
    return hov && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

void GlowLine(int x1, int y1, int x2, int y2, Color c) {
    Color dim = { c.r, c.g, c.b, 60 };
    DrawLineEx({(float)x1,(float)y1},{(float)x2,(float)y2}, 4, dim);
    DrawLineEx({(float)x1,(float)y1},{(float)x2,(float)y2}, 1.5f, c);
}

void DrawBackground() {
    ClearBackground(BG);
    for (int x=0; x<SW; x+=60) DrawLine(x,0,x,SH,{30,38,60,25});
    for (int y=0; y<SH; y+=60) DrawLine(0,y,SW,y,{30,38,60,25});
    DrawCircleGradient(200,150,260,{64,190,255,18},{0,0,0,0});
    DrawCircleGradient(900,550,220,{120,80,255,18},{0,0,0,0});
}

void DrawLogo(int cx, int y) {
    float fs = 36;
    const char* t1 = "NEP";
    const char* t2 = "SYS";
    Vector2 w1 = MeasureTextEx(fontBold, t1, fs, fs*0.04f);
    Vector2 w2 = MeasureTextEx(fontBold, t2, fs, fs*0.04f);
    float total = w1.x + w2.x + 4;
    DrawTextEx(fontBold, t1, {cx-total/2,          (float)y}, fs, fs*0.04f, ACCENT);
    DrawTextEx(fontBold, t2, {cx-total/2+w1.x+4,   (float)y}, fs, fs*0.04f, ACCENT2);
    const char* sub = "BILLING SYSTEM";
    float sfs = 11;
    Vector2 sw2 = MeasureTextEx(fontRegular, sub, sfs, sfs*0.04f);
    DrawTextEx(fontRegular, sub, {cx-sw2.x/2,(float)y+42}, sfs, sfs*0.04f, MUTED);
    GlowLine(cx-60,y+60,cx+60,y+60,ACCENT);
}