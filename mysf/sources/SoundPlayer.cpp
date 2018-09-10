#include "SoundPlayer.hpp"

namespace mysf
{
	std::vector<float> SoundPlayer::_volumes;

	SoundPlayer::SoundPlayer()
	{

	}

	SoundPlayer::~SoundPlayer()
	{

	}

	void SoundPlayer::setNbLayer(unsigned int nbLayer)
	{
		_volumes.resize(nbLayer);
	}

	unsigned int SoundPlayer::getNbLayer()
	{
		return _volumes.size();
	}

	void SoundPlayer::setLayerVolume(float volume, unsigned int layer)
	{
		_volumes[layer] = volume;
	}

	float SoundPlayer::getLayerVolume(unsigned int layer)
	{
		return _volumes[layer];
	}

	void SoundPlayer::play(const sf::Sound & sound)
	{
		_sounds.push_back(sf::Sound(sound));
		_sounds.back().play();
	}

	void SoundPlayer::play(const sf::Sound & sound, unsigned int layer)
	{
		_sounds.push_back(sf::Sound(sound));
		sf::Sound & s = _sounds.back();

		s.setVolume(s.getVolume() * _volumes[layer] / 100.f);
		s.play();
	}

	unsigned int SoundPlayer::getNbSoundPlaying() const
	{
		return _sounds.size();
	}

	void SoundPlayer::removeStoppedSounds()
	{
		_sounds.remove_if([] (const sf::Sound & s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
	}
}
