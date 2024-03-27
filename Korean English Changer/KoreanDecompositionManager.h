#pragma once
#include <unordered_map>
#include <vector>
#include <wchar.h>

class KoreanDecompositionManager
{
private:
	static std::unordered_map<wchar_t, char> first;
	static std::unordered_map<wchar_t, char> middle1;
	static std::unordered_map<wchar_t, char> middle2;
	static std::unordered_map<wchar_t, char> last1;
	static std::unordered_map<wchar_t, char> last2;
	static std::unordered_map<wchar_t, char> single_consonants1;
	static std::unordered_map<wchar_t, char> single_consonants2;

public:
	static wchar_t* KoreanDecomposition(const wchar_t* p_korean_text);
};

