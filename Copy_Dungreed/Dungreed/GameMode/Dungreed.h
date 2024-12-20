#pragma once
class Dungreed : public GameMode
{
public:
	Dungreed();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

	void Init();

private:
	shared_ptr<Player> _player;
	float _gameRunTime = 0.0f;
};

