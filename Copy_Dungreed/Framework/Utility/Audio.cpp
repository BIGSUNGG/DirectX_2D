#include "framework.h"
#include "Audio.h"

Audio * Audio::_instance = nullptr;

using namespace FMOD;

Audio::Audio()
{
	System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);

	Load();
}

Audio::~Audio()
{
	for (auto& soundPair : _soundMap)
		delete soundPair.second;

	_soundSystem->release();
}

void Audio::Update()
{
	_soundSystem->update();
}

void Audio::Save()
{
	{
		BinaryWriter basicWriter(L"Save/Audio_Setting/AudioVolum.bin");

		vector<float> basicInfo;

		basicInfo.push_back(_audioVolume);
		basicInfo.push_back(_bgmVolume);
		basicInfo.push_back(_sfxVolume);

		basicWriter.Uint(basicInfo.size());
		basicWriter.Byte(basicInfo.data(), basicInfo.size() * sizeof(float));
	}
}

void Audio::Load()
{
	{
		BinaryReader Reader(L"Save/Audio_Setting/AudioVolum.bin");

		UINT size = Reader.Uint();

		vector<float> graphicInfo;
		graphicInfo.resize(3);
		void* ptr = graphicInfo.data();
		Reader.Byte(&ptr, size * sizeof(float));

		_audioVolume = graphicInfo[0];
		_bgmVolume = graphicInfo[1];
		_sfxVolume = graphicInfo[2];

		SetVolumeAll();
	}
}

void Audio::Add(string key, string file, bool loop, bool bgm)
{
	if (_soundMap.count(key) > 0)
		return;

	SoundInfo* info = new SoundInfo();

	if (loop)
		_soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, IN & info->_sound);
	else
		_soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, IN & info->_sound);

	if (bgm)
		_type[key] = true;
	else
		_type[key] = false;

	assert(info->_sound != nullptr);

	_soundMap[key] = info;
}

void Audio::Play(string key)
{
	if (_soundMap.count(key) == 0)
	{
		if (key == "")
			return;

		assert(false);
	}

	_soundSystem->playSound(_soundMap[key]->_sound, nullptr, false, &_soundMap[key]->_channel);

	float soundvolume;

	if (_type[key] == true)
		soundvolume = _audioVolume * _bgmVolume;
	else
		soundvolume = _audioVolume * _sfxVolume;

	_soundMap[key]->_channel->setVolume(soundvolume);
}

void Audio::Stop(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->_channel->stop();
}

void Audio::StopAll()
{
	for (auto& sound : _soundMap)
		sound.second->_channel->stop();
}

void Audio::Pause(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->_channel->setPaused(true);
}

void Audio::PauseAll()
{
	for (auto& sound : _soundMap)
		sound.second->_channel->setPaused(true);
}

void Audio::Resume(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->_channel->setPaused(false);
}

void Audio::ResumeAll()
{
	for (auto& sound : _soundMap)
		sound.second->_channel->setPaused(false);
}

void Audio::SetVolume(string key, float volume)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]->_channel == nullptr)
		return;

	if (volume <= 0)
		volume = 0;

	if (volume >= 2.0f)
		volume = 2.0f;

	_soundMap[key]->_channel->setVolume(volume);
}

void Audio::SetVolumeAll()
{
	for (auto& sound : _soundMap)
	{
		if (sound.second->_channel == nullptr)
			continue;

		float soundvolume;

		if(_type[sound.first] == true)
			soundvolume = _audioVolume * _bgmVolume;
		else
			soundvolume = _audioVolume * _sfxVolume;

		sound.second->_channel->setVolume(soundvolume);
	}
}

bool Audio::IsPlaySound(string key)
{
	if (_soundMap.count(key) == 0)
		return false;

	bool isPlay = false;
	_soundMap[key]->_channel->isPlaying(IN & isPlay);

	return isPlay;
}

void Audio::ImGuiRender()
{
	ImGui::SliderFloat("Audio Volume", &_tempAudioVolume, 0.0f, 2.0f, "%0.1f");
	ImGui::SliderFloat("BGM Volume", &_tempBgmVolume, 0.0f, 1.0f, "%0.1f");
	ImGui::SliderFloat("SFX Volume", &_tempSfxVolume, 0.0f, 1.0f, "%0.1f");

	if (ImGui::Button("Apply"))
	{
		_audioVolume = _tempAudioVolume;
		_bgmVolume = _bgmVolume;
		_sfxVolume = _tempSfxVolume;
		SOUND->SetVolumeAll();
	}

	if (ImGui::Button("Save"))
		SOUND->Save(); 
}
