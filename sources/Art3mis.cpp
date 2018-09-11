#include "Art3mis.hpp"

const std::string Art3mis::_winName = WIN_NAME;
const sf::Vector2f Art3mis::_winSize = sf::Vector2f(WIN_SIZE_X, WIN_SIZE_Y);

Art3mis::Art3mis()
	: mysf::Engine()
{
	static const std::vector<sf::VideoMode> & modes = sf::VideoMode::getFullscreenModes();

	if (modes.size())
		_window.create(modes[0], _winName, sf::Style::Fullscreen);
	else
		_window.create(sf::VideoMode(_winSize.x, _winSize.y), _winName);
	_window.setFramerateLimit(30);
}

Art3mis::~Art3mis()
{

}

bool Art3mis::init(int ac, char ** av)
{
	if (ac < 2 || ac > 3)
	{
		std::cerr << "Usage: " << av[0] << " transmission.txt [music]" << std::endl;
		return false;
	}

	const sf::Vector2u wsize = _window.getSize();
	_grender = new CodecRender(av[1], ac > 2 ? av[2] : DFT_MUSIC, sf::Vector2f(wsize.x / _winSize.x, wsize.y / _winSize.y));
	return _grender->init();
}
