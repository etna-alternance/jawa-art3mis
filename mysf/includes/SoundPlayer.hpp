#ifndef MYSF_SOUND_PLAYER_HPP_
# define MYSF_SOUND_PLAYER_HPP_

# include <list>

# include <SFML/Audio.hpp>

namespace mysf
{
	class SoundPlayer : public sf::Listener
	{
	public:
		SoundPlayer();
		SoundPlayer(const SoundPlayer &) = delete;
		SoundPlayer & operator=(const SoundPlayer &) = delete;
		virtual ~SoundPlayer();

		static void 				setNbLayer(unsigned int nbLayer);
		static unsigned int	getNbLayer();
		static void 				setLayerVolume(float volume, unsigned int layer);
		static float				getLayerVolume(unsigned int layer);

		void 								play(const sf::Sound & sound);
		void 								play(const sf::Sound & sound, unsigned int layer);
		unsigned int				getNbSoundPlaying() const;
		void 								removeStoppedSounds();

	private:
		static std::vector<float> 		_volumes;
		std::list<sf::Sound>				 	_sounds;
	};
}

#endif // !MYSF_SOUND_PLAYER_HPP_
