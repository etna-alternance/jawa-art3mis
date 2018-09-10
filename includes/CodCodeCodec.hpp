#ifndef COD_CODE_CODEC_HPP_
# define COD_CODE_CODEC_HPP_

# include <iostream>
# include <vector>

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

# include "Engine.hpp"
# include "CodecRender.hpp"

class CodCodeCodec : public mysf::Engine
{
public:
  CodCodeCodec();
  CodCodeCodec(const CodCodeCodec &) = delete;
  CodCodeCodec & operator=(const CodCodeCodec &) = delete;
  virtual ~CodCodeCodec();

  virtual bool init(int ac, char ** av);
};

#endif // !COD_CODE_CODEC_HPP_
