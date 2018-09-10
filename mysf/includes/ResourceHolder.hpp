#ifndef MYSF_RESOURCE_HOLDER_HPP_
# define MYSF_RESOURCE_HOLDER_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>

# include <string>
# include <vector>

namespace mysf
{
  template <typename Resource, typename Identifier = unsigned int>
  class ResourceHolder
  {
  public:
    explicit ResourceHolder(const Resource & defaultRsc = Resource())
      : _resourceArr()
      , _default(defaultRsc)
    {

    }

    ResourceHolder(const ResourceHolder & o)
      : _resourceArr(o._resourceArr)
      , _default(o._default)
    {

    }

    ResourceHolder & operator=(const ResourceHolder & o)
    {
      if (&o == this)
	     return *this;
      _resourceArr = o._resourceArr;
      _default = o._default;
      return *this;
    }

    virtual ~ResourceHolder()
    {
      for (auto it = _resourceArr.begin(); it != _resourceArr.end(); ++it)
	      delete it->second;
    }

    bool load(const Identifier id, const std::string & filename)
    {
      Resource * resource = new Resource();

      if (resource->loadFromFile(filename) == false)
	     return false;
      if (_resourceArr[id])
	     delete _resourceArr[id];
      _resourceArr[id] = resource;
      return true;
    }

    template <typename Parameter>
    bool load(const Identifier id, const std::string & filename, const Parameter & secondParam)
    {
      Resource * resource = new Resource();

      if (resource->loadFromFile(filename, secondParam) == false)
        return false;
      if (_resourceArr[id])
	      delete _resourceArr[id];
      _resourceArr[id] = resource;
      return true;
    }

    void unload()
    {
      for (auto it = _resourceArr.begin(); it != _resourceArr.end(); ++it)
        delete it->second;
      _resourceArr.clear();
    }

    void unload(const Identifier id)
    {
      auto found = _resourceArr.find(id);

      if (found != _resourceArr.end())
    	{
    	  delete found->second;
    	  _resourceArr.erase(found);
    	}
    }

    bool setDefault(const std::string & filename)
    {
      return _default.loadFromFile(filename);
    }

    void setDefault(const Resource & defaultRsc)
    {
      _default = defaultRsc;
    }

    const Resource & getDefault() const
    {
      return _default;
    }

    Resource & operator[](const Identifier id)
    {
      auto found = _resourceArr.find(id);

      if (found == _resourceArr.end())
	     return _default;
      return *(found->second);
    }

    const Resource & operator[](const Identifier id) const
    {
      auto found = _resourceArr.find(id);

      if (found == _resourceArr.end())
	      return _default;
      return *(found->second);
    }

  private:
    std::map<Identifier, Resource *> _resourceArr;
    Resource _default;
  };

  typedef ResourceHolder<sf::Texture> 		TextureHolder;
  typedef ResourceHolder<sf::SoundBuffer>	SoundBufferHolder;
  typedef ResourceHolder<sf::Font> 				FontHolder;
}

#endif // !MYSF_RESOURCE_HOLDER_HPP_
