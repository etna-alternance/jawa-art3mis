#ifndef MYSF_GRAPHIC_LAYER_SET_HPP_
# define MYSF_GRAPHIC_LAYER_SET_HPP_

# include <vector>

# include <SFML/Graphics.hpp>

# include "LayerSet.hpp"
# include "GraphicLayer.hpp"
# include "Event.hpp"

namespace mysf
{
  class GraphicLayerSet : public LayerSet<GraphicLayer>
  {
  public:
    explicit GraphicLayerSet(unsigned int nbLayer = 0);
    GraphicLayerSet(const GraphicLayerSet &) = delete;
    GraphicLayerSet & operator=(const GraphicLayerSet &) = delete;
    virtual ~GraphicLayerSet();

    void	update(const sf::Time & deltaTime, const Event & event);
    void	draw(sf::RenderTarget & target, sf::RenderStates states = sf::RenderStates()) const;
  };
}

#endif // !MYSF_GRAPHIC_LAYER_SET_HPP_
