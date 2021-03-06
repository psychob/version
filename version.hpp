//
// file autogenerated by version utility
//

#ifndef VERSION_FILE_HPP_AUTOGENERATED_1557353030
#define VERSION_FILE_HPP_AUTOGENERATED_1557353030 1557353030

/// @brief Major version of program as int
#define VERSION_CURRENT_VERSION_MAJOR			(1)
/// @brief Major version of program as string
#define VERSION_CURRENT_VERSION_MAJOR_STR		"1"
/// @brief Minor version of program as int
#define VERSION_CURRENT_VERSION_MINOR			(2)
/// @brief Minor version of program as string
#define VERSION_CURRENT_VERSION_MINOR_STR		"2"
/// @brief Patch version of program as int
#define VERSION_CURRENT_VERSION_PATCH			(0)
/// @brief Patch version of program as string
#define VERSION_CURRENT_VERSION_PATCH_STR		"0"
/// @brief Build version of program as int
#define VERSION_CURRENT_VERSION_BUILD			(0)
/// @brief Build version of program as string
#define VERSION_CURRENT_VERSION_BUILD_STR		"0"
/// @brief All build count version of program as int
#define VERSION_CURRENT_VERSION_BUILD_COUNT			(110)
/// @brief All build count version of program as string
#define VERSION_CURRENT_VERSION_BUILD_COUNT_STR		"110"

/// @brief Version encoded in "window" format
///
/// Windows format is composed from four numbers divided by dot. If you disabled some components, they
/// will be replaced by zeros.
#define VERSION_CURRENT_VERSION_ENCODED_WIN			VERSION_CURRENT_VERSION_MAJOR_STR "." VERSION_CURRENT_VERSION_MINOR_STR "." VERSION_CURRENT_VERSION_PATCH_STR "." VERSION_CURRENT_VERSION_BUILD_STR

/// @brief Version encoded in single 4 byte int
#define VERSION_CURRENT_VERSION_ENCODED_INT			(0x1020000U)

/// @brief Version encoded in single 8 byte int
#define VERSION_CURRENT_VERSION_ENCODED_LONG		(0x1000200000000ULL)

/// @brief Pretty version
#define VERSION_CURRENT_VERSION_PRETTY				"1.2"

#ifndef VERSION_VERSION_API
	#define VERSION_VERSION_API
#endif // VERSION_VERSION_API

#ifndef VERSION_VERSION_VISIBILITY
	#define VERSION_VERSION_VISIBILITY
#endif // VERSION_VERSION_VISIBILITY

#ifndef VERSION_VERSION_CONST
	#ifdef __GNUC__
		#define VERSION_VERSION_CONST __attribute__((const))
	#else
		#define VERSION_VERSION_CONST
	#endif // ___GNUC__
#endif // VERSION_VERSION_CONST

namespace version
{
	VERSION_VERSION_API VERSION_VERSION_VISIBILITY int major() VERSION_VERSION_CONST;
	VERSION_VERSION_API VERSION_VERSION_VISIBILITY int minor() VERSION_VERSION_CONST;
	VERSION_VERSION_API VERSION_VERSION_VISIBILITY int patch() VERSION_VERSION_CONST;
	VERSION_VERSION_API VERSION_VERSION_VISIBILITY int build() VERSION_VERSION_CONST;

	VERSION_VERSION_API VERSION_VERSION_VISIBILITY const char * pretty() VERSION_VERSION_CONST;
	VERSION_VERSION_API VERSION_VERSION_VISIBILITY int encoded_int() VERSION_VERSION_CONST;
	VERSION_VERSION_API VERSION_VERSION_VISIBILITY long long encoded_long() VERSION_VERSION_CONST;
}

#endif // VERSION_FILE_HPP_AUTOGENERATED_1557353030
