#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/GL.h>
#include <gl/GLU.h>

#define W_WIDTH 1000
#define W_HEIGHT 800

extern HWND hWnd;      // 主窗口句柄
extern HDC  hDC;       // OpenGL渲染环境

void InitOpenGL();
void DestroyOpenGL();

bool InitScene();
void DrawScene();

void KeyHandle(WPARAM wParam, LPARAM lParam);
void Reshape();
