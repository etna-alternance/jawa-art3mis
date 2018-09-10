# include "Frequency.hpp"

const unsigned int Frequency::_max   = 199;
const float        Frequency::_speed = 0.1f;

Frequency::Frequency(unsigned int value)
  : _value(value)
{
  _drawArrow[0] = false;
  _drawArrow[1] = false;
}

Frequency::~Frequency()
{

}

bool Frequency::init(const mysf::TextureHolder & thl)
{
  for (unsigned int i = 0; i < 3; ++i)
    _digit[i].setTexture(thl[Resource::Texture::Digits]);

  _digit[0].setPosition(160, 77);
  _digit[1].setPosition(175, 77);
  _digit[2].setPosition(187, 77);
  _updateDigit();

  _arrow[0].setTexture(thl[Resource::Texture::ArrowL]);
  _arrow[1].setTexture(thl[Resource::Texture::ArrowR]);

  _arrow[0].setPosition(90, 68);
  _arrow[1].setPosition(205, 68);
  return true;
}

void Frequency::set(unsigned int value)
{
  _value = (value > _max ? _max : value);
}

void Frequency::add(unsigned int value)
{
  _value = (_value + value) % (_max + 1);
}

void Frequency::sub(unsigned int value)
{
  if (value > _value)
    _value = (_max + 1) - (value - _value);
  else
    _value -= value;
}

unsigned int Frequency::get() const
{
  return _value;
}

void Frequency::updateCurrent(const sf::Time & deltaTime, const mysf::Event & event)
{
  static sf::Time delta = sf::Time::Zero;
  unsigned int tmpValue = _value;

  if (event.key().isDown(sf::Keyboard::Left) || event.key().isDown(sf::Keyboard::Right))
    {
      if (_drawArrow[0] || _drawArrow[1])
	{
	  _drawArrow[0] = event.key().isDown(sf::Keyboard::Left) ? true : false;
	  _drawArrow[1] = event.key().isDown(sf::Keyboard::Right) ? true : false;
	  for (delta += deltaTime; delta.asSeconds() >= _speed; delta -= sf::seconds(_speed))
	    {
	      if (_drawArrow[0])
		sub(1);
	      if (_drawArrow[1])
		add(1);
	    }
	}
      else
	{
	  if (event.key().isDown(sf::Keyboard::Left))
	    {
	      sub(1);
	      _drawArrow[0] = true;
	    }
	  else
	    _drawArrow[0] = false;
	  if (event.key().isDown(sf::Keyboard::Right))
	    {
	      add(1);
	      _drawArrow[1] = true;
	    }
	  else
	    _drawArrow[1] = false;
	}
    }
  else
    {
      delta = sf::Time::Zero;
      _drawArrow[0] = false;
      _drawArrow[1] = false;
    }

  if (tmpValue != _value)
    _updateDigit();
}

void Frequency::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
  for (unsigned int i = 0; i < 3; ++i)
    target.draw(_digit[i], states);
  for (unsigned int i = 0; i < 2; ++i)
    if (_drawArrow[i])
      target.draw(_arrow[i], states);
}

void Frequency::_updateDigit()
{
  _digit[0].setTextureRect(sf::IntRect((_value / 100) * 11, 0, 11, 19));
  _digit[1].setTextureRect(sf::IntRect((_value / 10 % 10) * 11, 0, 11, 19));
  _digit[2].setTextureRect(sf::IntRect((_value % 10) * 11, 0, 11, 19));
}
