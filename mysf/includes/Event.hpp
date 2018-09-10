#ifndef MYSF_EVENT_HPP_
# define MYSF_EVENT_HPP_

# include <SFML/Window.hpp>

# include "Key.hpp"
# include "Mouse.hpp"
# include "Joysticks.hpp"

namespace mysf
{
  class Event
  {
		friend class Engine;

  public:
    Event();
    Event(const Event & o);
    Event & operator=(const Event & o);
    virtual ~Event();

    void	           			update(const sf::Event & event);
		void 									loop();
    void	           			reset();

		Key &				  	  		key();
    const Key &		    		key() const;
		Mouse &	    					mouse();
    const Mouse &	    		mouse() const;
	 	Joysticks &						joysticks();
    const Joysticks & 		joysticks() const;

    bool				          isClosed() const;
    bool				          isFocused() const;
		bool									isResized() const;
		const sf::Vector2u &	getSize() const;

  protected:
    Key		            		_key;
    Mouse	            		_mouse;
    Joysticks         		_joysticks;
    bool	            		_closed;
    bool              		_focus;
		bool									_resized;
		sf::Vector2u					_size;
  };
}

#endif // !MYSF_EVENT_HPP_
