#ifndef MYSF_ENGINE_HPP_
# define MYSF_ENGINE_HPP_

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

# include "GraphicRender.hpp"
# include "Event.hpp"

namespace mysf
{
  class Engine
  {
  public:
    Engine();
    Engine(const Engine &) = delete;
    Engine & operator=(const Engine &) = delete;
    virtual ~Engine();

    virtual bool init(int ac, char ** av);
    int run();

		void 	pause(bool isPaused);
		void 	setSpeed(float speed);
		void 	multiplySpeed(float speed);
		void 	divideSpeed(float speed);
		float	getSpeed() const;

  private:
    void	_processEvents();
    int		_update(const sf::Time & deltaTime);
    void	_draw();

  protected:
		sf::RenderWindow  	_window;
    GraphicRender *			_grender;
    Event 							_event;
		float 							_speed;
  };
}

#endif // !MYSF_ENGINE_HPP_
