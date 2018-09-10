#include "TextBox.hpp"

TextBox::TextBox()
	: _letterTime(sf::seconds(0.09f))
	, _over(false)
{

}

TextBox::~TextBox()
{

}

bool TextBox::init(const mysf::FontHolder & fhl)
{
	if (_dialogue.parse() == false)
		return false;
	if (_dialogue.empty() == false)
		_currQuote = _dialogue.front();
	_text.setFont(fhl[Resource::Font::Ayar]);
	_text.setCharacterSize(11);
	return true;
}

void TextBox::setFilename(const std::string & filename)
{
	_dialogue.setFilename(filename);
}

bool TextBox::isOver() const
{
	return _over;
}

void TextBox::setSize(float width, float height)
{
	_size.x = width;
	_size.y = height;
}

void TextBox::setSize(const sf::Vector2f & size)
{
	_size = size;
}

const sf::Vector2f & TextBox::getSize() const
{
	return _size;
}

void TextBox::updateCurrent(const sf::Time & deltaTime, const mysf::Event &)
{
	static sf::Time quoteTime(sf::Time::Zero);
	static sf::Time timer(sf::Time::Zero);

	timer += deltaTime;
	if (timer >= quoteTime)
    {
		timer -= quoteTime;
		if (_dialogue.empty() == false)
    	{
			if (_currQuote.index != _dialogue.front().index || _currQuote.talker != _dialogue.front().talker)
				_talkerChanged = true;
			_currQuote = _dialogue.front();
			_dialogue.pop();
			_updateText();
			quoteTime = _letterTime * static_cast<sf::Int64>(_currQuote.quote.size());
			quoteTime += _letterTime * static_cast<sf::Int64>(10);
    	}
		else
		{
			quoteTime = sf::Time::Zero;
			_over = true;
    	}
    }
}

void TextBox::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_text, states);
}

void TextBox::_updateText()
{
	std::string cut(_currQuote.quote);
	unsigned int count = 0;
	int ret = 0;

	while ((ret = _whereToCut(cut, ret)) != -1)
    {
		cut[ret] = '\n';
		++count;
    }
	_text.setString(cut);
	_centerText(!count);
}

void TextBox::_centerText(bool isCenter)
{
	if (isCenter)
    {
		const sf::FloatRect rect(_text.getLocalBounds());

		_text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
		_text.setPosition(_size.x / 2.f, 0.f);
    }
	else
    {
		_text.setOrigin(0.f, 0.f);
		_text.setPosition(0.f, 0.f);
    }
}

int TextBox::_whereToCut(const std::string & str, unsigned int offset) const
{
	int pos = -1;

	if (_stringTextW(str.substr(offset)) <= _size.x)
		return pos;
	for (unsigned int i = offset; i < str.size(); ++i)
		if (str[i] == ' ')
		{
			if (_stringTextW(str.substr(offset, i - offset)) > _size.x)
				return pos;
			pos = i;
		}
	return pos;
}

unsigned int TextBox::_stringTextW(const std::string & str) const
{
	sf::Text tmp(_text);

	tmp.setString(str);
	return tmp.getLocalBounds().width;
}
