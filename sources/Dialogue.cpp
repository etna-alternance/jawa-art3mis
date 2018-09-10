#include  "Dialogue.hpp"

const std::vector<Dialogue::funcPtr> Dialogue::_funcTab({
    &Dialogue::addIndex,
    &Dialogue::addTalker,
    &Dialogue::addQuote,
    &Dialogue::defaultFunc
  });

const int         Dialogue::DEF_DQ_INDEX = -1;
const std::string Dialogue::DEF_DQ_TALKER = std::string();
const std::string Dialogue::DEF_DQ_QUOTE = std::string();

Dialogue::Dialogue(const std::string & filename) :
  ACsvParser(filename)
{}

Dialogue::~Dialogue(void)
{}

Dialogue::DataQuote::DataQuote(void) :
  index(Dialogue::DEF_DQ_INDEX),
  talker(Dialogue::DEF_DQ_TALKER),
  quote(Dialogue::DEF_DQ_QUOTE)
{}

Dialogue::DataQuote::~DataQuote(void)
{}

const Dialogue::DataQuote &Dialogue::front(void) const
{
  return (_dialog.front());
}

void Dialogue::pop(void)
{
  _dialog.pop();
}

bool Dialogue::empty(void) const
{
  return (_dialog.empty());
}

const std::vector<std::string> & Dialogue::getTalkers() const
{
  return _talkers;
}

const std::vector<std::string> & Dialogue::getFirstTalkers() const
{
  return _firstTalkers;
}

bool Dialogue::onParse(unsigned int x, unsigned int y, const std::string & value)
{
  static Dialogue::DataQuote dataQuote;

  if ((this->*_funcTab[x < _funcTab.size() ? x : _funcTab.size() - 1])(x, y, dataQuote, value))
    {
      if (x == _funcTab.size() - 2)
	{
	  _dialog.push(dataQuote);
	  dataQuote = Dialogue::DataQuote();
	}
      return (true);
    }
  return (false);
}

bool Dialogue::finalCheck(void)
{
  return (true);
}

bool Dialogue::addIndex(unsigned int x, unsigned int y, Dialogue::DataQuote & dataQuote, const std::string & value)
{
  if (checkIndex(dataQuote.index))
    {
      Dialogue::errColumn(y - 1, x, "Quote");
      return (false);
    }
  try {
    dataQuote.index = std::stoi(value);
  }
  catch (std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
    Dialogue::errColumn(y, x, "Index");
    std::cerr << "Expected 0 or 1 value." << std::endl;
    return (false);
  }
  if (dataQuote.index != 0 && dataQuote.index != 1)
    {
      Dialogue::errColumn(y, x, "Index");
      std::cerr << "Expected 0 or 1 value." << std::endl;
      return (false);
    }
  return (true);
}

bool Dialogue::addTalker(unsigned int x, unsigned int y, Dialogue::DataQuote & dataQuote, const std::string & value)
{
  if (!checkIndex(dataQuote.index))
    {
      Dialogue::errColumn(y, x, "Index");
      return (false);
    }
  dataQuote.talker = value;
  if (std::find(_talkers.begin(), _talkers.end(), value) == _talkers.end())
    _talkers.push_back(value);

  if (dataQuote.index >= 0 && static_cast<unsigned int>(dataQuote.index) >= _firstTalkers.size())
    {
      _firstTalkers.resize(dataQuote.index + 1);
      _firstTalkers[dataQuote.index] = value;
    }
  else if (_firstTalkers[dataQuote.index].empty())
    _firstTalkers[dataQuote.index] = value;
  return (true);
}

bool Dialogue::addQuote(unsigned int x, unsigned int y, Dialogue::DataQuote & dataQuote, const std::string & value)
{
  if (!checkIndex(dataQuote.index))
    {
      Dialogue::errColumn(y, x, "Index");
      return (false);
    }
  if (!checkTalker(dataQuote.talker))
    {
      Dialogue::errColumn(y, x, "Talker");
      return (false);
    }
  dataQuote.quote = value;
  if (!checkQuote(dataQuote.quote))
    {
      Dialogue::errColumn(y, x, "Quote");
      return (false);
    }
  return (true);
}

bool Dialogue::defaultFunc(unsigned int x, unsigned int y, Dialogue::DataQuote &, const std::string &)
{
  std::cerr << "Line " << y + 1 << ", Column " << x + 1 << ": Too much columns." << std::endl;
  return (false);
}

bool Dialogue::checkIndex(int index) const
{
  if (index == Dialogue::DEF_DQ_INDEX)
    return (false);
  return (true);
}

bool Dialogue::checkTalker(const std::string & talker) const
{
  if (talker.compare(Dialogue::DEF_DQ_TALKER) == 0)
    return (false);
  return (true);
}

bool Dialogue::checkQuote(const std::string & quote) const
{
  if (quote.compare(Dialogue::DEF_DQ_QUOTE) == 0)
    return (false);
  return (true);
}

inline void Dialogue::errColumn(unsigned int iLine, unsigned int iColumn, const std::string & target)
{
  std::cerr << "Line " << iLine + 1 << ", Column " << iColumn + 1 << ": " << target << " column is missing, bad or empty." << std::endl;
}
