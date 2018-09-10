#include "GraphicRender.hpp"

namespace mysf
{
  GraphicRender::GraphicRender()
  {

  }

  GraphicRender::~GraphicRender()
  {

  }

	bool GraphicRender::init()
	{
		return true;
	}

  GraphicRender * GraphicRender::update(const sf::Time & deltaTime, const Event & event)
  {
		_spl.removeStoppedSounds();
    _gls.update(deltaTime, event);
    return this;
  }

  void GraphicRender::draw(sf::RenderTarget & target, sf::RenderStates states) const
  {
		_gls.draw(target, states);
  }
}
