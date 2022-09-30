#pragma once
class BackGround : public Object
{
public:
	enum BackGround_Type
	{
		STATIC,
		FOLLOW_CAMERA,
		FOLLOW_PLAYER,
	};

public:
	BackGround(int level,int num);

	virtual void Update() override;

	virtual BackGround_Type& GetBackGroundType() { return _backGroundType; }
	float& GetRatio() { return _perspectiveRatio; }

protected:
	BackGround_Type _backGroundType = STATIC;

	float _perspectiveRatio = 1.5f;
};

