#pragma once

/// <summary>
/// App�܂ł�C�ŏ�����Ă��܂�
/// main���[�v�̏�������́A���L�̂S�֐����Ăяo�����̂ŁA
/// ���̐�̗���͂����ŏ����Ă�������
/// </summary>

void AppInit();

void AppUpdate();

void AppDraw();

void AppRelease();

enum SCENE_ID {
	TITLE_SCENE,
	PLAY_SCENE,
};
void ChangeScene(SCENE_ID scene);