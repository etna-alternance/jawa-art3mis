#include "Binding.hpp"

namespace mysf
{
	Binding::Binding(unsigned int nbAction, unsigned int joystickId)
		: _bind(nbAction)
		, _joystickId(joystickId)
	{

	}

	Binding::Binding(const Binding & o)
		: _bind(o._bind)
		, _joystickId(o._joystickId)
	{

	}

	Binding & Binding::operator=(const Binding & o)
	{
		if (this == &o)
			return *this;
		_bind = o._bind;
		_joystickId = o._joystickId;
		return *this;
	}

	Binding::~Binding()
	{

	}

	const std::vector<Input> * Binding::getInput(unsigned int action, const Event & event) const
	{
		bool stop;

		for (unsigned int i = 0; i < _bind[action].size(); ++i)
		{
			stop = false;
			for (unsigned int j = 0; j < _bind[action][i].size() && !stop; ++j)
			{
				const Input & input = _bind[action][i][j];

				switch (input.type)
				{
					case Input::KeyboardKey:
						stop = (event.key().isDown(input.keycode) == false);
						break;
					case Input::MouseButton:
						stop = (event.mouse().isDown(input.mButton) == false);
						break;
					case Input::MouseWheel:
						stop = (event.mouse().isScrolled(input.wheelDir) == false);
						break;
					case Input::JoystickButton:
						stop = (event.joysticks().isConnected(_joystickId) == false || event.joysticks()[_joystickId].isDown(input.jButton) == false);
						break;
					case Input::JoystickAxis:
						stop = (event.joysticks().isConnected(_joystickId) == false || event.joysticks()[_joystickId].getAxis(input.axis) == 0.f);
						break;
					default:
						return 0;
				}
			}
			if (!stop)
				return &_bind[action][i];
		}
		return 0;
	}

	bool Binding::load(const std::string & filename, const std::map<std::string, unsigned int> & bind)
	{
		std::map<std::string, Input> sfbind;
		std::ifstream file;
		std::string line;

		file.open(filename.c_str());
		if (file.is_open() == false)
			return false;
		_initSfbind(sfbind);

		while (std::getline(file, line))
		{
			line = line.substr(0, line.find_first_of("#"));
			_eraseSpace(line);
			if (line.size())
			{
				std::size_t pos;
				unsigned int action;

				pos = line.find_first_of("=");
				if (pos != std::string::npos)
				{
			    action = bind.at(line.substr(0, pos));
			    line = line.substr(pos + 1);
					setBind(action, _parseActionOr(line, sfbind));
				}
			}
		}

		file.close();
		return true;
	}

	void Binding::setNbAction(unsigned int size)
	{
		_bind.resize(size);
	}

	void Binding::setBind(unsigned int action, const Input & bind)
	{
		if (action >= _bind.size())
			_bind.resize(action + 1);
		_bind[action].resize(1);
		_bind[action][0].resize(1, bind);
	}

	void Binding::setBind(unsigned int action, const std::vector<Input> & bind)
	{
		if (action >= _bind.size())
			_bind.resize(action + 1);
		_bind[action].resize(1);
		_bind[action][0] = bind;
	}

	void Binding::setBind(unsigned int action, const std::vector<std::vector<Input>> & bind)
	{
		if (action >= _bind.size())
			_bind.resize(action + 1);
		_bind[action] = bind;
	}

	void Binding::setJoystickId(unsigned int joystickId)
	{
		_joystickId = joystickId;
	}

	unsigned int Binding::getJoystickId() const
	{
		return _joystickId;
	}

	std::vector<std::vector<Input>> Binding::_parseActionOr(std::string line, const std::map<std::string, Input> & sfbind) const
	{
		std::vector<std::vector<Input>> key;

		while (line.size())
		{
			std::size_t pos;

			pos = line.find('|');
			key.push_back(_parseActionAnd(line.substr(0, pos), sfbind));
			if (pos == std::string::npos)
				return key;
			line = line.substr(pos + 1);
		}
		return key;
	}

