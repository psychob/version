#include "version.hpp"

namespace version
{
	int major()
	{
		return VERSION_CURRENT_VERSION_MAJOR;
	}

	int minor()
	{
		return VERSION_CURRENT_VERSION_MINOR;
	}

	int patch()
	{
		return VERSION_CURRENT_VERSION_PATCH;
	}

	int build()
	{
		return VERSION_CURRENT_VERSION_BUILD;
	}

	const char * pretty()
	{
		return VERSION_CURRENT_VERSION_PRETTY;
	}

	int encoded_int()
	{
		return VERSION_CURRENT_VERSION_ENCODED_INT;
	}

	long long encoded_long()
	{
		return VERSION_CURRENT_VERSION_ENCODED_LONG;
	}
}
