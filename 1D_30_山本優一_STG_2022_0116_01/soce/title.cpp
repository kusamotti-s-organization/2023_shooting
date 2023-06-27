#include"title.h"
#include<DxLib.h>
#include"config.h"
#include<string>
namespace {
    std::string str= "Rキー以外の\n何かキーを押してスタート";

    int num = 0;
    bool keyflag = false;
    bool keystop = false;
    bool nextflag = false;

    VECTOR squarepos[2] = {};
}
void TitleInit(){
    num = 0;
    keyflag = false;
    keystop = true;
    nextflag = false;
    squarepos[0].x = SCREEN_WIDTH  / 7.0f;
    squarepos[0].y = SCREEN_HEIGHT / 2.8f;
    squarepos[1].x = SCREEN_WIDTH  / 7.0f+(128*9/2)+10;
    squarepos[1].y = SCREEN_HEIGHT / 2.8f+ 128;
}
bool TitleUpdate(){
    keyflag = CheckHitKeyAll() != 0;
    if (keyflag && !keystop) {
        nextflag = true;
    }
    keystop= keyflag;

    return nextflag;
}
void TitleDraw(){
    printfDx("\n");
    printfDx("\n");
    printfDx(" 操作説明\n");
    printfDx("\n");
    printfDx("移動　　　　　 ：WASD\n");
    printfDx("ダッシュ移動　 ：LeftShift\n");
    printfDx("弾を打つ　　　 ：MouseLeft\n");
    printfDx("弾を打つオート ：MouseRight\n");
    SetFontSize(128);
    DrawBox(squarepos[0].x, squarepos[1].y -10,  squarepos[1].x,     squarepos[1].y-128/8   ,GetColor(100,100,100),true);
    DrawBox(squarepos[0].x, squarepos[0].y,      squarepos[1].x,     squarepos[1].y         ,GetColor(255,255,255),false);
    DrawFormatString(squarepos[0].x, squarepos[0].y, GetColor(200, 200, 200), "T i t l e");
    SetFontSize(16);
    DrawFormatString(SCREEN_WIDTH / 2.5f, SCREEN_HEIGHT / 1.2f, GetColor(200, 200, 200), str.c_str());
}
void TitleDelete(){

}
