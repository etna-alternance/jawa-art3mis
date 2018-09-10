#include "ACsvParser.hpp"

ACsvParser::ACsvParser(const std::string & filename)
  : _filename(filename)
{

}

ACsvParser::~ACsvParser()
{

}

void ACsvParser::setFilename(const std::string & filename)
{
  _filename = filename;
}

const std::string & ACsvParser::getFilename() const
{
  return _filename;
}

bool ACsvParser::parse()
{
  std::ifstream file;
  std::string line;

  file.open(_filename.c_str());
  if (file.is_open() == false)
    return false;

  for (unsigned int y = 0; std::getline(file, line); ++y)
    {
      std::stringstream ss(line);

      for (unsigned int x = 0; std::getline(ss, line, ';'); ++x)
	if (onParse(x, y, line) == false)
	  return false;
    }

  file.close();
  return finalCheck();
}

bool ACsvParser::parse(const std::string & filename)
{
  setFilename(filename);
  return parse();
}

bool ACsvParser::finalCheck()
{
  return true;
}
