#ifndef MYSF_LAYER_HPP_
# define MYSF_LAYER_HPP_

# include <list>
# include <algorithm>

namespace mysf
{
	template <typename T>
  class Layer
  {
  public:
    Layer() {}
    Layer(const Layer & o) : _list(o._list) {}
    Layer & operator=(const Layer & o)
		{
	    if (&o == this)
	      return *this;
			_list = o._list;
	    return *this;
		}
    virtual ~Layer() {}

    void	add(T * node)
	  {
	    _list.push_back(node);
	  }

		void 	remove(T * node)
		{
			_list.erase(std::find(_list.begin(), _list.end(), node));
		}

    void	clear()
	  {
	    _list.clear();
	  }

  protected:
    std::list<T *>	_list;
  };
}

#endif // !MYSF_LAYER_HPP_
