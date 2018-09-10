#include "CodCodeCodec.hpp"

CodCodeCodec::CodCodeCodec()
  : mysf::Engine()
{
  static const std::vector<sf::VideoMode> & modes = sf::VideoMode::getFullscreenModes();

  if (modes.size())
    _window.create(modes[0], "CodCodeCodec", sf::Style::Fullscreen);
  else
    _window.create(sf::VideoMode(320, 240), "CodCodeCodec");
  _window.setFramerateLimit(30);
}

CodCodeCodec::~CodCodeCodec()
{

}

bool CodCodeCodec::init(int ac, char ** av)
{
  if (ac < 2 || ac > 4)
    {
      std::cerr << "Usage: " << av[0] << " mission.csv [music] [ringtone]" << std::endl;
      return false;
    }

  const sf::Vector2u wsize = _window.getSize();
  _grender = new CodecRender(av[1], ac > 2 ? av[2] : DFT_MUSIC, ac > 3 ? av[3] : DFT_RINGT, sf::Vector2f(wsize.x / 320.f, wsize.y / 240.f));
  return _grender->init();
}
