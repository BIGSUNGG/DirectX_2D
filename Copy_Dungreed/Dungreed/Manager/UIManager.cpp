#include "framework.h"
#include "UIManager.h"

UIManager* UIManager::_instance = nullptr;

void UIManager::Update()
{
	_cursur->GetTransform()->GetPos() = MOUSE_POS;
	_cursur->Update();

	switch (_state)
	{
	case UIManager::UI_State::NOMAL:
		_hpBar->Update();
		_weaponSlot->Update();
		_info->Update();
		_miniMap->Update();
		break;
	case UIManager::UI_State::SHOP:
		break;
	case UIManager::UI_State::RESTAURANT:
		break;
	default:
		break;
	}
}

void UIManager::PreRender()
{
	_miniMap->PreRender();
}

void UIManager::PostRender()
{
	Camera::GetInstance()->SetUiCameraBuffer();

	switch (_state)
	{
	case UIManager::UI_State::NOMAL:
		_hpBar->Render();
		_weaponSlot->Render();
		_info->Render();
		_miniMap->Render();
		break;
	case UIManager::UI_State::SHOP:
		break;
	case UIManager::UI_State::RESTAURANT:
		break;
	default:
		break;
	}
	_cursur->Render();
}

void UIManager::ChangedMap()
{
	_miniMap->Refresh();
}

UIManager::UIManager()
{
	_cursur = OBJ_MANAGER->GetCursur(2);

	_hpBar = make_shared<UI_HpBar>();
	_weaponSlot = make_shared<UI_WeaponSlot>();
	_info = make_shared<UI_Info>();
	_miniMap = make_shared<UI_MiniMap>();
}

UIManager::~UIManager()
{
}