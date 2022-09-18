#include "framework.h"
#include "MapManager.h"

MapManager* MapManager::_instance = nullptr;

shared_ptr<Map> MapManager::Load(int level, int num)
{
	shared_ptr<Map> newMap = make_shared<Map>(level,num);
	wstring path = L"Save/Maps/Level_";
	wstring levelPath;
	{
		if (level < 10)
			levelPath += L"0";

		levelPath += to_wstring(level);
	}
	wstring numPath;
	{
		if (num < 10)
			numPath += L"0";

		numPath += to_wstring(num);
	}
	path += levelPath + L"_" + numPath;

	int objectCount;
	{
		BinaryReader basicReader(path + L"_basic" + L".txt");

		UINT size = basicReader.Uint();

		vector<int> basicInfo;
		basicInfo.resize(7);
		void* ptr = basicInfo.data();
		basicReader.Byte(&ptr, size * sizeof(int));

		objectCount = basicInfo[0];
		newMap->GetLeftBottom() = Vector2(basicInfo[1], basicInfo[2]);
		newMap->GetRightTop() = Vector2(basicInfo[3], basicInfo[4]);
		newMap->GetStartPos() = Vector2(basicInfo[5], basicInfo[6]);
	}

	{
		BinaryReader mapReader(path + L".txt");

		UINT size = mapReader.Uint();

		vector<int> mapInfo;
		int info = 6;
		int infoCount = objectCount * info;
		mapInfo.resize(infoCount);
		void* ptr = mapInfo.data();
		mapReader.Byte(&ptr, size * sizeof(int));

		for (int i = 0; i < objectCount; i++)
		{
			int cur = i * info;

			shared_ptr<Object> object = MAKE_OBJECT(mapInfo[cur], mapInfo[cur + 1], mapInfo[cur + 2]);

			object->SetSpawnPos(Vector2(mapInfo[cur + 3], mapInfo[cur + 4]));

			if (mapInfo[cur + 5] == 1)
				object->ReverseTexture();

			newMap->AddObject(object, mapInfo[cur]);
		}
	}

	return newMap;
}

void MapManager::Save(shared_ptr<Map> map)
{
	const int& level = map->GetLevel();
	const int& num = map->GetNum();

	wstring path = L"Save/Maps/Level_";
	wstring levelPath;
	{
		if (level < 10)
			levelPath += L"0";

		levelPath += to_wstring(level);
	}
	wstring numPath;
	{
		if (num < 10)
			numPath += L"0";

		numPath += to_wstring(num);
	}
	path += levelPath + L"_" + numPath;

	{
		BinaryWriter basicWriter(path + L"_basic" + L".txt");

		vector<int> basicInfo;

		basicInfo.push_back(map->GetObjectCount());
		basicInfo.push_back(map->GetLeftBottom().x);
		basicInfo.push_back(map->GetLeftBottom().y);
		basicInfo.push_back(map->GetRightTop().x);
		basicInfo.push_back(map->GetRightTop().y);
		basicInfo.push_back(map->GetStartPos().x);
		basicInfo.push_back(map->GetStartPos().y);

		basicWriter.Uint(basicInfo.size());
		basicWriter.Byte(basicInfo.data(), basicInfo.size() * sizeof(int));
	}

	{
		BinaryWriter mapWriter(path + L".txt");

		vector<int> mapInfo;


		for (auto& objects : map->GetObjects())
		{
			for (auto& object : objects)
			{
				mapInfo.push_back((int)object->GetType());
				mapInfo.push_back(object->GetLevel());
				mapInfo.push_back(object->GetNum());
				mapInfo.push_back((int)object->GetTexture()->GetTransform()->GetPos().x);
				mapInfo.push_back((int)object->GetTexture()->GetTransform()->GetPos().y);
				mapInfo.push_back((int)object->GetReversed());
			}
		}

		mapWriter.Uint(mapInfo.size());
		mapWriter.Byte(mapInfo.data(), mapInfo.size() * sizeof(int));
	}
}

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}