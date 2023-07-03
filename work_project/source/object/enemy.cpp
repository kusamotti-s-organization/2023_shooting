#include "enemy.h"

#include<DxLib.h>
#include<cassert>
#include"../main/config.h"
#include"../common.h"
#include"../sceneManager.h"
#include"graphic.h"
#include"destroyEffect.h"

namespace {
	struct Enemy {
		Position m_position;//座標
		Position m_moveVector;//移動ベクトル
		bool isActive;//生きているか
		bool color;//カラフルかモノクロか
	};
	constexpr int MAX_ENEMY_NUM = 400 +1;//敵の最大数
	constexpr float ENMEY_INSTANCE_TIME = 0.2f;//敵の生成クールタイム
	constexpr float ENEMY_RADIUS = 20.f;//敵の大きさ 半径
	Enemy enemies[MAX_ENEMY_NUM];//Enemyのインスタンス

	int frameCounter;//敵のクールタイムに使った カウンタ
	int instanceCount;//敵の生成数を数える
	int instanceTime;//クールタイムのカウンタ
	int enemiesKillCount;//敵の倒した数を数える
}

void EnemyInit(){
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		enemies[i].m_position = Position{0,0};//structの初期化 方法
		enemies[i].m_moveVector= Position{0,0};//structの初期化 方法
		enemies[i].isActive = false;
		enemies[i].color = false;
	}
	frameCounter = 0;
	instanceCount =0;
	enemiesKillCount = 0;
	//乱数で1～60*ENMEY_INSTANCE_TIME
	instanceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME))+1;
}

void EnemyUpdate(){

	//敵生成終了
	int instanceGoalNum = MAX_ENEMY_NUM - 1;
	if (instanceCount >= instanceGoalNum && enemiesKillCount >= instanceGoalNum)
	{
		//ボスの生成
		//（上にする前の仮）とりあえずシーンを切り替える
		ChangeScene(Scene::title);
	}
	//敵が生成されるか試すために書いたコード デバッグ用
	{
		////敵の生成
		//{
		//	//float x= 100.f + GetRand(SCREEN_WIDTH - 100);
		//	//EnemyCreate(x,0,0,1,GetRand(1));
		//	EnemyMovePattarn(EnemyMovePatternState::left);
		//}

		//敵の生成
		//if (enemiesKillCount <= instanceGoalNum)
		//if (frameCounter% instanceTime == 0) {
		//	bool instanceSuccess = false;
		//	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		//		Enemy enemy = enemies[i];
		//		if (enemy.isActive)
		//			continue;
		//
		//		enemies[i].m_position.x= 100.f+GetRand(SCREEN_WIDTH-100);
		//		enemies[i].m_position.y=0;
		//		enemies[i].m_moveVector = Position{0,1};
		//		enemies[i].isActive = true;
		//		instanceSuccess = true;
		//		break;
		//	}
		//
		//	if(instanceSuccess)
		//		++instanceCount;
		//
		//	instanceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME))+1;
		//}
	}

	//敵移動
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];//値を変えないなら変数名を短くしたかった
		
		//現在 画面に居ないなら
		if (!enemy.isActive) 
		{
			//次のループへ
			continue;
		}
		//いるなら
		//移動方向へ移動
		enemies[i].m_position.x += enemies[i].m_moveVector.x;
		enemies[i].m_position.y += enemies[i].m_moveVector.y;
	}

	//敵が見えなくなったら
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];//値を変えないなら変数名を短くしたかった
		
		//現在 画面に居ないなら
		if (!enemy.isActive)
		{
			//次のループへ
			continue;
		}

		bool top	= enemy.m_position.y >= 0-ENEMY_RADIUS;//上端よりも下にいる
		bool bottom	= enemy.m_position.y <= SCREEN_HEIGHT+ ENEMY_RADIUS;//下端よりも上にいる

		bool left  = enemy.m_position.x <= SCREEN_WIDTH+ ENEMY_RADIUS;//右端よりも左にいる
		bool right = enemy.m_position.x >= 0- ENEMY_RADIUS;//左端よりも右にいる

		//画面内にいるなら
		if (left && right && top && bottom)
		{
			//次のループへ
			continue;
		}

		//画面外に出た敵を消す
		enemies[i].isActive = false;
	}

	//カウンタ
	++frameCounter;
}

