#pragma once

void BulletInit();
void BulletUpdate();
void BulletDraw();
void BulletDelete();
/// <summary>
/// 弾の生成
/// </summary>
/// <param name="x">ｘ座標</param>
/// <param name="y">ｙ座標</param>
void BulletCreate(float x,float y);
