#ifndef TEXTBOX_HPP_
# define TEXTBOX_HPP_

# include "SceneNode.hpp"
# include "ResourceHolder.hpp"
# include "Resource.hpp"
# include "Dialogue.hpp"

class TextBox : public mysf::SceneNode
{
public:
  TextBox();
  TextBox(const TextBox &) = default;
  TextBox & operator=(const TextBox &) = default;
  virtual ~TextBox();

  bool init(const mysf::FontHolder & fhl);
  void setFilename(const std::string & filename);

  void setSize(float width, float height);
  void setSize(const sf::Vector2f & size);
  const sf::Vector2f & getSize() const;

  bool isTalkerChanged();
  int getIndex() const;
  const std::string & getTalker() const;
  const std::vector<std::string> & getTalkers() const;
  const std::vector<std::string> & getFirstTalkers() const;
  bool isOver() const;

protected:
  virtual void updateCurrent(const sf::Time & deltaTime, const mysf::Event & event);
  virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

private:
  void _updateText();
  void _centerText(bool isCenter = true);
  int _whereToCut(const std::string & str, unsigned int offset) const;
  unsigned int _stringTextW(const std::string & str) const;

private:
  Dialogue _dialogue;
  Dialogue::DataQuote _currQuote;
  sf::Time _letterTime;
  bool _talkerChanged;
  bool _over;

  sf::Vector2f _size;
  sf::Text _text;
};

#endif // !TEXTBOX_HPP_
