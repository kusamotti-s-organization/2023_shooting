#pragma once

enum Scene {
	start = 0
	,title
	,mainGame
	,result
	,staff
	,max
};

void Init_SceneManager();
void Updata_SceneManager();
void Draw_SceneManager();
void Delete_SceneManager();

/// <summary>
///		�V�[���ύX
///		<para> </para>
/// </summary>
/// <param name="scene">�w��̃V�[��</param>
/// <returns></returns>
bool ChangeScene(Scene scene);