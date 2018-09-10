#ifndef SPRITE_NODE_HPP_
# define SPRITE_NODE_HPP_

# include "SceneNode.hpp"
# include "Event.hpp"

class SpriteNode : public mysf::SceneNode
{
public:
	SpriteNode();
	explicit SpriteNode(const sf::Texture & texture);
	explicit SpriteNode(const sf::Texture & texture, const sf::IntRect & rectangle);
	SpriteNode(const SpriteNode & o) = delete;
	SpriteNode & operator=(const SpriteNode & o) = delete;
	virtual ~SpriteNode();

	void setTexture(const sf::Texture & texture, bool resetRect = false);
	void setTextureRect(const sf::IntRect & rectangle);
	void setColor(const sf::Color & color);

	const sf::Texture * getTexture() const;
	const sf::IntRect & getTextureRect() const;
	const sf::Color & getColor() const;

protected:
	virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

protected:
	sf::Sprite _sprite;
};

#endif // !SPRITE_NODE_HPP_