	std::vector<Input> Binding::_parseActionAnd(std::string line, const std::map<std::string, Input> & sfbind) const
	{
		std::vector<Input> key;

		while (line.size())
		{
			std::size_t pos;

			pos = line.find('+');
			key.push_back(sfbind.at(line.substr(0, pos)));
			if (pos == std::string::npos)
				return key;
			line = line.substr(pos + 1);
		}
		return key;
	}

  void Binding::_eraseSpace(std::string & str) const
  {
    std::size_t pos, size;

    while ((pos = str.find_first_of(" \n\t")) != std::string::npos)
    {
			size = str.find_first_not_of(" \n\t", pos);
			if (size != std::string::npos)
			  size -= pos;
			str.erase(pos, size);
    }
  }

	void Binding::_initSfbind(std::map<std::string, Input> & sfbind) const
	{
		// KeyboardKey
		sfbind["A"] = {Input::KeyboardKey, {sf::Keyboard::A}};
    sfbind["B"] = {Input::KeyboardKey, {sf::Keyboard::B}};
    sfbind["C"] = {Input::KeyboardKey, {sf::Keyboard::C}};
    sfbind["D"] = {Input::KeyboardKey, {sf::Keyboard::D}};
    sfbind["E"] = {Input::KeyboardKey, {sf::Keyboard::E}};
    sfbind["F"] = {Input::KeyboardKey, {sf::Keyboard::F}};
    sfbind["G"] = {Input::KeyboardKey, {sf::Keyboard::G}};
    sfbind["H"] = {Input::KeyboardKey, {sf::Keyboard::H}};
    sfbind["I"] = {Input::KeyboardKey, {sf::Keyboard::I}};
    sfbind["J"] = {Input::KeyboardKey, {sf::Keyboard::J}};
    sfbind["K"] = {Input::KeyboardKey, {sf::Keyboard::K}};
    sfbind["L"] = {Input::KeyboardKey, {sf::Keyboard::L}};
    sfbind["M"] = {Input::KeyboardKey, {sf::Keyboard::M}};
    sfbind["N"] = {Input::KeyboardKey, {sf::Keyboard::N}};
    sfbind["O"] = {Input::KeyboardKey, {sf::Keyboard::O}};
    sfbind["P"] = {Input::KeyboardKey, {sf::Keyboard::P}};
    sfbind["Q"] = {Input::KeyboardKey, {sf::Keyboard::Q}};
    sfbind["R"] = {Input::KeyboardKey, {sf::Keyboard::R}};
    sfbind["S"] = {Input::KeyboardKey, {sf::Keyboard::S}};
    sfbind["T"] = {Input::KeyboardKey, {sf::Keyboard::T}};
    sfbind["U"] = {Input::KeyboardKey, {sf::Keyboard::U}};
    sfbind["V"] = {Input::KeyboardKey, {sf::Keyboard::V}};
    sfbind["W"] = {Input::KeyboardKey, {sf::Keyboard::W}};
    sfbind["X"] = {Input::KeyboardKey, {sf::Keyboard::X}};
    sfbind["Y"] = {Input::KeyboardKey, {sf::Keyboard::Y}};
    sfbind["Z"] = {Input::KeyboardKey, {sf::Keyboard::Z}};
    sfbind["Num0"] = {Input::KeyboardKey, {sf::Keyboard::Num0}};
    sfbind["Num1"] = {Input::KeyboardKey, {sf::Keyboard::Num1}};
    sfbind["Num2"] = {Input::KeyboardKey, {sf::Keyboard::Num2}};
    sfbind["Num3"] = {Input::KeyboardKey, {sf::Keyboard::Num3}};
    sfbind["Num4"] = {Input::KeyboardKey, {sf::Keyboard::Num4}};
    sfbind["Num5"] = {Input::KeyboardKey, {sf::Keyboard::Num5}};
    sfbind["Num6"] = {Input::KeyboardKey, {sf::Keyboard::Num6}};
    sfbind["Num7"] = {Input::KeyboardKey, {sf::Keyboard::Num7}};
    sfbind["Num8"] = {Input::KeyboardKey, {sf::Keyboard::Num8}};
    sfbind["Num9"] = {Input::KeyboardKey, {sf::Keyboard::Num9}};
    sfbind["Escape"] = {Input::KeyboardKey, {sf::Keyboard::Escape}};
    sfbind["LControl"] = {Input::KeyboardKey, {sf::Keyboard::LControl}};
    sfbind["LShift"] = {Input::KeyboardKey, {sf::Keyboard::LShift}};
    sfbind["LAlt"] = {Input::KeyboardKey, {sf::Keyboard::LAlt}};
    sfbind["LSystem"] = {Input::KeyboardKey, {sf::Keyboard::LSystem}};
    sfbind["RControl"] = {Input::KeyboardKey, {sf::Keyboard::RControl}};
    sfbind["RShift"] = {Input::KeyboardKey, {sf::Keyboard::RShift}};
    sfbind["RAlt"] = {Input::KeyboardKey, {sf::Keyboard::RAlt}};
    sfbind["RSystem"] = {Input::KeyboardKey, {sf::Keyboard::RSystem}};
    sfbind["Menu"] = {Input::KeyboardKey, {sf::Keyboard::Menu}};
    sfbind["LBracket"] = {Input::KeyboardKey, {sf::Keyboard::LBracket}};
    sfbind["RBracket"] = {Input::KeyboardKey, {sf::Keyboard::RBracket}};
    sfbind["SemiColon"] = {Input::KeyboardKey, {sf::Keyboard::SemiColon}};
    sfbind["Comma"] = {Input::KeyboardKey, {sf::Keyboard::Comma}};
    sfbind["Period"] = {Input::KeyboardKey, {sf::Keyboard::Period}};
    sfbind["Quote"] = {Input::KeyboardKey, {sf::Keyboard::Quote}};
    sfbind["Slash"] = {Input::KeyboardKey, {sf::Keyboard::Slash}};
    sfbind["BackSlash"] = {Input::KeyboardKey, {sf::Keyboard::BackSlash}};
    sfbind["Tilde"] = {Input::KeyboardKey, {sf::Keyboard::Tilde}};
    sfbind["Equal"] = {Input::KeyboardKey, {sf::Keyboard::Equal}};
    sfbind["Dash"] = {Input::KeyboardKey, {sf::Keyboard::Dash}};
    sfbind["Space"] = {Input::KeyboardKey, {sf::Keyboard::Space}};
    sfbind["Return"] = {Input::KeyboardKey, {sf::Keyboard::Return}};
    sfbind["BackSpace"] = {Input::KeyboardKey, {sf::Keyboard::BackSpace}};
    sfbind["Tab"] = {Input::KeyboardKey, {sf::Keyboard::Tab}};
    sfbind["PageUp"] = {Input::KeyboardKey, {sf::Keyboard::PageUp}};
    sfbind["PageDown"] = {Input::KeyboardKey, {sf::Keyboard::PageDown}};
    sfbind["End"] = {Input::KeyboardKey, {sf::Keyboard::End}};
    sfbind["Home"] = {Input::KeyboardKey, {sf::Keyboard::Home}};
    sfbind["Insert"] = {Input::KeyboardKey, {sf::Keyboard::Insert}};
    sfbind["Delete"] = {Input::KeyboardKey, {sf::Keyboard::Delete}};
    sfbind["Add"] = {Input::KeyboardKey, {sf::Keyboard::Add}};
    sfbind["Subtract"] = {Input::KeyboardKey, {sf::Keyboard::Subtract}};
    sfbind["Multiply"] = {Input::KeyboardKey, {sf::Keyboard::Multiply}};
    sfbind["Divide"] = {Input::KeyboardKey, {sf::Keyboard::Divide}};
    sfbind["Left"] = {Input::KeyboardKey, {sf::Keyboard::Left}};
    sfbind["Right"] = {Input::KeyboardKey, {sf::Keyboard::Right}};
    sfbind["Up"] = {Input::KeyboardKey, {sf::Keyboard::Up}};
    sfbind["Down"] = {Input::KeyboardKey, {sf::Keyboard::Down}};
    sfbind["Numpad0"] = {Input::KeyboardKey, {sf::Keyboard::Numpad0}};
    sfbind["Numpad1"] = {Input::KeyboardKey, {sf::Keyboard::Numpad1}};
    sfbind["Numpad2"] = {Input::KeyboardKey, {sf::Keyboard::Numpad2}};
    sfbind["Numpad3"] = {Input::KeyboardKey, {sf::Keyboard::Numpad3}};
    sfbind["Numpad4"] = {Input::KeyboardKey, {sf::Keyboard::Numpad4}};
    sfbind["Numpad5"] = {Input::KeyboardKey, {sf::Keyboard::Numpad5}};
    sfbind["Numpad6"] = {Input::KeyboardKey, {sf::Keyboard::Numpad6}};
    sfbind["Numpad7"] = {Input::KeyboardKey, {sf::Keyboard::Numpad7}};
    sfbind["Numpad8"] = {Input::KeyboardKey, {sf::Keyboard::Numpad8}};
    sfbind["Numpad9"] = {Input::KeyboardKey, {sf::Keyboard::Numpad9}};
    sfbind["F1"] = {Input::KeyboardKey, {sf::Keyboard::F1}};
    sfbind["F2"] = {Input::KeyboardKey, {sf::Keyboard::F2}};
    sfbind["F3"] = {Input::KeyboardKey, {sf::Keyboard::F3}};
    sfbind["F4"] = {Input::KeyboardKey, {sf::Keyboard::F4}};
    sfbind["F5"] = {Input::KeyboardKey, {sf::Keyboard::F5}};
    sfbind["F6"] = {Input::KeyboardKey, {sf::Keyboard::F6}};
    sfbind["F7"] = {Input::KeyboardKey, {sf::Keyboard::F7}};
    sfbind["F8"] = {Input::KeyboardKey, {sf::Keyboard::F8}};
    sfbind["F9"] = {Input::KeyboardKey, {sf::Keyboard::F9}};
    sfbind["F10"] = {Input::KeyboardKey, {sf::Keyboard::F10}};
    sfbind["F11"] = {Input::KeyboardKey, {sf::Keyboard::F11}};
    sfbind["F12"] = {Input::KeyboardKey, {sf::Keyboard::F12}};
    sfbind["F13"] = {Input::KeyboardKey, {sf::Keyboard::F13}};
    sfbind["F14"] = {Input::KeyboardKey, {sf::Keyboard::F14}};
    sfbind["F15"] = {Input::KeyboardKey, {sf::Keyboard::F15}};
    sfbind["Pause"] = {Input::KeyboardKey, {sf::Keyboard::Pause}};

		// MouseButton
		sfbind["MouseLeft"] = {Input::MouseButton, {sf::Mouse::Left}};
		sfbind["MouseRight"] = {Input::MouseButton, {sf::Mouse::Right}};
		sfbind["MouseMiddle"] = {Input::MouseButton, {sf::Mouse::Middle}};
		sfbind["MouseXButton1"] = {Input::MouseButton, {sf::Mouse::XButton1}};
		sfbind["MouseXButton2"] = {Input::MouseButton, {sf::Mouse::XButton2}};

		// MouseWheel
		sfbind["MouseVertical"] = {Input::MouseButton, {sf::Mouse::VerticalWheel}};
		sfbind["MouseHorizontal"] = {Input::MouseButton, {sf::Mouse::HorizontalWheel}};

		// JoystickButton
		for (unsigned int i = 0; i < sf::Joystick::ButtonCount; ++i)
			sfbind[std::string("Joystick") + std::to_string(i)] = {Input::JoystickButton, {i}};

		// JoystickAxis
		sfbind["JoystickX"] = {Input::JoystickAxis, {sf::Joystick::X}};
		sfbind["JoystickY"] = {Input::JoystickAxis, {sf::Joystick::Y}};
		sfbind["JoystickZ"] = {Input::JoystickAxis, {sf::Joystick::Z}};
		sfbind["JoystickR"] = {Input::JoystickAxis, {sf::Joystick::R}};
		sfbind["JoystickU"] = {Input::JoystickAxis, {sf::Joystick::U}};
		sfbind["JoystickV"] = {Input::JoystickAxis, {sf::Joystick::V}};
		sfbind["JoystickPovX"] = {Input::JoystickAxis, {sf::Joystick::PovX}};
		sfbind["JoystickPovY"] = {Input::JoystickAxis, {sf::Joystick::PovY}};
	}
}
