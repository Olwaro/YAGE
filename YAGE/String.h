#include <string>
#include <sstream>

namespace String
{
	template<typename ...Ts>
	std::string concat(Ts&&... args)
	{
		std::ostringstream oss;
		impl::__concat__(oss, args...);
		return oss.str();
	}

	namespace impl
	{
		template<typename T>
		void __concat__(std::ostringstream &oss, T&& arg)
		{
			oss << arg;
		}

		template<typename T, typename ...Ts>
		void __concat__(std::ostringstream &oss, T&& arg, Ts&&... args)
		{
			oss << arg;
			__concat__(oss, args...);
		}
	}
}
