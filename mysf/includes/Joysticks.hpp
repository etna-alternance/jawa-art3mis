#ifndef MYSF_JOYSTICKS_HPP_
# define MYSF_JOYSTICKS_HPP_

# include <vector>

# include <SFML/Window.hpp>

# include "EventType.hpp"

namespace mysf
{
  class Joysticks
  {
		typedef void (Joysticks::*updateFct)(const sf::Event & event);

  public:
    class Joystick
    {
			friend class Joysticks;

    public:
      Joystick();
      Joystick(const Joystick & o);
      Joystick & operator=(const Joystick & o);
      virtual ~Joystick();

      void connect();
      void disconnect();
      bool isConnected() const;

      void reset();

			bool 		isDown(unsigned int button) const;
			float 	getAxis(sf::Joystick::Axis axis) const;

    private:
      bool _isConnected;
      std::vector<bool> _down;
      std::vector<float> _axis;
    };

  public:
    Joysticks();
    Joysticks(const Joysticks & o);
    Joysticks & operator=(const Joysticks & o);
    virtual ~Joysticks();

    void	update(const sf::Event & event);
		void 	loop();
    void	reset();

		void 							setEventType(const EventType & eventType);
		const EventType &	getEventType() const;

    const Joystick & operator[](unsigned int joystick) const;
    unsigned int size() const;
    unsigned int nbConnected() const;
		bool isConnected(unsigned int joystick) const;

  private:
    void connect(unsigned int joystick);
    void disconnect(unsigned int joystick);

		void _updatePressed(const sf::Event & event);
		void _updateOnPressed(const sf::Event & event);
		void _updateOnReleased(const sf::Event & event);

		std::vector<updateFct> _update;

  protected:
		EventType							_eventType;
		std::vector<int>			_buttons;

		std::vector<Joystick> _joysticks;
    unsigned int          _nbConnected;
  };
}

#endif // !MYSF_JOYSTICKS_HPP_
