#pragma once
class Dungreed : public GameMode
{
public:

	// GameMode��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ImGuiRender() override;
};
