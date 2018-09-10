#include "Art3mis.hpp"

std::string Art3mis::WIN_NAME = "Codec - Art3mis";

Art3mis::Art3mis()
	: mysf::Engine()
{
	static const std::vector<sf::VideoMode> & modes = sf::VideoMode::getFullscreenModes();

	if (modes.size())
		_window.create(modes[0], WIN_NAME, sf::Style::Fullscreen);
	else
		_window.create(sf::VideoMode(320, 240), WIN_NAME);
	_window.setFramerateLimit(30);
}

Art3mis::~Art3mis()
{

}

bool Art3mis::init(int ac, char ** av)
{
	if (ac < 2 || ac > 3)
    {
		std::cerr << "Usage: " << av[0] << " transmission.csv [music]" << std::endl;
		return false;
    }

	const sf::Vector2u wsize = _window.getSize();
	_grender = new CodecRender(av[1], ac > 2 ? av[2] : DFT_MUSIC, sf::Vector2f(wsize.x / 320.f, wsize.y / 240.f));
	return _grender->init();
}
