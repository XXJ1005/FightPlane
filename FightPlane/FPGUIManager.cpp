#include <windows.h>
#include "glUtility.h"
#include "FPGUIManager.h"
#include "FPGameManager.h"

void startGameBtnDownBlock(ButtonType type);
void startGameBtnUpBlock(ButtonType type);
void overGameBtnDownBlock(ButtonType type);
void overGameBtnUpBlock(ButtonType type);
void restartGameBtnDownBlock(ButtonType type);
void restartGameBtnUpBlock(ButtonType type);

void FPGUIManager::InitGUI()
{
	InitStartGameGUI();
	InitPlayGameGUI();
	InitSuccessGameGUI();
	InitFailureGameGUI();
}

// FBGUIManager
void FPGUIManager::RenderGUI() {
	// RenderStartGameGUI()
	if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Start) {
		RenderStartGameGUI();
	} else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Play) {
		RenderPlayGameGUI();
	} else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Success) {
		RenderSuccessGameGUI();
	} else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Failure) {
		RenderFailureGameGUI();
	}
}

void FPGUIManager::InitStartGameGUI() {
	// 创建开始游戏按钮
	RECT windowsRect;
	GetClientRect(GameHwnd, &windowsRect);

	FPFrame *startGameBtnFrame = new FPFrame(windowsRect.right / 2.0 - 100, windowsRect.bottom / 2.0 + 60, 200, 100);
	const char* startGameNormalTexture = "../media/icon/start_game_btn_normal.png";
	const char* startGameDownTexture = "../media/icon/start_game_btn_down.png";
	const char* startGameOverTexture = "../media/icon/start_game_btn_over.png";
	FPButton *startGameButton = new FPButton(startGameBtnFrame, startGameNormalTexture, startGameDownTexture, startGameOverTexture, startGameBtnDownBlock, startGameBtnUpBlock);
	
	m_GameStartButtons.push_back(startGameButton);

	FPFrame *overGameBtnFrame = new FPFrame(windowsRect.right / 2.0 - 100, windowsRect.bottom / 2.0 - 60, 200, 100);
	const char* overGameNormalTexture = "../media/icon/over_game_btn_normal.png";
	const char* overGameDownTexture = "../media/icon/over_game_btn_down.png";
	const char* overGameOverTexture = "../media/icon/over_game_btn_over.png";
	FPButton *overGameButton = new FPButton(overGameBtnFrame, overGameNormalTexture, overGameDownTexture, overGameOverTexture, overGameBtnDownBlock, overGameBtnUpBlock);

	m_GameStartButtons.push_back(overGameButton);
}

void FPGUIManager::RenderStartGameGUI() {
	// 按钮更新
	for (FPButton *button : m_GameStartButtons) {
		button->Render();
	}
}

void FPGUIManager::InitPlayGameGUI() {
	Color3D color;
	color.r = 255.0; color.g = 0.0; color.b = 0.0;
	m_ScoreText = new FPText(-0.1, -0.3, 64, color);

	// 最大生命值
	// 窗口大小
	int windowRect[4];
	glGetIntegerv(GL_VIEWPORT, windowRect);

	int lifeMaxCount = 5;
	for (size_t i = 1; i <= lifeMaxCount; i++) {
		FPFrame *frame = new FPFrame(windowRect[2] - 30 - 60 * i, windowRect[3] - 100, 60, 60);
		FPIcon* lifeIcon = new FPIcon("../media/icon/heart.png", frame);
		m_lifeIcons.push_back(lifeIcon);
	}
}

void FPGUIManager::RenderPlayGameGUI() {

	// 得分面板
	static int planeScore = 0;
	char buffer[1024];
	sprintf(buffer, "SCORE: %d", planeScore);
	planeScore += rand() % 3;

	if (planeScore >= 10) {
		FPGameManager::GetInstance()->SetCurrentGameState(FPGameManager::FPGameState::Success);
		return;
	}

	m_ScoreText->Render(buffer);

	// 血条
	static int lifeCount = 0;
	static int timeCount = 0;

	if (timeCount > 10) {
		lifeCount = rand() % 5;
		if (lifeCount == 0) {
			FPGameManager::GetInstance()->SetCurrentGameState(FPGameManager::FPGameState::Failure);
			return;
		}
		timeCount = 0;
	}
	else {
		timeCount++;
	}
	 
	for (size_t i = 0; i < lifeCount; i++) {
		m_lifeIcons.at(i)->Render();
	}
}

