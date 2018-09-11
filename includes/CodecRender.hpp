#ifndef CODEC_RENDER_HPP_
# define CODEC_RENDER_HPP_

# include <iostream>
# include <string>
# include <vector>

# include "GraphicRender.hpp"
# include "ResourceHolder.hpp"
# include "AnimNode.hpp"

# include "const.hpp"

# include "TextBox.hpp"
# include "SpriteNode.hpp"
# include "Resource.hpp"

class CodecRender : public mysf::GraphicRender
{
public:
	explicit CodecRender(const std::string & filename, const std::string & bgmusic, const sf::Vector2f & scale = sf::Vector2f(1.f, 1.f));
	CodecRender(const CodecRender &) = delete;
	CodecRender & operator=(const CodecRender &) = delete;
	virtual ~CodecRender();

	virtual bool init();
	virtual mysf::GraphicRender * update(const sf::Time & deltaTime, const mysf::Event & event);

private:
	bool initResourceHolders();
	bool initMusic();
	bool initNodes();
	bool initTalker();
	void setupLoaded();

protected:
	mysf::TextureHolder _thl;
	mysf::FontHolder _fhl;
	mysf::SoundBufferHolder _shl;

private:
	const sf::Vector2f _scale;

	SpriteNode _background;

	mysf::SceneNode _middleground;
	mysf::AnimNode _talker;

	mysf::SceneNode _frontground;
	TextBox _textBox;

	const std::string _bgmusic;
	sf::Music _music;

	static constexpr float _musicVolume = 100.f;
	static const sf::Vector2u _spriteSize;
	static const sf::Vector2f _position;
};

#endif // !CODEC_RENDER_HPP_
