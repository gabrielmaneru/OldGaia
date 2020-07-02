#pragma once

#define Extensions(...) static constexpr e_Extension m_extensions[]={__VA_ARGS__}

namespace Gaia {
	enum class e_Extension {
		none,
		begin,
		png,
		jpg,
		obj,
		level,
		mtl,
		end
	};
	inline e_Extension operator++(e_Extension&x);

	e_Extension get_extension(const std::string& path);

}