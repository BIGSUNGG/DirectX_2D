#pragma once

class ObjectManager;

class Weapon : public Item
{
public:
	enum Weapon_Type
	{
		MELEE,
		GUN,
		SUB,
	};

public:
	Weapon(int level, int num);

	virtual void Update();

	virtual void Attack() override;
	virtual void Skill() override;
	virtual void Damaged(const Creature_Status& status) override;

	virtual void SetAttackEffect(function<shared_ptr<Effect>()> effect) { _attackEffect = effect; }

	void AddOffsetIndex(const int& num);

	virtual void SetWeapon();
	void SetOffset(Vector2 offset) { _offset = offset; }
	void SetShowTo(const float& showDirection) { _showDirection = showDirection; }

	void SetAttackDelay(float delay);
	void SetAttackRange(Vector2 range) { _attackRange = range; }
	void SetGiveDamageDelay(float delay) { _giveDamageDelay = delay; }
	void SetAppendAngle(vector<float> angle) { _appendAngle = angle; }
	virtual void SetAttackSound(const string& sound) { _attackSound = sound; }

	void SetSkill(function<void()> skill, const wstring& image);
	void SetSkillDelay(const float& delay);
	virtual void SetOwner(shared_ptr<Creature> owner) override;

	float GetSkillCoolTimeRatio();
	virtual const Vector2& GetOffset() { return _offset; }
	const Weapon_Type& GetWeaponType() { return _weaponType; }
	shared_ptr<Transform> GetSpringArm() { return _springArm; }
	virtual const float& GetShowDirection() { return _showDirection; }
	shared_ptr<Quad> GetSkillHuiTexture() { return _skillHudTexture; }
	virtual const bool& GetFastRender() { return _fastRender[_offsetIndex]; }
protected:
	virtual void AttackEffect();
	virtual void CheckAttack();

protected:
	Weapon_Type _weaponType = MELEE;
	shared_ptr<Quad> _skillHudTexture;
	function<void()> _skill;
	float _skillDelay = 3.f;
	float _skillRuntime = 3.f;

	float _weaponLength = 0.0f;
	bool _reversed = false;
	shared_ptr<Transform> _springArm;
	shared_ptr<Transform> _attackOfsset;
	shared_ptr<Transform> _ownerFollower;

	vector<bool> _fastRender = { false,true };

	float _attackDelay = 0.3f;
	float _attackDelayTime = 0.3f;
	string _attackSound;

	vector<float> _appendAngle = { 0.0f };
	Vector2 _attackRange = { 0,0 };
	Vector2 _offset;
	int _offsetIndex = 0;
	float _showDirection = 0.f;

	bool _attacked = false;
	float _giveDamageDelay = 0.0f;
	float _giveDamageDelayRunTime = 0.0f;

	function<shared_ptr<Effect>()> _attackEffect;
};

