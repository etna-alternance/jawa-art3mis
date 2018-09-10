#include "CodecRender.hpp"

const sf::Vector2u CodecRender::_spriteSize   = sf::Vector2u(52, 89);
const sf::Vector2f CodecRender::_positions[2] = {sf::Vector2f(30.f, 30.f), sf::Vector2f(236.f, 30.f)};

CodecRender::CodecRender(const std::string & filename, const std::string & ringtone, const sf::Vector2f & scale)
	: mysf::GraphicRender()
	, _bgmusic(bgmusic)
	, _scale(scale)
{
	_gls.resize(2);

	_gls[0].add(&_background);
	_gls[1].add(&_middleground);
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
	return true;
}

mysf::GraphicRender * CodecRender::update(const sf::Time & deltaTime, const mysf::Event & event)
{
	static sf::Time delta = sf::Time::Zero;
	constexpr float wait = 0.35f;
	constexpr float fadeTime = 4.f;
	const float ds = delta.asSeconds();

	if (event.isClosed() || event.key().isDown(sf::Keyboard::Escape))
		return 0;

	if (_iTalker == -1)
    {
		if (_spl.getNbSoundPlaying() == 0)
        {
			_spl.play(sf::Sound(_shl[Resource::Sound::Answer]));
			_middleground.addChild(_lines[0]);
			_ringing = false;
        }
		if (_ringing == false)
        {
			delta += deltaTime;
			if (ds > wait)
            {
				setupLoaded();
				delta = sf::Time::Zero;
            }
			else
				setupLoading(ds / wait);
        }
    }
	else
    {
		if (_textBox.isOver())
        {
			const static float musicFadeVolume = _music.getVolume();

			delta += deltaTime;
			if (ds > fadeTime)
				return 0;
			_music.setVolume(musicFadeVolume - (musicFadeVolume * (ds / fadeTime)));
			_talking[_iTalker]->stop();
			_lines[1].stop();
        }
		else if (_textBox.isTalkerChanged())
			changeTalker();
    }

	_spl.removeStoppedSounds();
	_gls.update(deltaTime, event);
	return this;
}

bool CodecRender::initResourceHolders()
{
	if (_thl.setDefault(IMAGE_DIR"default.png") == false)
		return false;
	if (_thlTalkers.setDefault(IMAGE_DIR"default.png") == false)
		return false;
	if (_fhl.setDefault(FONT_DIR"default.ttf") == false)
		return false;
	if (_shl.setDefault(MUSIC_DIR"default.ogg") == false)
		return false;

	_thl.load(Resource::Texture::Codec,    IMAGE_DIR"codec.png");
	_thl.load(Resource::Texture::PTT,      IMAGE_DIR"ptt.png");
	_thl.load(Resource::Texture::Fourteen, IMAGE_DIR"14.png");
	_thl.load(Resource::Texture::Dot,      IMAGE_DIR"dot.png");
	_thl.load(Resource::Texture::Digits,   IMAGE_DIR"digits.png");
	_thl.load(Resource::Texture::ArrowL,   IMAGE_DIR"arrow_l.png");
	_thl.load(Resource::Texture::ArrowR,   IMAGE_DIR"arrow_r.png");
	_thl.load(Resource::Texture::Lines,    IMAGE_DIR"lines.png");

	_fhl.load(Resource::Font::Ayar,        FONT_DIR"ayar_takhu.ttf");
	return true;
}

bool CodecRender::initMusic()
{
	_shl.load(Resource::Sound::Ringtone, _ringtone);
	_shl.load(Resource::Sound::Answer, MUSIC_DIR"answer.ogg");
	if (_music.openFromFile(_bgmusic))
    {
		_music.setLoop(true);
		_music.setVolume(_musicVolume);
		_music.stop();
    }

	_spl.play(sf::Sound(_shl[Resource::Sound::Ringtone]));
	_ringing = true;
	return true;
}

bool CodecRender::initNodes()
{
	if (_textBox.init(_fhl) == false)
		return false;
	_textBox.setPosition(30, 140);
	_textBox.setSize(320 - (2 * _textBox.getPosition().x), 240 - (_textBox.getPosition().y + 15));

	_ptt.setTexture(_thl[Resource::Texture::PTT]);
	_ptt.setPosition(143, 31);
	_fourteen.setTexture(_thl[Resource::Texture::Fourteen]);
	_fourteen.setPosition(141, 80);
	_dot.setTexture(_thl[Resource::Texture::Dot]);
	_dot.setPosition(171, 92);

	_background.setTexture(_thl[Resource::Texture::Codec]);
	_background.setScale(_scale);
	_middleground.setScale(_scale);
	return true;
}

bool CodecRender::initTalker()
{
	const std::vector<std::string> & t = _textBox.getTalkers();
	const std::vector<std::string> & ft = _textBox.getFirstTalkers();

	_talkers.resize(t.size());
	for (unsigned int i = 0; i < t.size(); ++i)
    {
		_thlTalkers.load(t[i], IMAGE_DIR"talker_" + t[i] + ".png");
		_talkers[i].setTexture(_thlTalkers[t[i]]);
		for (unsigned int j = 0; j < _talkers[i].getTexture()->getSize().x / _spriteSize.x; ++j)
			_talkers[i].addFrame(sf::IntRect(j * _spriteSize.x, 0, _spriteSize.x, _spriteSize.y));
		_talkers[i].setFrameTime(sf::seconds(0.2f));
		_talkers[i].stop();
		_tbind[t[i]] = i;
    }
	for (unsigned int i = 0; i < ft.size(); ++i)
    {
		mysf::AnimNode & talker = _talkers[_tbind[ft[i]]];

		_talking[i] = &talker;
		if (i < 2)
			talker.setPosition(_positions[i].x, _positions[i].y + (_spriteSize.y / 2.f));
		talker.setOrigin(0, _spriteSize.y / 2.f);
		talker.setScale(1.f, 0.f);
		_middleground.addChild(talker);
    }
	_iTalker = -1;
	return true;
}

void CodecRender::setupLoading(float percent)
{
	for (unsigned int i = 0; i < 2; ++i)
		if (_talking[i])
			_talking[i]->setScale(1.f, percent);
}

void CodecRender::setupLoaded()
{
	_music.play();
	_background.addChild(_ptt);
	_background.addChild(_fourteen);
	_background.addChild(_dot);
	_middleground.addChild(_textBox);
	_middleground.addChild(_frequency);
	_middleground.subChild(_lines[0]);
	_middleground.addChild(_lines[1]);

	for (unsigned int i = 0; i < 2; ++i)
		if (_talking[i])
		{
			_talking[i]->setOrigin(0, 0);
			_talking[i]->setPosition(_positions[i]);
			_talking[i]->setScale(1.f, 1.f);
		}
	_iTalker = _textBox.getIndex();
	_talking[_iTalker]->play();
}
