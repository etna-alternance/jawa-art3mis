#ifndef  DIALOGUE_HPP_
# define DIALOGUE_HPP_

# include <string>
# include <vector>
# include <queue>
# include <algorithm>
# include <stdexcept>

# include "ACsvParser.hpp"

class Dialogue : public ACsvParser
{
public:
  struct DataQuote
  {
    int index;
    std::string talker;
    std::string quote;

    explicit DataQuote(void);
    DataQuote(const DataQuote &) = default;
    DataQuote &operator=(const DataQuote &) = default;
    ~DataQuote(void);
  };

  typedef bool (Dialogue::*funcPtr)(unsigned int, unsigned int, Dialogue::DataQuote &, const std::string &);

public:
  explicit Dialogue(const std::string & filename = std::string());
  Dialogue(const Dialogue &) = default;
  Dialogue & operator=(const Dialogue &) = default;
  virtual ~Dialogue(void);

  const Dialogue::DataQuote & front(void) const;
  void pop(void);
  bool empty(void) const;

  const std::vector<std::string> & getTalkers() const;
  const std::vector<std::string> & getFirstTalkers() const;

protected:
  virtual bool onParse(unsigned int x, unsigned int y, const std::string & value) override;
  virtual bool finalCheck(void) override;

private:
  static const std::vector<Dialogue::funcPtr> _funcTab;
  std::queue<Dialogue::DataQuote> _dialog;
  std::vector<std::string> _talkers;
  std::vector<std::string> _firstTalkers;

  bool addIndex(unsigned int x, unsigned int y, Dialogue::DataQuote & dataQuote, const std::string & value = std::string());
  bool addTalker(unsigned int x, unsigned int y, Dialogue::DataQuote & dataQuote, const std::string & value = std::string());
  bool addQuote(unsigned int x, unsigned int y, Dialogue::DataQuote & dataQuote, const std::string & value = std::string());
  bool defaultFunc(unsigned int x, unsigned int y, Dialogue::DataQuote & dataQuote, const std::string & value = std::string());

  bool checkIndex(int index) const;
  bool checkTalker(const std::string & talker) const;
  bool checkQuote(const std::string & quote) const;

  static void errColumn(unsigned int iLine, unsigned int iColumn, const std::string & target);

public:
  static const int DEF_DQ_INDEX;
  static const std::string DEF_DQ_TALKER;
  static const std::string DEF_DQ_QUOTE;
};

#endif // !DIALOGUE_HPP_
