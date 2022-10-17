#include "framework.h"
#include "LockDoorTop.h"

LockDoorTop::LockDoorTop()
	: LockDoor()
{
	_moveDirection = { 0,1 };

	SetAnimation();
	GetAnimation()->_animSpeed[LockDoor::LOCK] = vector<float>(8, 0.1f);
	GetAnimation()->_animState[LockDoor::LOCK] = Animation::Anim_State::END;
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele00.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele01.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele02.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele03.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele04.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele05.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele06.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Lock/Stele07.png");

	GetAnimation()->_animSpeed[LockDoor::IDLE] = vector<float>(8, 0.05f);
	GetAnimation()->_animState[LockDoor::IDLE] = Animation::Anim_State::LOOP;
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele08.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele09.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele10.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele11.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele12.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele13.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele14.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Idle/Stele15.png");

	GetAnimation()->_animSpeed[LockDoor::OPEN] = vector<float>(8, 0.1f);
	GetAnimation()->_animState[LockDoor::OPEN] = Animation::Anim_State::END;
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Open/Stele16.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Open/Stele17.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Open/Stele18.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Open/Stele19.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Open/Stele20.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Open/Stele21.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorTop/Open/Stele22.png");

	auto texture = make_shared<Quad>(GetAnimation()->_animList[LockDoor::LOCK][0]);
	SetTexture(texture);

	GetAnimation()->SetTexture(texture);
}

void LockDoorTop::DoorOpenEffect()
{
	auto trail = make_shared<Effect_Trail>();
	auto quad = make_shared<Quad>(L"Resource/Effect/LockDoor/DoorEffect.png");
	trail->SetTexture(quad);
	trail->GetPos().x = MathUtility::RandomFloat(MAP_MANAGER->GetCurMap()->GetTopDoor().x - _texture->GetHalfSize().x, MAP_MANAGER->GetCurMap()->GetTopDoor().x + _texture->GetHalfSize().x);
	trail->GetPos().y = MathUtility::RandomFloat(MAP_MANAGER->GetCurMap()->GetTopDoor().y - (_texture->GetHalfSize().y * 0.7), MAP_MANAGER->GetCurMap()->GetTopDoor().y + (_texture->GetHalfSize().y * 0.7));
	trail->SetAlpha(MathUtility::RandomFloat(0.3f, 0.7f));
	trail->GetObjectTexture()->GetTransform()->GetScale() *= MathUtility::RandomFloat(0.5f, 1.0f);
	trail->SetFadeRatio(0.7f);
	trail->SetDirection({ 0,-1 });
	trail->SetSpeed(100.0f);
	GAME->AddEffect(trail);
}