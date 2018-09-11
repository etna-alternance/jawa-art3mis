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
			Talk,
			Size
		};
	}

	namespace Font
	{
		enum ID
		{
			None = -1,
			First = 0,
			Orbitron = First,
			Size
		};
	}

	namespace Sound
	{
		enum ID
		{
			None = -1,
			First = 0,
			Subdivisions = First,
			Size
		};
	}
}

#endif // !RESOURCE_HPP_
