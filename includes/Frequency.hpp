#ifndef FREQUENCY_HPP_
# define FREQUENCY_HPP_

# include <iostream>

# include "SceneNode.hpp"
# include "ResourceHolder.hpp"
# include "Resource.hpp"

class Frequency : public mysf::SceneNode
{
public:
  explicit Frequency(unsigned int value = 0);
  Frequency(const Frequency &) = delete;
  Frequency & operator=(const Frequency &) = delete;
  virtual ~Frequency();

  bool init(const mysf::TextureHolder & thl);

  void set(unsigned int value);
  void add(unsigned int value);
  void sub(unsigned int value);

  unsigned int get() const;

protected:
  virtual void updateCurrent(const sf::Time & deltaTime, const mysf::Event & event);
  virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

private:
  void _updateDigit();

private:
  unsigned int _value;
  sf::Sprite _digit[3];

  bool _drawArrow[2];
  sf::Sprite _arrow[2];

  static const unsigned int _max;
  static const float _speed;
};

#endif // !FREQUENCY_HPP_
