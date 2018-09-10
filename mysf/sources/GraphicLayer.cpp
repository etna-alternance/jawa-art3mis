#include "GraphicLayer.hpp"

namespace mysf
{
  GraphicLayer::GraphicLayer()
  {

  }

  GraphicLayer::GraphicLayer(const GraphicLayer & o)
    : Layer(o)
  {

  }

  GraphicLayer & GraphicLayer::operator=(const GraphicLayer & o)
  {
    if (&o == this)
      return *this;
		Layer::operator=(o);
    return *this;
  }

  GraphicLayer::~GraphicLayer()
  {

  }

  void GraphicLayer::update(const sf::Time & deltaTime, const Event & event)
  {
    for (auto it = _list.begin(); it != _list.end(); ++it)
      (*it)->update(deltaTime, event);
  }

  void GraphicLayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
  {
    for (auto it = _list.begin(); it != _list.end(); ++it)
      (*it)->draw(target, states);
  }
}
