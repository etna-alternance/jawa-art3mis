#include "AnimNode.hpp"

namespace mysf
{
  AnimNode::AnimNode(bool isPaused, bool isLooped)
    : _texture(0)
    , _frames(0)
    , _frameTime(sf::seconds(1.f))
    , _currTime(sf::Time::Zero)
    , _currFrame(0)
    , _paused(isPaused)
    , _looped(isLooped)
  {

  }

  AnimNode::AnimNode(const sf::Texture & texture, bool isPaused, bool isLooped)
    : _texture(&texture)
    , _frames(0)
    , _frameTime(sf::seconds(1.f))
    , _currTime(sf::Time::Zero)
    , _currFrame(0)
    , _paused(isPaused)
    , _looped(isLooped)
  {

  }

  AnimNode::~AnimNode()
  {

  }

  void AnimNode::setTexture(const sf::Texture & texture)
  {
    _texture = &texture;
  }

  const sf::Texture * AnimNode::getTexture() const
  {
    return _texture;
  }

  void AnimNode::addFrame(const sf::IntRect & rect)
  {
    if (_texture)
      _frames.push_back(sf::Sprite(*_texture, rect));
  }

  void AnimNode::addFrame(const sf::IntRect & rect, const sf::Texture & texture)
  {
    _frames.push_back(sf::Sprite(texture, rect));
  }

  void AnimNode::play()
  {
    _paused = false;
  }

  void AnimNode::pause()
  {
    _paused = true;
  }

  void AnimNode::stop()
  {
    _paused = true;
    _currFrame = 0;
  }

  void AnimNode::loop(bool isLooped)
  {
    _looped = isLooped;
  }

  void AnimNode::setFrameTime(const sf::Time & deltaTime)
  {
    _frameTime = deltaTime;
  }

  const sf::Time & AnimNode::getFrameTime() const
  {
    return _frameTime;
  }

  bool AnimNode::isPlaying() const
  {
   return !_paused;
  }

  bool AnimNode::isLooped() const
  {
   return _looped;
  }

  void AnimNode::updateCurrent(const sf::Time & deltaTime, const Event & /* event */)
  {
    if (_paused)
      return ;
    _currTime += deltaTime;
    if (_currTime < _frameTime)
      return ;
    _currTime = sf::microseconds(_currTime.asMicroseconds() % _frameTime.asMicroseconds());
    if (_currFrame + 1 < _frames.size())
      ++_currFrame;
    else
    {
      if (_looped)
        _currFrame = 0;
      else
        _paused = true;
    }
  }

  void AnimNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
  {
    target.draw(_frames[_currFrame], states);
  }
}
