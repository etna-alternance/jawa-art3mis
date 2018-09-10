#ifndef MYSF_GRAPHIC_LAYER_HPP_
# define MYSF_GRAPHIC_LAYER_HPP_

# include <list>
# include <algorithm>

# include <SFML/Graphics.hpp>

# include "Layer.hpp"
# include "SceneNode.hpp"
# include "Event.hpp"

namespace mysf
{
  class GraphicLayer : public Layer<SceneNode>
  {
  public:
    GraphicLayer();
    GraphicLayer(const GraphicLayer & o);
    GraphicLayer & operator=(const GraphicLayer & o);
    virtual ~GraphicLayer();

    void	update(const sf::Time & deltaTime, const Event & event);
    void	draw(sf::RenderTarget & target, sf::RenderStates states) const;
  };
}

#endif // !MYSF_GRAPHIC_LAYER_HPP_
