#pragma once
#include "common.h"

void EnemiesInit();
void EnemiesUpdate();
void EnemiesDraw();
void EnemiesRelease();

// “G‚ÆÎ‚Ì“–‚½‚è”»’è‚ğ‚·‚é
// “G‚Ì‰~‚ğó‚¯æ‚èA“–‚½‚Á‚Ä‚¢‚ê‚Î“G‚ğ€–S‚³‚¹‚é
// “–‚½‚Á‚Ä‚¢‚ê‚Îtrue‚ğ•Ô‚·
bool EnemyCollideStone(CIRCLE stone);