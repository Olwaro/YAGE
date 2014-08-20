#pragma once

#include <string>

namespace Debug
{
	void warning(const std::string& message);
	void error(const std::string& message);
	void die(const std::string& message);
	void check_assert(bool assertion, const std::string& message);
}
