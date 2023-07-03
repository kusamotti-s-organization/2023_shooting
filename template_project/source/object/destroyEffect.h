#pragma once

void DestroyEffectInit();
void DestroyEffectUpdate();
void DestroyEffectDraw();
void DestroyEffectDelete ();

/// <summary>
/// エフェクトを生成する
/// </summary>
/// /// <param name="x">ｘ座標</param>
/// /// <param name="y">ｙ座標</param>
/// /// <param name="r">半径</param>
void EffectOn(float x,float y,float r);