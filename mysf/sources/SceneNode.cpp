#include "SceneNode.hpp"

namespace mysf
{
  SceneNode::SceneNode()
    : sf::Transformable()
    , sf::Drawable()
    , _child()
    , _parent(0)
  {

  }

  SceneNode::~SceneNode()
  {

  }

  void SceneNode::addChild(SceneNode & child)
  {
    child._parent = this;
    _child.push_back(&child);
  }

	SceneNode * SceneNode::getChild(const SceneNode & node)
	{
		for (auto it = _child.begin(); it != _child.end(); ++it)
			if (&node == *it)
				return *it;
		return 0;
	}

  SceneNode * SceneNode::subChild(const SceneNode & node)
  {
    for (auto it = _child.begin(); it != _child.end(); ++it)
      if (&node == *it)
    	{
    	  _child.erase(it);
    	  return *it;
    	}
    return 0;
  }

  sf::Transform SceneNode::getWorldTransform() const
  {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode * node = this; node; node = node->_parent)
      transform *= node->getTransform();
    return transform;
  }

  sf::Vector2f SceneNode::getWorldPosition() const
  {
    return getWorldTransform() * sf::Vector2f();
  }

  void SceneNode::update(const sf::Time & deltaTime, const Event & event)
  {
    updateCurrent(deltaTime, event);
    for (auto it = _child.begin(); it != _child.end(); ++it)
      (*it)->update(deltaTime, event);
  }

  void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
  {
    states.transform *= getTransform();
    drawCurrent(target, states);
    for (auto it = _child.begin(); it != _child.end(); ++it)
      (*it)->draw(target, states);
  }

  void SceneNode::updateCurrent(const sf::Time & /* deltaTime */, const Event & /* event */)
	{

	}

	void SceneNode::drawCurrent(sf::RenderTarget & /* target */, sf::RenderStates /* states */) const
	{

	}
}
