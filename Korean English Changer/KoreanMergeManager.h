#pragma once
#include <unordered_map>
#include <string>

class KoreanMergeManager
{
private:
	static std::unordered_map<std::string, char> first;
	static std::unordered_map<std::string, char> middle;
	static std::unordered_map<std::string, char> last;
	static std::unordered_map<std::string, char> single_consonants;

private:
	static int ConsonantVowelConsonantMerge(char m_first, char m_middle, char m_last);

public:
	static wchar_t* KoreanMerge(const char* p_english_text);
};
