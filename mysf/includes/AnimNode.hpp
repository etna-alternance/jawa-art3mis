#ifndef MYSF_AnimNode_HPP_
# define MYSF_AnimNode_HPP_

# include <vector>

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

# include "SceneNode.hpp"

namespace mysf
{
  class AnimNode : public SceneNode
  {
  public:
    explicit AnimNode(bool isPaused = false, bool isLooped = true);
    explicit AnimNode(const sf::Texture & texture, bool isPaused = false, bool isLooped = true);
    AnimNode(const AnimNode & o) = default;
    AnimNode & operator=(const AnimNode & o) = default;
    virtual ~AnimNode();

    void setTexture(const sf::Texture & texture);
    const sf::Texture * getTexture() const;
    void addFrame(const sf::IntRect & rect);
    void addFrame(const sf::IntRect & rect, const sf::Texture & texture);

    void play();
    void pause();
    void stop();
    void loop(bool isLooped = true);

    void setFrameTime(const sf::Time & deltaTime);
    const sf::Time & getFrameTime() const;

    bool isPlaying() const;
    bool isLooped() const;

  protected:
    virtual void updateCurrent(const sf::Time & deltaTime, const Event & event);
    virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

  protected:
    const sf::Texture * _texture;
    std::vector<sf::Sprite> _frames;

    sf::Time _frameTime;
    sf::Time _currTime;
    unsigned int _currFrame;
    bool _paused;
    bool _looped;
  };
}

#endif //!MYSF_AnimNode_HPP_