// Success
void FPGUIManager::InitSuccessGameGUI() {
	RECT windowsRect;
	GetClientRect(GameHwnd, &windowsRect);

	// 胜利图标
	FPFrame *frame = new FPFrame(windowsRect.right / 2.0 - 150, windowsRect.bottom / 2.0 + 80, 300, 200);
	m_gameSuccessIcon = new FPIcon("../media/icon/success.png" ,frame);

	// 创建重新开始游戏按钮

	FPFrame *restartGameBtnFrame = new FPFrame(windowsRect.right / 2.0 - 100, windowsRect.bottom / 2.0 - 60, 200, 100);
	const char* restartGameNormalTexture = "../media/icon/restart_game_btn_normal.png";
	const char* restartGameDownTexture = "../media/icon/restart_game_btn_down.png";
	const char* restartGameOverTexture = "../media/icon/restart_game_btn_over.png";
	FPButton *restartGameButton = new FPButton(restartGameBtnFrame, restartGameNormalTexture, restartGameDownTexture, restartGameOverTexture, restartGameBtnDownBlock, restartGameBtnUpBlock);

	m_GameSuccessButtons.push_back(restartGameButton);

	FPFrame *overGameBtnFrame = new FPFrame(windowsRect.right / 2.0 - 100, windowsRect.bottom / 2.0 - 180, 200, 100);
	const char* overGameNormalTexture = "../media/icon/over_game_btn_normal.png";
	const char* overGameDownTexture = "../media/icon/over_game_btn_down.png";
	const char* overGameOverTexture = "../media/icon/over_game_btn_over.png";
	FPButton *overGameButton = new FPButton(overGameBtnFrame, overGameNormalTexture, overGameDownTexture, overGameOverTexture, overGameBtnDownBlock, overGameBtnUpBlock);

	m_GameSuccessButtons.push_back(overGameButton);
}

void FPGUIManager::RenderSuccessGameGUI() {
	// 按钮更新
	for (FPButton *button : m_GameSuccessButtons) {
		button->Render();
	}

	// 
	m_gameSuccessIcon->Render();
}

// Failure
void FPGUIManager::InitFailureGameGUI() {
	RECT windowsRect;
	GetClientRect(GameHwnd, &windowsRect);

	// 胜利图标
	FPFrame *frame = new FPFrame(windowsRect.right / 2.0 - 150, windowsRect.bottom / 2.0 + 80, 300, 200);
	m_gameFailureIcon = new FPIcon("../media/icon/failure.png", frame);

	// 创建重新开始游戏按钮

	FPFrame *restartGameBtnFrame = new FPFrame(windowsRect.right / 2.0 - 100, windowsRect.bottom / 2.0 - 60, 200, 100);
	const char* restartGameNormalTexture = "../media/icon/restart_game_btn_normal.png";
	const char* restartGameDownTexture = "../media/icon/restart_game_btn_down.png";
	const char* restartGameOverTexture = "../media/icon/restart_game_btn_over.png";
	FPButton *restartGameButton = new FPButton(restartGameBtnFrame, restartGameNormalTexture, restartGameDownTexture, restartGameOverTexture, restartGameBtnDownBlock, restartGameBtnUpBlock);

	m_GameFailureButtons.push_back(restartGameButton);

	FPFrame *overGameBtnFrame = new FPFrame(windowsRect.right / 2.0 - 100, windowsRect.bottom / 2.0 - 180, 200, 100);
	const char* overGameNormalTexture = "../media/icon/over_game_btn_normal.png";
	const char* overGameDownTexture = "../media/icon/over_game_btn_down.png";
	const char* overGameOverTexture = "../media/icon/over_game_btn_over.png";
	FPButton *overGameButton = new FPButton(overGameBtnFrame, overGameNormalTexture, overGameDownTexture, overGameOverTexture, overGameBtnDownBlock, overGameBtnUpBlock);

	m_GameFailureButtons.push_back(overGameButton);
}

void FPGUIManager::RenderFailureGameGUI() {
	// 按钮更新
	for (FPButton *button : m_GameFailureButtons) {
		button->Render();
	}

	// 
	m_gameFailureIcon->Render();
}

void FPGUIManager::LButtonDownHandle(WPARAM wParam, LPARAM lParam) {
	int x = LOWORD(lParam); // 不能写成(LOWORD)wParam
	int y = HIWORD(lParam);
	RECT rect;
	GetClientRect(GameHwnd, &rect);

	if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Start) {
		y = rect.bottom - rect.top - y; // 坐标转化
		for (FPButton *button : m_GameStartButtons) {
			button->OnMouseDown(ButtonType::LButton, x, y);
		}
	} else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Play) {
		// 没有button
	} else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Success) {
		y = rect.bottom - rect.top - y; // 坐标转化
		for (FPButton *button : m_GameSuccessButtons) {
			button->OnMouseDown(ButtonType::LButton, x, y);
		}
	} else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Failure) {
		y = rect.bottom - rect.top - y; // 坐标转化
		for (FPButton *button : m_GameFailureButtons) {
			button->OnMouseDown(ButtonType::LButton, x, y);
		}
	}
}

