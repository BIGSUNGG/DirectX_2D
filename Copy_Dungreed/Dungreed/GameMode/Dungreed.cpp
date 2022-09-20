#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	_modeType = DUNGREED;

	CAMERA->GetFreeMode() = false;

	MAP_MANAGER->MakeRandomMap(1, 0);

	Init();

	_cursur = OBJ_MANAGER->GetCursur(2);
	CursurOff();
}

void Dungreed::Update()
{
	_gameRunTime += DELTA_TIME;

	_cursur->GetTransform()->GetPos() = MOUSE_WORLD_POS;
	_cursur->Update();

	GAME->Update();
	MAP_MANAGER->Update();
}

void Dungreed::PreRender()
{
	GAME->PreRender();
}

void Dungreed::Render()
{
	GAME->Render();
}

void Dungreed::PostRender()
{
	GAME->PostRender();

	_cursur->Render();
}

void Dungreed::ImGuiRender()
{
	if (ImGui::CollapsingHeader("Dungreed"))
	{
		ImGui::Text("Run Time : %f", _gameRunTime);
	}

	if (ImGui::CollapsingHeader("Player"))
	{
		if(ImGui::Button("MELEE"))
			_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));

		ImGui::SameLine();

		if(ImGui::Button("GUN"))
			_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));

		ImGui::Text("Pos : %0.1f , %0.1f", _player->GetTexture()->GetTransform()->GetPos().x, _player->GetTexture()->GetTransform()->GetPos().y);
		ImGui::Text("Velocity : %0.1f , %0.1f", _player->GetVelocity().x, _player->GetVelocity().y);
	}

	GAME->ImguiRender();
}

void Dungreed::Init()
{
	_player = dynamic_pointer_cast<Player>(MAKE_PLAYER(0));
	_player->GetTexture()->GetTransform()->GetPos().x = MAP_MANAGER->GetCurMap()->GetStartPos().x;
	_player->GetTexture()->SetBottom(MAP_MANAGER->GetCurMap()->GetStartPos().y);
	_player->SetSpawnPos(_player->GetTexture()->GetTransform()->GetPos());
	_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));
	_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));

	GAME->AddPlayer(_player);
	GAME->GetObjectUpdate() = true;

	CAMERA->SetTarget(_player->GetTexture()->GetTransform());
	CAMERA->SetLeftBottom(MAP_MANAGER->GetCurMap()->GetLeftBottom());
	CAMERA->SetRightTop(MAP_MANAGER->GetCurMap()->GetRightTop());
	CAMERA->Update();
}
