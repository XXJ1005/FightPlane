#pragma once
#include <vector>
#include <functional>
using namespace std;

class FPButton;
class FPText;
class FPIcon;

class FPGUIManager
{
public:
	enum MouseState { LBDown, LBUp, Move};

	FPGUIManager() {}

	void InitGUI();
	void RenderGUI();

	void addGameStartButton(FPButton *button) {
		m_GameStartButtons.push_back(button);
	}

	void LButtonDownHandle(WPARAM wParam, LPARAM lParam);
	void LButtonUpHandle(WPARAM wParam, LPARAM lParam);

	void UpdateButtonState(MouseState state, WPARAM wParam, LPARAM lParam);
private:
	void RenderStartGameGUI();
	void InitStartGameGUI();

	void RenderPlayGameGUI();
	void InitPlayGameGUI();

	void RenderSuccessGameGUI();
	void InitSuccessGameGUI();

	void RenderFailureGameGUI();
	void InitFailureGameGUI();

	// Start
	vector<FPButton *> m_GameStartButtons;
	// Play
	FPText *m_ScoreText;
	vector<FPIcon *>m_lifeIcons;
	// Success
	vector<FPButton *> m_GameSuccessButtons;
	FPIcon *m_gameSuccessIcon;
	// Failure
	vector<FPButton *> m_GameFailureButtons;
	FPIcon *m_gameFailureIcon;

	static FPGUIManager *m_Manager;
};

enum class ButtonType
{
	LButton,
	RButton,
	MButton
};

class FPFrame {
public:
	FPFrame() {}
	FPFrame(float x, float y, float width, float height) { m_x = x; m_y = y; m_width = width; m_height = height; }

	float m_x;
	float m_y;
	float m_width;
	float m_height;
};

extern GLuint LoadTexture(const char *fileName);

class FPButton {
public:
	enum ButtonState{ Down, Over, Normal};

	FPButton() {}
	FPButton(FPFrame *frame, const char* NormalTextureFileName, 
		const char *DownTextureFileName, const char *OverTextureFileName,
		function<void(ButtonType type)> buttonDownBlock, function<void(ButtonType type)> buttonUpBlock) {
		m_Frame = frame;

		m_texture[0] = LoadTexture(NormalTextureFileName);
		m_texture[1] = LoadTexture(DownTextureFileName);
		m_texture[2] = LoadTexture(OverTextureFileName);

		m_fButtonDownBlock = buttonDownBlock;
		m_fButtonUpBlock = buttonUpBlock;

		m_TextureArea[0][0] = 0;
		m_TextureArea[0][1] = 0;

		m_TextureArea[1][0] = frame->m_width;
		m_TextureArea[1][1] = 0;

		m_TextureArea[2][0] = frame->m_width;
		m_TextureArea[2][1] = frame->m_height;

		m_TextureArea[3][0] = 0;
		m_TextureArea[3][1] = frame->m_height;

		m_State = ButtonState::Normal;
	}

	void Render();

	void OnMouseDown(ButtonType type, int x, int y);
	void OnMouseUp(ButtonType type, int x, int y);

	void setButtonState(ButtonState state) { m_State = state; }
	ButtonState getButtonState() { return m_State; }

	FPFrame* GetFrame() { return m_Frame; }
private:
	FPFrame *m_Frame;

	GLuint m_texture[3];

	ButtonState m_State;

	float m_TextureArea[4][2];
	
	function<void(ButtonType type)> m_fButtonDownBlock;
	function<void(ButtonType type)> m_fButtonUpBlock;
};

typedef struct Color3D {
	float r, g, b;
}Color3D;

class FPText {
public:
	FPText() {}
	FPText(float x, float y, int fontSize, Color3D color) {
		m_x = x;
		m_y = y;
		m_fontSize = fontSize;
		m_color = color;
	}
	void Render(const char* text);
private:
	float m_x, m_y;
	int m_fontSize;
	Color3D m_color;
};

class FPIcon {
public:
	FPIcon() {}
	FPIcon(const char* iconFileName, FPFrame *frame) {
		m_texture = LoadTexture(iconFileName);

		m_frame = frame;

		m_TextureArea[0][0] = 0;
		m_TextureArea[0][1] = 0;

		m_TextureArea[1][0] = frame->m_width;
		m_TextureArea[1][1] = 0;

		m_TextureArea[2][0] = frame->m_width;
		m_TextureArea[2][1] = frame->m_height;

		m_TextureArea[3][0] = 0;
		m_TextureArea[3][1] = frame->m_height;
	}

	void Render();
private:
	GLuint m_texture;
	FPFrame *m_frame;
	float m_TextureArea[4][2];
};