void FPGUIManager::LButtonUpHandle(WPARAM wParam, LPARAM lParam) {
	int x = LOWORD(lParam); // 不能写成(LOWORD)wParam
	int y = HIWORD(lParam);
	RECT rect;
	GetClientRect(GameHwnd, &rect);

	if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Start) {
		y = rect.bottom - rect.top - y; // 坐标转化
		for (FPButton *button : m_GameStartButtons) {
			button->OnMouseUp(ButtonType::LButton, x, y);
		}
	}
	else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Play) {
		// 没有button
	}
	else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Success) {
		y = rect.bottom - rect.top - y; // 坐标转化
		for (FPButton *button : m_GameSuccessButtons) {
			button->OnMouseUp(ButtonType::LButton, x, y);
		}
	}
	else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Failure) {
		y = rect.bottom - rect.top - y; // 坐标转化
		for (FPButton *button : m_GameFailureButtons) {
			button->OnMouseUp(ButtonType::LButton, x, y);
		}
	}
}

void FPGUIManager::UpdateButtonState(MouseState mouseState, WPARAM wParam, LPARAM lParam) {

	RECT windowsRect;
	int x = LOWORD(lParam); // 不能写成(LOWORD)wParam
	int y = HIWORD(lParam);
	GetClientRect(GameHwnd, &windowsRect);
	y = windowsRect.bottom - windowsRect.top - y;

	if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Start) {
		for (FPButton *button : m_GameStartButtons) {
			if (mouseState == MouseState::LBDown) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&& y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Down);
				}
			} else if (mouseState == MouseState::LBUp) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&&  y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Over);
				} else {
					button->setButtonState(FPButton::ButtonState::Normal);
				}
			} else if (mouseState == MouseState::Move) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&&  y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Over);
				}
				else {
					button->setButtonState(FPButton::ButtonState::Normal);
				}
			}
		}
	}
	else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Play) {

	}
	else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Success) {
		for (FPButton *button : m_GameSuccessButtons) {
			if (mouseState == MouseState::LBDown) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&& y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Down);
				}
			}
			else if (mouseState == MouseState::LBUp) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&&  y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Over);
				}
				else {
					button->setButtonState(FPButton::ButtonState::Normal);
				}
			}
			else if (mouseState == MouseState::Move) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&&  y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Over);
				}
				else {
					button->setButtonState(FPButton::ButtonState::Normal);
				}
			}
		}
	}
	else if (FPGameManager::GetInstance()->GetCurrentGameState() == FPGameManager::FPGameState::Failure) {
		for (FPButton *button : m_GameFailureButtons) {
			if (mouseState == MouseState::LBDown) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&& y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Down);
				}
			}
			else if (mouseState == MouseState::LBUp) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&&  y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Over);
				}
				else {
					button->setButtonState(FPButton::ButtonState::Normal);
				}
			}
			else if (mouseState == MouseState::Move) {
				if (x <= button->GetFrame()->m_x + button->GetFrame()->m_width && x >= button->GetFrame()->m_x
					&&  y <= button->GetFrame()->m_y + button->GetFrame()->m_height && y >= button->GetFrame()->m_y) {
					button->setButtonState(FPButton::ButtonState::Over);
				}
				else {
					button->setButtonState(FPButton::ButtonState::Normal);
				}
			}
		}
	}
}

// FPButton
void FPButton::Render() {

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glViewport(m_Frame->m_x, m_Frame->m_y, m_Frame->m_width, m_Frame->m_height); //26像素是菜单栏的高度

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, m_Frame->m_width, 0, m_Frame->m_height, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	GLuint texture;
	if (getButtonState() == FPButton::Normal) {
		texture = m_texture[0];
	} else if (getButtonState() == FPButton::Down) {
		texture = m_texture[1];
	} else if (getButtonState() == FPButton::Over) {
		texture = m_texture[2];
	}

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex2fv(m_TextureArea[0]);
	glTexCoord2f(1.0, 0.0);
	glVertex2fv(m_TextureArea[1]);
	glTexCoord2f(1.0, 1.0);
	glVertex2fv(m_TextureArea[2]);
	glTexCoord2f(0.0, 1.0);
	glVertex2fv(m_TextureArea[3]);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();

	//glDeleteTextures(1, &texture);
}

