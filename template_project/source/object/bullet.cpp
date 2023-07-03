#include "bullet.h"

#include<DxLib.h>
#include"../common.h"
#include"enemy.h"
#include"graphic.h"

namespace {
	constexpr float BULLET_SPEED = 8.f;//弾速
	struct Bullet {
		Position m_position;//座標
		float radius;//半径
		bool isActive;//画面内にいるか否か
	};
	constexpr int MAX_BULLET_NUM = 300 + 1;//弾の最大数
	Bullet bullets[MAX_BULLET_NUM];//弾のインスタンス
	constexpr float BULLETS_RADIUS= 30.f;//弾の半径
}

void BulletInit(){
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		bullets[i].m_position = Position{0,0};
		bullets[i].radius= BULLETS_RADIUS;
		bullets[i].isActive = false;
	}
}

void BulletUpdate(){

	//(仮)弾 移動
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];//値を変えないなら変数名を短くしたかった
		//弾が画面内にないなら
		if (!bullet.isActive)
		{
			//次のループへ
			continue;
		}

		//移動処理
		bullets[i].m_position.y += -BULLET_SPEED;
	}

	//画面外の弾を消す
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];//値を変えないなら変数名を短くしたかった
		if (!bullet.isActive) 
		{
			//次のループへ
			continue;
		}

		//弾が上端に行ったら
		if (bullet.m_position.y > 0)
		{
			//次のループへ
			continue;
		}

		bullets[i].isActive = false;
		bullets[i].m_position = Position{0,0};
	}

	//Enemyと当たったかどうか
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];//値を変えないなら変数名を短くしたかった
		//弾が生成されていないなら
		if (!bullet.isActive)
		{
			//次のループへ
			continue;
		}

		bool isCollision= EnemyToBulletCollision(bullet.m_position.x,bullet.m_position.y,bullet.radius/2);//当たっているか
		//当たっていなかったら
		if (!isCollision)
		{
			//次のループへ
			continue;
		}

		//当たったら消す
		bullets[i].isActive = false;
	}
}

void BulletDraw(){
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];//値を変えないなら変数名を短くしたかったs
		if (!bullet.isActive)
		{
			//次のループへ
			continue;
		}
	
		//デバッグ用
		//DrawCircleAA(bullet.m_position.x,bullet.m_position.y, bullet.radius,22,0xff0fff);

		//矢の描画
		ArrowGraphicDrawUp(bullet.m_position.x, bullet.m_position.y, bullet.radius);
	}
}

void BulletDelete(){
	//消すものなし
}

//弾生成　１つのみ
void BulletCreate(float x, float y){
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];//値を変えないなら変数名を短くしたかったs
		if (bullet.isActive)
		{
			//次のループへ
			continue;
		}

		bullets[i].m_position = Position{x,y};
		bullets[i].isActive = true;

		//ループ終了
		break;
	}
}

