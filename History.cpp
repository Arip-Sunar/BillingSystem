#include "history.h"
#include "globals.h"
#include "helpers.h"
#include "ui.h"
#include <sstream>
#include <iomanip>


//  HISTORY SCREEN
//  Traverses the Linked List of saved bills
//  and displays them newest first

void DrawHistoryScreen() {
    DrawBackground();

    // Top bar
    DrawRectangle(0,0,SW,56,PANEL);
    GlowLine(0,56,SW,56,{40,50,80,255});
    DrawPoppinsBold("NEPSys",24,16,20,ACCENT);
    DrawPoppins("Bill History",108,20,14,TXT_DIM);

    // Bill count
    std::string cnt = std::to_string(billHistory.count)+" bill(s) in history";
    DrawPoppins(cnt.c_str(), SW-MeasurePoppins(cnt.c_str(),13)-120, 21, 13, TXT_DIM);

    // Back button
    if (Button({(float)SW-110,12,90,32},"BACK",{30,38,60,200},ACCENT,0.25f))
        currentScreen=SCREEN_BILLING;

    // DSA label
    DrawPoppins("DSA: Linked List traversal — each bill is a node linked to the next",
                24, 62, 11, {60,80,120,200});

    // No history message
    if (billHistory.head == nullptr) {
        DrawPoppinsBold("No bill history yet.",
            SW/2 - MeasurePoppins("No bill history yet.",18)/2,
            SH/2-20, 18, TXT_DIM);
        DrawPoppins("Print a bill from the Billing Screen to save it here.",
            SW/2 - MeasurePoppins("Print a bill from the Billing Screen to save it here.",13)/2,
            SH/2+14, 13, TXT_DIM);
        return;
    }

    // Traverse linked list and draw each bill node
    float viewH = (float)(SH - 80);
    BeginScissorMode(0, 80, SW, (int)viewH);

    float oy = 88 - histScroll;
    BillNode* cur = billHistory.head;
    int billNum = billHistory.count;

    while (cur != nullptr) {
        // Calculate card height based on items
        float cardH = 90 + cur->items.size() * 28.0f;
        Rectangle card = { 20, oy, (float)SW-40, cardH };

        RRect(card, 0.03f, PANEL);
        RRectLines(card, 0.03f, 1.2f, BORDER);

        // Bill header
        std::string billLabel = "Bill #" + std::to_string(billNum);
        DrawPoppinsBold(billLabel.c_str(), (int)card.x+16, (int)oy+10, 14, ACCENT);
        DrawPoppins(cur->date.c_str(), (int)card.x+16, (int)oy+28, 11, TXT_DIM);
        DrawPoppins(("Cashier: "+cur->cashier).c_str(),
                    (int)card.x+16, (int)oy+42, 11, TXT_DIM);

        // Node pointer info (shows linked list concept)
        std::string nodeInfo = cur->next ?
            "-> next node: Bill #"+std::to_string(billNum-1) :
            "-> next: NULL (tail)";
        DrawPoppins(nodeInfo.c_str(),
            (int)(card.x+card.width)-MeasurePoppins(nodeInfo.c_str(),11)-12,
            (int)oy+10, 11, {60,80,120,200});

        GlowLine((int)card.x+12,(int)oy+60,
                 (int)(card.x+card.width)-12,(int)oy+60, BORDER);

        // Item rows
        float iy = oy + 66;
        int cols[] = {40, 260, 380, 500};
        DrawPoppinsSemi("Item",    cols[0],(int)iy,11,MUTED);
        DrawPoppinsSemi("Qty",     cols[1],(int)iy,11,MUTED);
        DrawPoppinsSemi("Price",   cols[2],(int)iy,11,MUTED);
        DrawPoppinsSemi("Total",   cols[3],(int)iy,11,MUTED);
        iy += 18;

        for (auto& it : cur->items) {
            DrawPoppins(it.name.c_str(), cols[0],(int)iy,12,TXT);
            DrawPoppins(std::to_string(it.qty).c_str(), cols[1],(int)iy,12,TXT);
            std::ostringstream ps;
            ps<<"Rs."<<std::fixed<<std::setprecision(2)<<it.price;
            DrawPoppins(ps.str().c_str(), cols[2],(int)iy,12,TXT);
            std::ostringstream ts;
            ts<<"Rs."<<std::fixed<<std::setprecision(2)<<it.qty*it.price;
            DrawPoppins(ts.str().c_str(), cols[3],(int)iy,12,SUCCESS);
            iy += 28;
        }

        // Grand total
        std::ostringstream gt;
        gt<<"GRAND TOTAL: Rs."<<std::fixed<<std::setprecision(2)<<cur->total;
        DrawPoppinsBold(gt.str().c_str(),
            (int)(card.x+card.width)-MeasurePoppins(gt.str().c_str(),13)-16,
            (int)(oy+cardH-22), 13, ACCENT);

        oy += cardH + 14;
        cur = cur->next;  // traverse to next node in linked list
        billNum--;
    }

    EndScissorMode();

    // Scroll
    float totalH = 0;
    BillNode* tmp = billHistory.head;
    while (tmp) {
        totalH += 90 + tmp->items.size()*28.0f + 14;
        tmp = tmp->next;
    }
    float wheel = GetMouseWheelMove();
    if (wheel!=0) {
        histScroll -= wheel*40;
        if (histScroll<0) histScroll=0;
        float maxScroll = totalH - viewH + 80;
        if (maxScroll>0 && histScroll>maxScroll) histScroll=maxScroll;
        if (totalH<=viewH) histScroll=0;
    }
}