void EnemyDraw(){
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];//値を変えないなら変数名を短くしたかった
		
		//現在 画面に居ないなら
		if (!enemy.isActive)
		{
			//次のループへ
			continue;
		}

		//色の選別
		if (enemy.color)
		{
			//カラフル
			TargetGraphicDrawColor(enemy.m_position.x, enemy.m_position.y, ENEMY_RADIUS);
		}
		else
		{
			//モノクロ
			TargetGraphicDrawMono(enemy.m_position.x, enemy.m_position.y, ENEMY_RADIUS);
		}
		//デバッグ用
	//	DrawCircleAA(enemy.m_position.x,enemy.m_position.y,5.f,22,0xffff0f);
	}

}

void EnemyDelete(){
	//消すものなし
}

bool EnemyToBulletCollision(float a_x, float a_y, float a_radius){
	Circle bullet = Circle{ Position{a_x,a_y},a_radius };//弾の円 コライダー
	bool anser = false;//結果 当たったか否か

	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];//値を変えないなら変数名を短くしたかった

		//現在 画面に居ないなら
		if (!enemy.isActive)
		{
			//次のループへ
			continue;
		}

		Circle enemyCiecle = Circle{ enemy.m_position,5 };//敵の円 コライダー
		anser = CircleCollision(bullet, enemyCiecle);//当たり判定 結果代入
		
		//当たっていなかったら
		if (!anser)
		{
			//次のループへ
			continue;
		}
		
		//敵を消す
		enemies[i].isActive = false;
		//カウンタ
		++enemiesKillCount;
		//撃破エフェクト 描画
		EffectOn(enemy.m_position.x,enemy.m_position.y,20);
		
		//ループ終了
		break;
	}

	//結果の返却
	return anser;
}

void EnemyCreate(float x, float y, float mx, float my,bool color){
	int instanceGoalNum = MAX_ENEMY_NUM - 1;//目標生成数

	//敵の生成

	//クールタイム用カウンタと クールタイム秒数で余り算の結果、０以外なら
	if ((frameCounter % instanceTime) != 0)
	{
		//早期リターン
		return;
	}

	bool instanceSuccess = false;//生成結果
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];//値を変えないなら変数名を短くしたかった
		//生成されていたら
		if (enemy.isActive)
		{
			//次のループへ
			continue;
		}

		enemies[i].m_position = Position{x,y};
		enemies[i].m_moveVector = Position{ mx,my};
		enemies[i].isActive = true;
		enemies[i].color = color;
		//結果代入
		instanceSuccess = true;

		//ループ終了
		break;
	}
	//生成していたら
	if (instanceSuccess)
	{
		//生成数を増やす
		++instanceCount;
	}
	//次の生成時間を設定 1～60 * ENMEY_INSTANCE_TIME
	instanceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME)) + 1;

}
//引数を減らすためにラッピング
void EnemyCreate(Position pos,Position vec ,bool color) {
	EnemyCreate(pos.x,pos.y,vec.x,vec.y,color);
}

int GetKillNum(){
	return enemiesKillCount;
}

int GetInstanceNum(){
	return instanceCount;
}

void ResetInstanceNum(){
	//値を戻す
	instanceCount = 0;
}

int GetActiveEnemy(){
	int count = 0;//数える用

	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		//画面にないなら
		if (!enemies[i].isActive)
		{
			//次のループへ
			continue;
		}

		//数える
		++count;
	}

	return count;
}

void EnemyMovePattarn(EnemyMovePatternState pattarn) {
	Position pos = Position{0,0};//座標
	Position move = Position{ 0,0 };//移動ベクトル
	bool col = false;//色 カラフルかモノクロか

	switch (pattarn)
	{
		//左から生成
		case EnemyMovePatternState::left:
			pos.x = -ENEMY_RADIUS;
			pos.y = ENEMY_RADIUS + GetRand(SCREEN_HEIGHT - (int)ENEMY_RADIUS);
			move = Position{1,0};
			col = false;

			break;
		//右から生成
		case EnemyMovePatternState::right:
			pos.x = SCREEN_WIDTH +ENEMY_RADIUS;
			pos.y = ENEMY_RADIUS + GetRand(SCREEN_HEIGHT - (int)ENEMY_RADIUS);
			move = Position{-1,0};
			col = true;

			break;
		//上から生成
		case EnemyMovePatternState::top:
			pos.x = 100.f + GetRand(SCREEN_WIDTH - 100);
			pos.y = -ENEMY_RADIUS;
			move = Position{0,1};
			col = GetRand(1);
			break;
		default:
			//異常な数値になったらお知らせ
			assert(false);
			break;
	}

	//結果で弾生成
	EnemyCreate(pos, move, col);
}

void EnemiesAllActive(bool _active) {
	// 敵 全てのactiveをつかさどる
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		enemies[i].isActive = _active;
	}

}