#include "CodecRender.hpp"

const sf::Vector2u CodecRender::_spriteSize = sf::Vector2u(354, 285);
const sf::Vector2f CodecRender::_position   = sf::Vector2f(541, 281);

CodecRender::CodecRender(const std::string & filename, const std::string & bgmusic, const sf::Vector2f & scale)
	: mysf::GraphicRender()
	, _scale(scale)
	, _bgmusic(bgmusic)
{
	_gls.resize(3);

	_gls[0].add(&_background);
	_gls[1].add(&_middleground);
	_gls[2].add(&_frontground);
	_textBox.setFilename(filename);
}

CodecRender::~CodecRender()
{
	_thl.unload();
	_fhl.unload();
	_shl.unload();
}

bool CodecRender::init()
{
	if (initResourceHolders() == false)
		return false;
	if (initMusic() == false)
		return false;
	if (initNodes() == false)
		return false;
	if (initTalker() == false)
		return false;
	setupLoaded();
	return true;
}

mysf::GraphicRender * CodecRender::update(const sf::Time & deltaTime, const mysf::Event & event)
{
	static sf::Time delta = sf::Time::Zero;
	const float ds = delta.asSeconds();
	constexpr float fadeTime = 4.f;

	if (event.isClosed() || event.key().isDown(sf::Keyboard::Escape))
		return 0;

	delta += deltaTime;
	if (_textBox.isOver())
	{
		const float musicFadeVolume = _music.getVolume();

		if (ds > fadeTime)
			return 0;
		_music.setVolume(musicFadeVolume - (musicFadeVolume * (ds / fadeTime)));
		_talker.stop();
	}

	_spl.removeStoppedSounds();
	_gls.update(deltaTime, event);
	return this;
}

bool CodecRender::initResourceHolders()
{
	if (_thl.setDefault(IMAGE_DIR"default.png") == false)
		return false;
	if (_fhl.setDefault(FONT_DIR"default.otf") == false)
		return false;
	if (_shl.setDefault(MUSIC_DIR"default.ogg") == false)
		return false;

	_thl.load(Resource::Texture::Codec, IMAGE_DIR"background.png");
	_thl.load(Resource::Texture::Talk,  IMAGE_DIR"ss_talk.png");

	_fhl.load(Resource::Font::Orbitron, FONT_DIR"orbitron.otf");
	return true;
}

bool CodecRender::initMusic()
{
	_shl.load(Resource::Sound::Subdivisions, MUSIC_DIR"subdivisions.ogg");
	if (_music.openFromFile(_bgmusic))
	{
		_music.setLoop(true);
		_music.setVolume(_musicVolume);
		_music.stop();
	}
	return true;
}

bool CodecRender::initNodes()
{
	if (_textBox.init(_fhl) == false)
		return false;
	_textBox.setPosition(WIN_SIZE_X / 6.f, WIN_SIZE_Y * 0.75f);
	_textBox.setSize(WIN_SIZE_X - (2 * _textBox.getPosition().x), WIN_SIZE_Y - (_textBox.getPosition().y + 20));

	_background.setTexture(_thl[Resource::Texture::Codec]);
	_background.setScale(_scale);

	_middleground.setScale(_scale);

	_frontground.setScale(_scale);
	_frontground.addChild(_textBox);
	return true;
}

bool CodecRender::initTalker()
{
	_talker.setTexture(_thl[Resource::Texture::Talk]);
	_talker.setPosition(_position.x, _position.y);

	for (unsigned int i = 0; i < _talker.getTexture()->getSize().x / _spriteSize.x; ++i)
		_talker.addFrame(sf::IntRect(i * _spriteSize.x, 0, _spriteSize.x, _spriteSize.y));
	_talker.setFrameTime(sf::seconds(0.1f));
	_talker.stop();

	_middleground.addChild(_talker);
	return true;
}

void CodecRender::setupLoaded()
{
	_music.play();
	_talker.play();
}
