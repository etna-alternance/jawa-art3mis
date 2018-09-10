#include "Engine.hpp"

namespace mysf
{
  Engine::Engine()
    : _grender(0)
		, _speed(1.f)
  {

  }

  Engine::~Engine()
  {
    if (_grender)
      delete _grender;
  }

	bool Engine::init(int /* ac */, char ** /* av */)
	{
		_grender = new GraphicRender;

		return _grender->init();
	}

  int Engine::run()
  {
		sf::Clock clock;
    int ret = 0;

		// Doesn't work if put in contructor
		_window.setKeyRepeatEnabled(false);
		_event._size = _window.getSize();

		_draw(); // 1st render
    while (_window.isOpen())
      {
	      _processEvents();
      	if ((ret = _update(clock.restart())))
      	  {
      	    _window.close();
      	    return ret - 1;
      	  }
      	_draw();
      }
    return ret;
  }

	void Engine::pause(bool isPaused)
	{
		_speed = isPaused ? 0.f : 1.f;
	}

	void Engine::setSpeed(float speed)
	{
		_speed = speed;
	}

	void Engine::multiplySpeed(float speed)
	{
		_speed *= speed;
	}

	void Engine::divideSpeed(float speed)
	{
		_speed /= speed;
	}

	float Engine::getSpeed() const
	{
		return _speed;
	}

  void Engine::_processEvents()
  {
		static sf::Event event;

		_event.loop();
    while (_window.pollEvent(event))
      _event.update(event);
  }

  // return (0: continue, 1: close win, 2: error)
  int Engine::_update(const sf::Time & deltaTime)
  {
    GraphicRender * ret;

    if (!_grender)
      return 2;
    if ((ret = _grender->update(deltaTime * _speed, _event)) != _grender)
      {
      	delete _grender;
      	if ((_grender = ret) == 0)
      	  return 1;
      	if (_grender->init() == false)
      	  return 2;
      	_event.reset();
      }
    return 0;
  }

  void Engine::_draw()
  {
    _window.clear();
    if (_grender)
      _grender->draw(_window);
    _window.display();
  }
}
