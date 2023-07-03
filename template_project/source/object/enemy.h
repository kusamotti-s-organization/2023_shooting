#pragma once

void EnemyInit();
void EnemyUpdate();
void EnemyDraw();
void EnemyDelete();
/// <summary>
/// 敵と弾の当たり判定
/// </summary>
/// <param name="x">ｘ座標</param>
/// <param name="y">ｙ座標</param>
/// <param name="radius">半径</param>
/// <returns></returns>
bool EnemyToBulletCollision(float x,float y,float radius);
/// <summary>
/// 敵生成 １体のみ
/// </summary>
/// <param name="x">ｘ座標</param>
/// <param name="y">ｙ座標</param>
/// <param name="mx">ｘ移動ベクトル</param>
/// <param name="my">ｙ移動ベクトル</param>
/// <param name="color">色 カラフルかモノクロか</param>
void EnemyCreate(float x,float y,float mx,float my,bool color = true);
//敵を倒した数
int GetKillNum();
//敵を生成した数
int GetInstanceNum();
//敵を生成した数をリセットする
void ResetInstanceNum();
//敵が画面内にいる数
int GetActiveEnemy();

enum EnemyMovePatternState {
	left=0//左端から右へ
	,right//右端から左へ
	,top//上端から下へ
};
/// <summary>
/// パターンによって敵を生成
/// </summary>
/// <param name="pattarn">enumで渡す</param>
void EnemyMovePattarn(EnemyMovePatternState pattarn);

