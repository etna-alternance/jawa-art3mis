#include "GraphicLayerSet.hpp"

namespace mysf
{
  GraphicLayerSet::GraphicLayerSet(unsigned int nbLayer)
    : LayerSet(nbLayer)
  {

  }

  GraphicLayerSet::~GraphicLayerSet()
  {

  }

  void GraphicLayerSet::update(const sf::Time & deltaTime, const Event & event)
  {
    for (unsigned int i = 0; i < _layers.size(); ++i)
      _layers[i].update(deltaTime, event);
  }

  void GraphicLayerSet::draw(sf::RenderTarget & target, sf::RenderStates states) const
  {
    for (unsigned int i = 0; i < _layers.size(); ++i)
      _layers[i].draw(target, states);
  }
}
