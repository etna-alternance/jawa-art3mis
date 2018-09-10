#include "Art3mis.hpp"

int main(int ac, char ** av)
{
  Art3mis codec;

  if (codec.init(ac, av) == false)
    return 1;
  return codec.run();
}
