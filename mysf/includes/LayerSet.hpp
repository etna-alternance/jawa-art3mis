#ifndef MYSF_LAYER_SET_HPP_
# define MYSF_LAYER_SET_HPP_

# include <vector>
# include <iostream>

# include <SFML/Graphics.hpp>

# include "Layer.hpp"
# include "Event.hpp"

namespace mysf
{
	template <typename T>
  class LayerSet
  {
  public:
    explicit LayerSet(unsigned int nbLayer = 0) : _layers(nbLayer) {}
    LayerSet(const LayerSet &) = delete;
    LayerSet & operator=(const LayerSet &) = delete;
    virtual ~LayerSet() {}

		unsigned int size() const
		{
			return _layers.size();
		}

    void		resize(unsigned int nbLayer)
	  {
	    clear();
	    _layers.resize(nbLayer);
	  }

    void		add(unsigned int nbLayer)
	  {
	    _layers.resize(_layers.size() + nbLayer);
	  }

    void		sub(unsigned int nbLayer)
	  {
	    if (_layers.size() != nbLayer)
	      for (unsigned int i = _layers.size() - nbLayer - 1; i < _layers.size(); ++i)
		     _layers[i].clear();
	    _layers.resize(_layers.size() - nbLayer);
	  }

    void		clear()
	  {
	    for (unsigned int i = 0; i < _layers.size(); ++i)
	      _layers[i].clear();
		}

  	T & operator[](unsigned int layer)
		{
			return _layers[layer];
		}

    const T & operator[](unsigned int layer) const
		{
			return _layers[layer];
		}

  protected:
    std::vector<T> _layers;
  };
}

#endif // !MYSF_LAYER_SET_HPP_
