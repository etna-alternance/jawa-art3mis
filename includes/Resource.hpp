#ifndef RESOURCE_HPP_
# define RESOURCE_HPP_

namespace Resource
{
  namespace Texture
  {
    enum ID
      {
	None = -1,
	First = 0,
	Codec = First,
	Snake,
	Otacon,
	Campbell,
	Meryl,
	Naomi,
	Mei,
	Miller,
	Wolf,
	Jim,
	PTT,
	Fourteen,
	Dot,
	Digits,
	ArrowL,
	ArrowR,
	Lines,
	Size
      };
  }

  namespace Sound
  {
    enum ID
      {
	None = -1,
	First = 0,
	Ringtone = First,
	Answer,
	Size
      };
  }

  namespace Font
  {
    enum ID
      {
	None = -1,
	First = 0,
	Ayar = First,
	Size
      };
  }
}

#endif // !RESOURCE_HPP_
