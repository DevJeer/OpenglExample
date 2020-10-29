#pragma once
#include "ggl.h"

void Init();
void Draw();

// 键盘按下的事件
void OnKeyDown(char code);
// 键盘抬起的事件
void OnKeyUp(char code);