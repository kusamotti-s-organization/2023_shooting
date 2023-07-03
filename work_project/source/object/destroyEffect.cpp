#include"destroyEffect.h"

#include<DxLib.h>
#include<cmath>
#include"../common.h"

namespace {
	constexpr int MAX_EFFECT_NUM = 100 + 1;//エフェクトの最大数

	//enumで区切ろうとしたけど、結局使わなかった
	//enum STATE {
	//	instance=0
	//
	//	,max
	//};

	struct EffectParam {
		float radiusChange;//半径の動的な大きさ
		int counter;//カウンタ cosに使った
		Circle circle;//円 座標
		bool active;//生成されているか

	};
	EffectParam effects[MAX_EFFECT_NUM];//エフェクトのインスタンス

}

void DestroyEffectInit() {
	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		effects[i].circle = Circle{ 0,0,0 };
		effects[i].active = false;
		effects[i].counter = 0;
		effects[i].radiusChange = 0;
	}
}

void DestroyEffectUpdate() {
	//デバッグ用を書いていた

	//デバッグ用
	/*for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		if ( !effects[i].active)
			continue;

			++effects[i].counter;
	}*/

	//test//デバッグ用
#ifdef _DEBUG
	//Debug Buildの時のみ処理する

	//左シフトとスペースキーを同時押し
	if (CheckHitKey(KEY_INPUT_SPACE) && CheckHitKey(KEY_INPUT_LSHIFT)) 
	{
		//エフェクト生成
		EffectOn(450, 450, 20);
	}
#endif
	//test--//デバッグ用

}

//デバッグ用のプロトタイプ宣言
//void FourCircleDraw1(float x, float y, float r);
//void FourCircleDraw2(float x, float y, float r);
//void StarCricleDraw(float x, float y, float r);
void DestroyEffectMob();

void DestroyEffectDraw() {
	//これは意味ない関数分けしたかも
	DestroyEffectMob();

	////test//デバッグ用
	//StarCricleDraw(200,200,20);
	//FourCircleDraw2(200,200,20);
	//FourCircleDraw1(200,200,20);
	//
	////FourCircleDraw1(300,300,20);
	////FourCircleDraw2(400,400,20);
	////StarCricleDraw(500,500,20);
	//
	//DestroyEffectMob(450,450,20);
	////test--
}

void DestroyEffectDelete() {
}

void CreateEffect(float x, float y, float r);
void EffectOn(float x, float y, float r) {
	//ヘッダーに書くために関数名を短く分かりやすくしたつもり。。。

	CreateEffect(x, y, r);

	//デバッグ用
	//active = true;
	//counter = 0;
	//radiusChange = 0;
	//position = {x,y,r};
}

//クローバーみたいな円の描画
void FourCircleDraw1(float x, float y, float r) {
	//0xffffff 白
	float harfHarfRadius = r / 2.f / 2.f;
	DrawCircleAA(x - harfHarfRadius, y, harfHarfRadius, 22, 0xffffff);
	DrawCircleAA(x + harfHarfRadius, y, harfHarfRadius, 22, 0xffffff);
	DrawCircleAA(x, y - harfHarfRadius, harfHarfRadius, 22, 0xffffff);
	DrawCircleAA(x, y + harfHarfRadius, harfHarfRadius, 22, 0xffffff);
}
//クローバーみたいな円の描画
void FourCircleDraw1(Circle circle) {
//引数を減らすためにラッピング
	FourCircleDraw1(circle.m_position.x,circle.m_position.y, circle.radius);
}
//クローバーみたいな円の描画もう少し大きく
void FourCircleDraw2(float x, float y, float r) {
	//0xdd5555 オレンジ
	float harfRadius = r / 2;
	DrawCircleAA(x - harfRadius, y, harfRadius, 22, 0xdd5555);
	DrawCircleAA(x + harfRadius, y, harfRadius, 22, 0xdd5555);
	DrawCircleAA(x, y - harfRadius, harfRadius, 22, 0xdd5555);
	DrawCircleAA(x, y + harfRadius, harfRadius, 22, 0xdd5555);
}
//クローバーみたいな円の描画もう少し大きく
void FourCircleDraw2(Circle circle) {
	//引数を減らすためにラッピング
	FourCircleDraw2(circle.m_position.x, circle.m_position.y, circle.radius);
}