void FPButton::OnMouseDown(ButtonType type, int x, int y) {
	if (x <= m_Frame->m_x + m_Frame->m_width && x >= m_Frame->m_x
		&&  y <= m_Frame->m_y + m_Frame->m_height && y >= m_Frame->m_y) {
		m_fButtonDownBlock(type);
	}
}

void FPButton::OnMouseUp(ButtonType type, int x, int y) {
	if (x <= m_Frame->m_x + m_Frame->m_width && x >= m_Frame->m_x
		&&  y <= m_Frame->m_y + m_Frame->m_height && y >= m_Frame->m_y) {
		m_fButtonUpBlock(type);
	}
}

// FPText
void FPText::Render(const char* text) {

	int windowsRect[4];
	glGetIntegerv(GL_VIEWPORT, windowsRect);
	RECT clientRect;
	GetClientRect(GameHwnd, &clientRect);

	GLuint base;
	HFONT font;
	HFONT oldfont;

	base = glGenLists(256);     // 创建96个显示列表  
	font = CreateFont(m_fontSize,      // 字体高度  
		0,      // 字体宽度  
		0,      // 字体的旋转角度  
		0,      // 字体底线的旋转角度  
		FW_BOLD,// 字体重量  
		FALSE,  // 是否使用斜体  
		FALSE,  // 是否使用下划线  
		FALSE,  // 是否使用删除线  
		ANSI_CHARSET,   // 设置字符集  
		OUT_TT_PRECIS,  // 输出精度  
		CLIP_DEFAULT_PRECIS,    // 剪裁精度  
		ANTIALIASED_QUALITY,    // 输出质量  
		FF_DONTCARE | DEFAULT_PITCH,
		"Courier New"); // 字体名称  
	oldfont = (HFONT)SelectObject(wglGetCurrentDC(), font); // 选择我们需要的字体  
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, base);     // 创建96个显示列表，绘制从ASCII码为32-128的字符  
	SelectObject(wglGetCurrentDC(), oldfont);
	DeleteObject(font);

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushAttrib(GL_LIST_BIT);  // 把显示列表属性压入属性堆栈  

	// 计字体大小对应像素值
	HDC hDC = GetDC(GameHwnd);
	int height = GetDeviceCaps(hDC, LOGPIXELSY); // 一英寸对应像素值，一英寸为72pt
	int fontPixel = height / 72.0 * m_fontSize;

	glTranslatef(m_x - 1.0, m_y + 1.0, -1.0f);
	glColor3f(m_color.r/255.0, m_color.g/255.0, m_color.b/255.0); // 颜色
	glRasterPos2f(0.0f, 0.0f); // 输出位置
	glListBase(base - 0);       // 设置显示列表的基础值  
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // 调用显示列表绘制字符串  
	glPopAttrib();              // 弹出属性堆栈  
	glPopAttrib();
}

// FPIcon
void FPIcon::Render() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glViewport(m_frame->m_x, m_frame->m_y, m_frame->m_width, m_frame->m_height); //26像素是菜单栏的高度

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, m_frame->m_width, 0, m_frame->m_height, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex2fv(m_TextureArea[0]);
	glTexCoord2f(1.0, 0.0);
	glVertex2fv(m_TextureArea[1]);
	glTexCoord2f(1.0, 1.0);
	glVertex2fv(m_TextureArea[2]);
	glTexCoord2f(0.0, 1.0);
	glVertex2fv(m_TextureArea[3]);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}

// 一些按钮回调函数
void startGameBtnDownBlock(ButtonType type) {
	if (type == ButtonType::LButton) {
	}
}

void startGameBtnUpBlock(ButtonType type) {
	if (type == ButtonType::LButton) {
		// 进入游戏
		FPGameManager::GetInstance()->SetCurrentGameState(FPGameManager::FPGameState::Play);
	}
}

void overGameBtnDownBlock(ButtonType type) {
	if (type == ButtonType::LButton) {
	}
}

void overGameBtnUpBlock(ButtonType type) {
	if (type == ButtonType::LButton) {
		// 退出游戏程序
		PostMessage(GameHwnd, WM_CLOSE, 0, 0);
	}
}

void restartGameBtnDownBlock(ButtonType type) {
	if (type == ButtonType::LButton) {
	}
}

void restartGameBtnUpBlock(ButtonType type) {
	if (type == ButtonType::LButton) {
		// 重新游戏
		FPGameManager::GetInstance()->SetCurrentGameState(FPGameManager::FPGameState::Start);
	}
}
