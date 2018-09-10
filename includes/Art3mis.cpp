#ifndef ART3MIS_HPP_
# define ART3MIS_HPP_

# include <iostream>
# include <string>
# include <vector>

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

# include "Engine.hpp"
# include "CodecRender.hpp"

class Art3mis : public mysf::Engine
{
public:
	Art3mis();
	Art3mis(const Art3mis &) = delete;
	Art3mis & operator=(const Art3mis &) = delete;
	virtual ~Art3mis();

	virtual bool init(int ac, char ** av);

public:
	static constexpr std::string WIN_NAME;
};

#endif // !ART3MIS_HPP_
