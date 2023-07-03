#pragma once

void GraphicInit();
void GraphicUpdate();
void GraphicDraw();
void GraphicDelete();
/// <summary>
/// カラフルな的の描画　たぶんアーチェリーの的
/// </summary>
/// <param name="x">ｘ座標</param>
/// <param name="y">ｙ座標</param>
/// <param name="r">半径</param>
void TargetGraphicDrawColor(float x, float y, float r);
/// <summary>
/// モノクロな的の描画　霞的
/// </summary>
/// <param name="x">ｘ座標</param>
/// <param name="y">ｙ座標</param>
/// <param name="r">半径</param>
void TargetGraphicDrawMono(float x, float y, float r);
/// <summary>
/// 矢を描画 
/// </summary>
/// <param name="x">ｘ座標</param>
/// <param name="y">ｙ座標</param>
/// <param name="s">サイズ</param>
void ArrowGraphicDrawUp(float x, float y, float s);
/// <summary>
/// プレイヤー用ハートを描画
/// </summary>
/// <param name="x">ｘ座標</param>
/// <param name="y">ｙ座標</param>
/// <param name="s">サイズ</param>
/// <param name="color">0x****** カラーコード 16進数で指定</param>
void PlayerGraphicDraw(float x,float y,float s,int color);
