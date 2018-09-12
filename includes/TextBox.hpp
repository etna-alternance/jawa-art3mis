#ifndef TEXTBOX_HPP_
# define TEXTBOX_HPP_

# include <fstream>

# include "SceneNode.hpp"
# include "ResourceHolder.hpp"
# include "Resource.hpp"

class TextBox : public mysf::SceneNode
{
public:
	TextBox();
	TextBox(const TextBox &) = default;
	TextBox & operator=(const TextBox &) = default;
	virtual ~TextBox();

	bool init(const mysf::FontHolder & fhl);
	bool setFilename(const std::string & filename);
	bool isOver() const;

	void setSize(float width, float height);
	void setSize(const sf::Vector2f & size);
	const sf::Vector2f & getSize() const;

protected:
	virtual void updateCurrent(const sf::Time & deltaTime, const mysf::Event & event);
	virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	void _updateText();
	void _centerText(bool isCenter = true);
	int _whereToCut(const std::string & str, unsigned int offset) const;
	unsigned int _stringTextW(const std::string & str) const;

private:
	std::ifstream _file;
	std::string _quote;
	sf::Time _letterTime;
	bool _over;

	sf::Vector2f _size;
	sf::Text _text;

	static constexpr unsigned int _characterSize = 40;
};

#endif // !TEXTBOX_HPP_
