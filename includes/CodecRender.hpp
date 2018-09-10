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
# include "Frequency.hpp"
# include "Resource.hpp"

class CodecRender : public mysf::GraphicRender
{
public:
  explicit CodecRender(const std::string & filename, const std::string & bgmusic, const std::string & ringtone, const sf::Vector2f & scale = sf::Vector2f(1.f, 1.f));
  CodecRender(const CodecRender &) = delete;
  CodecRender & operator=(const CodecRender &) = delete;
  virtual ~CodecRender();

  virtual bool init();
  virtual mysf::GraphicRender * update(const sf::Time & deltaTime, const mysf::Event & event);

protected:
  bool initResourceHolders();
  bool initMusic();
  bool initNodes();
  bool initTalkers();
  bool initLines();
  void setupLoading(float percent);
  void setupLoaded();
  bool changeTalker();

protected:
  mysf::TextureHolder _thl;
  mysf::ResourceHolder<sf::Texture, std::string> _thlTalkers;
  mysf::FontHolder _fhl;
  mysf::SoundBufferHolder _shl;

  sf::Music _music;
  bool _ringing;
  const std::string _bgmusic;
  const std::string _ringtone;

  const sf::Vector2f _scale;
  SpriteNode _background;
  SpriteNode _ptt;
  SpriteNode _fourteen;
  SpriteNode _dot;

  mysf::SceneNode _middleground;
  TextBox _textBox;
  std::vector<mysf::AnimNode> _talkers;
  std::map<std::string, int> _tbind;
  int _iTalker;
  mysf::AnimNode * _talking[2];
  mysf::AnimNode _lines[2];
  Frequency _frequency;

  static constexpr float _musicVolume = 100.f;
  static const sf::Vector2u _spriteSize;
  static const sf::Vector2f _positions[2];
};

#endif // !CODEC_RENDER_HPP_
