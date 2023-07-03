#pragma once

enum Scene {
	start = 0
	,title
	,mainGame
	,result//現在はクリア画面になっている。。。
	,staff//使わなかった
	,max//最大数
};

void Init_SceneManager();
void Updata_SceneManager();
void Draw_SceneManager();
void Delete_SceneManager();

/// <summary>
///		シーン変更
///		<para> </para>
/// </summary>
/// <param name="scene">指定のシーン</param>
/// <returns></returns>
bool ChangeScene(Scene scene);