#include "CodCodeCodec.hpp"

int main(int ac, char ** av)
{
  CodCodeCodec codec;

  if (codec.init(ac, av) == false)
    return 1;
  return codec.run();
}
