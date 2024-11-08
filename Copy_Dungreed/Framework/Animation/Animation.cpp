#include "framework.h"
#include "Animation.h"


void Animation::Update()
{
	assert(_texture != nullptr);

	if (_curState != _index.first)
	{
		_index.first = _curState;
		_index.second = 0;
		ChangeImage();
		_isPlaying = true;
	}

	if (_isPlaying == true)
	{
		_animRunTime += DELTA_TIME;
		if (_animRunTime >= _animSpeed[_index.first][_index.second] && _isPlaying == true)
		{
			_animRunTime = 0;
			_index.second++;
			if (_index.second < _animList[_index.first].size())
			{
				ChangeImage();
			}
			else
			{
				switch (_animState[_index.first])
				{
				case Animation::Anim_State::END:
					_isPlaying = false;
					break;
				case Animation::Anim_State::LOOP:
					_index.second = 0;
					ChangeImage();
					break;
				case Animation::Anim_State::PINGPONG:
					_index.second = 1;
					reverse(_animList[_index.first].begin(), _animList[_index.first].end());
					ChangeImage();
					break;
				}
			}
		}
	}
}

void Animation::ChangeAnimation(int state , bool force)
{
	if (force)
	{
		_index.first = state;
		_index.second = 0;
	}

	if(_animList[state].size() > 0)
		_curState = state;

}

void Animation::ChangeImage()
{
	if (_beforeChange != nullptr)
		_beforeChange(_index);
	_texture->SetImage(_animList[_index.first][_index.second]);
	if (_afterChange != nullptr)
		_afterChange(_index);
}
