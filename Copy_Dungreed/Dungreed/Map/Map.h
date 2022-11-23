#pragma once
class Map : public enable_shared_from_this<Map>
{
public:
	enum Level
	{
		LEVEL_00,
		LEVEL_01,
		LEVEL_02,
		LEVEL_03,
		LEVEL_04,
		LEVEL_05,
		LEVEL_06,
		LEVEL_07,
		PUBLIC,
	};

public:
	Map(int level, int num);

	bool CheckCleared();

	void AddObject(shared_ptr<Object> addObject, int type);
	bool DeleteObject(shared_ptr<Object> deleteObject, int type);
	void Paste(shared_ptr<Map> copyMap);
	void Reset();

	void OpenEvent();
	void LockEvent();
	void AddOpenEvent(const function<void()>& func) { _openEvent.emplace_back(func); }
	void AddLockEvent(const function<void()>& func) { _lockEvent.emplace_back(func); }

	vector<vector<shared_ptr<Object>>>& GetObjects() { return _objects; }

	Vector2& GetStartPos() { return _startPos; }
	Vector2& GetLeftBottom() { return _leftBottom; }
	Vector2& GetRightTop() { return _rightTop; }

	bool CanGoTop() { return (_topDoor != Vector2(0, 0)); }
	bool CanGoBottom() { return (_bottomDoor != Vector2(0, 0)); }
	bool CanGoLeft() { return (_leftDoor != Vector2(0, 0)); }
	bool CanGoRight() { return (_rightDoor != Vector2(0, 0)); }

	Vector2& GetTopDoor() { return _topDoor; }
	Vector2& GetBottomDoor() { return _bottomDoor; }
	Vector2& GetLeftDoor() { return _leftDoor; }
	Vector2& GetRightDoor() { return _rightDoor; }

	const bool& GetCleared() { return _cleared; }
	const int& GetLevel() { return _level; }
	const int& GetNum() { return _num; }
	const int& GetObjectCount() { return _objectCount; }

private:
	vector<vector<shared_ptr<Object>>> _objects;
	int _objectCount = 0;

	vector<function<void()>> _openEvent;
	vector<function<void()>> _lockEvent;

	Vector2 _startPos = { 5000,5000 };
	Vector2 _leftBottom = { 0,0 };
	Vector2 _rightTop = { 0,0 };

	Vector2 _topDoor = { 0,0 };
	Vector2 _bottomDoor = { 0,0 };
	Vector2 _leftDoor = { 0,0 };
	Vector2 _rightDoor = { 0,0 };

	int _level;
	int _num;

	bool _cleared = false;
};