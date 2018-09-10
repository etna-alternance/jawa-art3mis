#include "Mouse.hpp"

namespace mysf
{
  Mouse::Mouse()
    : _update(EventType::EventTypeCount)
		, _eventType(EventType::Pressed)
		, _button(sf::Mouse::ButtonCount)
		, _down(sf::Mouse::ButtonCount, false)
    , _inside(false)
    , _moved(false)
    , _scrolled(false)
    , _pos(0, 0)
    , _wheelTick(0, 0)
  {
		_update[EventType::Pressed] = &Mouse::_updatePressed;
		_update[EventType::OnPressed] = &Mouse::_updateOnPressed;
		_update[EventType::OnReleased] = &Mouse::_updateOnReleased;
  }

  Mouse::Mouse(const Mouse & o)
    : _update(EventType::EventTypeCount)
		, _eventType(o._eventType)
		, _button(o._button)
		, _down(o._down)
    , _inside(o._inside)
    , _moved(o._moved)
    , _scrolled(o._scrolled)
    , _pos(o._pos)
    , _wheelTick(o._wheelTick)
  {
		_update[EventType::Pressed] = &Mouse::_updatePressed;
		_update[EventType::OnPressed] = &Mouse::_updateOnPressed;
		_update[EventType::OnReleased] = &Mouse::_updateOnReleased;
  }

  Mouse & Mouse::operator=(const Mouse & o)
  {
    if (this == &o)
      return *this;
		_eventType = o._eventType;
		_button = o._button;
		_down = o._down;
    _inside = o._inside;
    _moved = o._moved;
    _scrolled = o._scrolled;
    _pos = o._pos;
    _wheelTick = o._wheelTick;
    return *this;
  }

  Mouse::~Mouse()
  {

  }

  void Mouse::update(const sf::Event & event)
  {
		_moved = false;
		_scrolled = false;

		(this->*_update[_eventType])(event);
		switch (event.type)
			{
			case sf::Event::MouseEntered:
				_inside = true;
				break;
			case sf::Event::MouseLeft:
				_inside = false;
				break;
			case sf::Event::MouseMoved:
				_moved = true;
				_pos.x = event.mouseMove.x;
				_pos.y = event.mouseMove.y;
				break;
			case sf::Event::MouseWheelScrolled:
				_scrolled = true;
				switch (event.mouseWheelScroll.wheel)
					{
					case sf::Mouse::HorizontalWheel:
						_wheelTick.x = event.mouseWheel.delta;
						_wheelTick.y = 0;
						break;
					case sf::Mouse::VerticalWheel:
						_wheelTick.x = 0;
						_wheelTick.y = event.mouseWheel.delta;
						break;
					}
				break;
			default:
				break;
			}
  }

	void Mouse::loop()
	{
		if (_eventType != EventType::Pressed && _button != sf::Mouse::ButtonCount)
		{
			_down[_button] = false;
			_button = sf::Mouse::ButtonCount;
		}
	}

  void Mouse::reset()
  {
		_button = sf::Mouse::ButtonCount;
    for (unsigned int i = 0; i < _down.size(); ++i)
      _down[i] = false;
  }

	void Mouse::setEventType(const EventType & eventType)
	{
		_eventType = eventType;
		reset();
	}

	const EventType & Mouse::getEventType() const
	{
		return _eventType;
	}

  bool Mouse::isDown(sf::Mouse::Button button) const
  {
    return _down[button];
  }

  bool Mouse::isInside() const
  {
    return _inside;
  }

  bool Mouse::isMoved() const
  {
    return _moved;
  }

  bool Mouse::isScrolled() const
  {
    return _scrolled;
  }

  bool Mouse::isScrolled(WheelDir dir) const
  {
		if (_scrolled == false)
			return false;
		switch (dir)
		{
			case Up:
				return _wheelTick.y > 0;
				break;
			case Down:
				return _wheelTick.y < 0;
				break;
			case Right:
				return _wheelTick.x > 0;
				break;
			case Left:
				return _wheelTick.x < 0;
				break;
			default:
				break;
		}
		return false;
  }

  const sf::Vector2i & Mouse::getPos() const
  {
    return _pos;
  }

  const sf::Vector2i & Mouse::getWheelTick() const
  {
    return _wheelTick;
  }

	void Mouse::_updatePressed(const sf::Event & event)
	{
		switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				_down[event.mouseButton.button] = true;
				break;
			case sf::Event::MouseButtonReleased:
				_down[event.mouseButton.button] = false;
				break;
			default:
				break;
			}
	}

	void Mouse::_updateOnPressed(const sf::Event & event)
	{
		switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				_button = event.mouseButton.button;
      	_down[_button] = true;
				break;
			default:
				break;
			}
	}

	void Mouse::_updateOnReleased(const sf::Event & event)
	{
		switch (event.type)
			{
			case sf::Event::MouseButtonReleased:
				_button = event.mouseButton.button;
      	_down[_button] = true;
				break;
			default:
				break;
			}
	}
}
