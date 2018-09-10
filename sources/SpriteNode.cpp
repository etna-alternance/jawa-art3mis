#include "SpriteNode.hpp"

SpriteNode::SpriteNode()
{

}

SpriteNode::SpriteNode(const sf::Texture & texture)
{
	setTexture(texture);
}

SpriteNode::SpriteNode(const sf::Texture & texture, const sf::IntRect & rectangle)
{
	setTexture(texture);
	setTextureRect(rectangle);
}

SpriteNode::~SpriteNode()
{

}

void SpriteNode::setTexture(const sf::Texture & texture, bool resetRect)
{
	_sprite.setTexture(texture, resetRect);
}

void SpriteNode::setTextureRect(const sf::IntRect & rectangle)
{
	_sprite.setTextureRect(rectangle);
}

void SpriteNode::setColor(const sf::Color & color)
{
	_sprite.setColor(color);
}

const sf::Texture * SpriteNode::getTexture() const
{
	return _sprite.getTexture();
}

const sf::IntRect & SpriteNode::getTextureRect() const
{
	return _sprite.getTextureRect();
}

const sf::Color & SpriteNode::getColor() const
{
	return _sprite.getColor();
}

void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
