#pragma once
#include <unordered_map>
#include <string>

class KoreanMergeManager
{
private:
	static std::unordered_map<std::wstring, wchar_t> first;
	static std::unordered_map<std::wstring, wchar_t> middle;
	static std::unordered_map<std::wstring, wchar_t> last;
	static std::unordered_map<std::wstring, wchar_t> single_consonants;

private:
	static int ConsonantVowelConsonantMerge(const wchar_t m_first, const wchar_t m_middle, const wchar_t m_last);

public:
	static wchar_t* KoreanMerge(const wchar_t* p_english_text);
};
