#pragma once
#define KEY_MAX 255

class InputManager
{
private:
	enum
	{
		PLAYER,
		DOWN,
		UP,
		PRESS
	};

	InputManager();
	~InputManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InputManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static InputManager* GetInstance()
	{
		if (_instance != nullptr)
		{
			return _instance;
		}

		return nullptr;
	}

	void Update();

	bool Down(UINT key) { return _stateMap[key] == DOWN; }
	bool Up(UINT key) { return _stateMap[key] == UP; }
	bool Press(UINT key) { return _stateMap[key] == PRESS; }

	Vector2& GetMousePos() { return _mousePos; }

private:
	static InputManager* _instance;

	byte _curState[KEY_MAX];
	byte _oldState[KEY_MAX];
	byte _stateMap[KEY_MAX];

	Vector2 _mousePos = { 0.0f,0.0f };
};