//十字架星みたいな円の描画
void StarCricleDraw(float x, float y, float r) {
	//0xff0000 真っ赤
	DrawOvalAA(x, y, r / 2, r * 2, 22, 0xff0000, TRUE);
	DrawOvalAA(x, y, r * 2, r / 2, 22, 0xff0000, TRUE);
}
//十字架星みたいな円の描画
void StarCricleDraw(Circle circle) {
//引数を減らすためにラッピング
	StarCricleDraw(circle.m_position.x, circle.m_position.y, circle.radius);
}

//Draw用エフェクトの描画
void DestroyEffectMob() {
	//高エネルギーなほど白くする。
	//だんだん赤く
	//最後は赤　半透明で小さく
	//円をかぶせて小さくする
	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		//生成されていないなら
		if (!effects[i].active)
		{
			//次のループへ
			continue;
		}

		EffectParam eff = effects[i];//値を変えないなら変数名を短くしたかった

		//カウンタ
		++effects[i].counter;


		if (effects[i].counter < 5)//カウンタ ５f以内
		{
			//最初は小さいクローバーみたいな円の描画
			FourCircleDraw1(eff.circle);
		}
		else if (effects[i].counter < 10)//カウンタ 10f以内
		{
			//半透明をかけながら
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
			//次は小さいクローバーみたいな円の描画少し大きい
			FourCircleDraw2(eff.circle);
		}
		else if (effects[i].counter < 20)//カウンタ 20f以内
		{
			//半透明をかけながら
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
			//十字架星みたいな円の描画
			StarCricleDraw(eff.circle);
		}
		else if (effects[i].radiusChange < 90) //カウンタ 20f以内 半径変更 90以内
		{
			//カウンタ
			++effects[i].radiusChange;
			//半透明をかけながら
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
			//大きさの変わる円の描画 白0xffffff
			DrawCircleAA(eff.circle.m_position.x, eff.circle.m_position.y, eff.circle.radius * 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);

			//半透明をかけながら
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
			//十字架星みたいな円の描画
			StarCricleDraw(eff.circle);
		}
		else if (effects[i].radiusChange < 180 - 1)//カウンタ 20f以内 半径変更 180以内
		{
			//カウンタ
			effects[i].radiusChange += (180 - effects[i].radiusChange) / 15;
			//半透明をかけながら
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
			//大きさの変わる円の描画 白0xffffff
			DrawCircleAA(eff.circle.m_position.x, eff.circle.m_position.y, eff.circle.radius * 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);
		}
		else //上記それ以外
		{
			effects[i].counter = 0;
			effects[i].radiusChange = 0;
			effects[i].active = false;
		}

		//半透明を戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}
//使わなかったのでデバッグ用です
//void DestroyEffectMob(float x, float y, float r) {
//	//高エネルギーなほど白くする。
//	//だんだん赤く
//	//最後は赤　半透明で小さく
//	//円をかぶせて小さくする
//	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
//		if (!effects[i].active)
//			continue;
//
//		++effects[i].counter;
//
//		if (effects[i].counter < 5)
//		{
//			FourCircleDraw1(x, y, r);
//		}
//		else if (effects[i].counter < 10)
//		{
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
//			FourCircleDraw2(x, y, r);
//		}
//		else if (effects[i].counter < 20)
//		{
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
//			StarCricleDraw(x, y, r);
//		}
//		else if (effects[i].radiusChange < 90) {
//			++effects[i].radiusChange;
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
//			DrawCircleAA(x, y, r * 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);
//
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
//			StarCricleDraw(x, y, r);
//		}
//		else if (effects[i].radiusChange < 180 - 1)
//		{
//			effects[i].radiusChange += (180 - effects[i].radiusChange) / 15;
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
//			DrawCircleAA(x, y, r * 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);
//		}
//		else {
//			effects[i].counter = 0;
//			effects[i].radiusChange = 0;
//			effects[i].active = false;
//		}
//	}
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//}
//void DestroyEffectMob(Circle _pos) {
//	DestroyEffectMob(_pos.m_position.x, _pos.m_position.y, _pos.radius);
//}
//void DestroyEffectMob(EffectParam _effect) {
//	DestroyEffectMob(_effect.circle);
//}

//エフェクトを1つづつの生成
void CreateEffect(float x, float y, float r) {

	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		//エフェクトが生成されていたら
		if (effects[i].active) {
			//次のループへ
			continue;
		}

		effects[i].active = true;
		effects[i].circle = Circle{ x,y,r };
		effects[i].counter = 0;
		effects[i].radiusChange = 0;

		//ループ終了
		break;
	}
}