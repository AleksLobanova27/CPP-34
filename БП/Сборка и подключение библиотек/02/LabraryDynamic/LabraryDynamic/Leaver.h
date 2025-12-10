#pragma once
#include <string>

#ifdef LABRARYDYNAMIC_EXPORTS
#define LABRARYDYNAMIC_API __declspec(dllexport)
#else
#define LABRARYDYNAMIC_API __declspec(dllimport)
#endif
namespace NameGoodbye {
	class Leaver {
	public:
		LABRARYDYNAMIC_API std::string leave(const std::string& name) ;
	};
}