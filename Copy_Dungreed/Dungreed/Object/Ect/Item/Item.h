#pragma once

class Creature;

class Item : public Ect
{
public:
	enum Item_Type
	{
		WEAPON,
		SUB_WEAPON,
		ACCESSORY,
		NONE
	};

	enum Item_State
	{
		IDLE,
		ATTACK,
		SKILL,
		DAMAGED,
	};

public:
	Item(int level, int num);
	virtual ~Item();

	virtual bool GiveDamage(shared_ptr<Creature> target);

	virtual void ReverseTexture();

	virtual void Attack() abstract;
	virtual void Skill() abstract;
	virtual void Damaged(const Creature_Status& status) abstract;

	virtual void SetOwner(shared_ptr<Creature> owner);
	void SetHudTexture(const wstring& image);

	shared_ptr<Quad> GetHudTexture() { return _hudTexture; }
	const shared_ptr<Creature> GetOwner() { return _owner.lock(); }
	const Item_Type& GetItemType() { return _itemType; }

protected:
	weak_ptr<Creature> _owner;
	shared_ptr<Quad> _hudTexture;

	Creature_Status _status;

	Item_Type _itemType = ACCESSORY;
};

