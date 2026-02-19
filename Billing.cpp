#include "billing.h"
#include "globals.h"
#include "helpers.h"
#include "ui.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>

void DrawBillingScreen() {
    DrawBackground();

    // Top Bar
    DrawRectangle(0,0,SW,56,PANEL);
    GlowLine(0,56,SW,56,{40,50,80,255});
    DrawPoppinsBold("NEPSys", 24, 16, 20, ACCENT);
    DrawPoppins("Billing Dashboard", 108, 20, 14, TXT_DIM);

    std::string uinfo = "Logged in: " + loggedUser;
    DrawPoppins(uinfo.c_str(), SW-MeasurePoppins(uinfo.c_str(),13)-120, 21, 13, TXT_DIM);

    if (Button({(float)SW-110,12,90,32}, "LOGOUT", {60,20,20,200}, DANGER, 0.25f)) {
        currentScreen=SCREEN_LOGIN;
        loggedUser=""; loginFocus=-1; loginError=false;
        memset(loginUser,0,sizeof(loginUser));
        memset(loginPass,0,sizeof(loginPass));
        cart.clear();
    }

    // Left panel: Add Item
    Rectangle leftPanel = {16,72,340,290};
    RRect(leftPanel,0.04f,PANEL);
    RRectLines(leftPanel,0.04f,1.2f,BORDER);
    DrawPoppinsSemi("Add Item", 36, 90, 16, ACCENT);
    GlowLine(36,112,200,112,ACCENT);

    float py = 122;
    DrawPoppins("Item Name", 36,(int)py,13,TXT_DIM);
    Rectangle rName={36,py+16,300,38};
    if (InputBox(rName,itemName,64,billFocus==0,"e.g. Laptop")) billFocus=0;

    py+=66;
    DrawPoppins("Quantity",36,(int)py,13,TXT_DIM);
    Rectangle rQty={36,py+16,140,38};
    if (InputBox(rQty,itemQty,16,billFocus==1,"1")) billFocus=1;

    DrawPoppins("Price (Rs.)",188,(int)py,13,TXT_DIM);
    Rectangle rPrice={188,py+16,148,38};
    if (InputBox(rPrice,itemPrice,16,billFocus==2,"0.00")) billFocus=2;

    py+=66;
    if (Button({36,py,300,44},"+ ADD TO BILL",SUCCESS,BG)) {
        if (strlen(itemName)==0) { billMsg="Enter item name."; billMsgOk=false; }
        else {
            int q=atoi(itemQty); float p=atof(itemPrice);
            if (q<=0) { billMsg="Quantity must be > 0."; billMsgOk=false; }
            else if (p<0) { billMsg="Price cannot be negative."; billMsgOk=false; }
            else {
                bool found=false;
                for (auto& it:cart) if (it.name==itemName){it.qty+=q;found=true;break;}
                if (!found) cart.push_back({itemName,q,p});
                billMsg="Item added!"; billMsgOk=true;
                memset(itemName,0,sizeof(itemName));
                memset(itemQty,0,sizeof(itemQty));
                memset(itemPrice,0,sizeof(itemPrice));
                billFocus=-1;
            }
        }
    }
    if (!billMsg.empty())
        DrawPoppins(billMsg.c_str(),36,(int)py+52,13,billMsgOk?SUCCESS:DANGER);

    // Bill Table
    Rectangle tablePanel={370,72,SW-386.0f,(float)SH-160};
    RRect(tablePanel,0.03f,PANEL);
    RRectLines(tablePanel,0.03f,1.2f,BORDER);
    DrawPoppinsSemi("CURRENT BILL",390,90,14,ACCENT);

    float tx=370,ty=114;
    DrawRectangle((int)tx,(int)ty,(int)(SW-386),32,{30,38,65,200});
    int cols[]={390,570,680,790};
    const char* headers[]={"Item Name","Qty","Unit Price","Total"};
    for (int i=0;i<4;i++) DrawPoppinsSemi(headers[i],cols[i],(int)ty+8,12,ACCENT);
    GlowLine((int)tx,(int)(ty+32),(int)(tx+SW-386),(int)(ty+32),BORDER);

    BeginScissorMode((int)tx,(int)(ty+33),(int)(SW-388),(int)(SH-230));
    float ry=ty+36-billScroll;
    for (int i=0;i<(int)cart.size();i++) {
        auto& it=cart[i];
        Color rowC=(i%2==0)?Color{20,26,42,255}:Color{24,30,50,255};
        DrawRectangle((int)tx,(int)ry,(int)(SW-386),36,rowC);
        DrawPoppins(it.name.c_str(),cols[0],(int)ry+10,13,TXT);
        DrawPoppins(std::to_string(it.qty).c_str(),cols[1],(int)ry+10,13,TXT);
        std::ostringstream ps; ps<<"Rs."<<std::fixed<<std::setprecision(2)<<it.price;
        DrawPoppins(ps.str().c_str(),cols[2],(int)ry+10,13,TXT);
        std::ostringstream ts; ts<<"Rs."<<std::fixed<<std::setprecision(2)<<it.qty*it.price;
        DrawPoppins(ts.str().c_str(),cols[3],(int)ry+10,13,SUCCESS);
        if (Button({(float)SW-110,(float)ry+6,60,24},"X DEL",{60,18,18,200},DANGER,0.3f)) {
            cart.erase(cart.begin()+i); i--;
        }
        ry+=36;
    }
    if (cart.empty())
        DrawPoppins("No items added yet.",cols[0],(int)(ty+60-billScroll),13,TXT_DIM);
    EndScissorMode();

    float contentH=cart.size()*36.0f;
    float viewH=SH-230.0f;
    float wheel=GetMouseWheelMove();
    if (wheel!=0) {
        billScroll-=wheel*30;
        if (billScroll<0) billScroll=0;
        if (contentH>viewH && billScroll>contentH-viewH) billScroll=contentH-viewH;
        if (contentH<=viewH) billScroll=0;
    }

    // Bottom Summary Bar
    DrawRectangle(0,SH-88,SW,88,PANEL);
    GlowLine(0,SH-88,SW,SH-88,BORDER);
    std::ostringstream tot;
    tot<<"TOTAL:  Rs. "<<std::fixed<<std::setprecision(2)<<CartTotal();
    DrawPoppinsBold(tot.str().c_str(),390,SH-62,20,ACCENT);
    std::string cnt=std::to_string(cart.size())+" item(s)";
    DrawPoppins(cnt.c_str(),390,SH-36,12,TXT_DIM);

    // Print Bill
    if (Button({(float)SW-280,(float)SH-72,120,44},"PRINT BILL",ACCENT,BG)) {
        if (cart.empty()) { billMsg="Cart is empty!"; billMsgOk=false; }
        else {
            std::ofstream r("receipt.txt");
            time_t now=time(0); std::string dt=ctime(&now);
            r<<"============================================\n";
            r<<"             BillingSystem Receipt\n";
            r<<"============================================\n";
            r<<"Date: "<<dt<<"Cashier: "<<loggedUser<<"\n";
            r<<"--------------------------------------------\n";
            r<<std::left<<std::setw(22)<<"Item"<<std::setw(6)<<"Qty"<<std::setw(12)<<"Price"<<"Total\n";
            r<<"--------------------------------------------\n";
            for (auto& it:cart)
                r<<std::left<<std::setw(22)<<it.name<<std::setw(6)<<it.qty
                 <<std::setw(12)<<it.price<<it.qty*it.price<<"\n";
            r<<"============================================\n";
            r<<"GRAND TOTAL: Rs. "<<std::fixed<<std::setprecision(2)<<CartTotal()<<"\n";
            r<<"============================================\n";
            r<<"       Thank you for your business!\n";
            r.close();
            billMsg="Receipt saved to receipt.txt"; billMsgOk=true;
        }
    }

    if (Button({(float)SW-148,(float)SH-72,120,44},"CLEAR BILL",{60,20,20,200},DANGER)) {
        cart.clear(); billMsg="Bill cleared."; billMsgOk=true; billScroll=0;
    }

    if (billFocus>=0 && IsKeyPressed(KEY_TAB)) billFocus=(billFocus+1)%3;

    // Version
    DrawPoppins("NEPSys v1.0", SW-MeasurePoppins("NEPSys v1.0",11)-8, SH-16, 11, {40,50,80,200});
}