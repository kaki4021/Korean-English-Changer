#include "KoreanMergeManager.h"


//한글 조합 저장
std::unordered_map<std::wstring, wchar_t> KoreanMergeManager::first = { {L"r", 0}, {L"R", 1}, {L"s", 2}, {L"S", 2}, {L"e", 3}, {L"E", 4}, {L"f", 5}, {L"F", 5}, {L"a", 6}, {L"A", 6}, {L"q", 7}, {L"Q", 8}, {L"t", 9}, {L"T", 10}, {L"d", 11}, {L"D", 11}, {L"w", 12}, {L"W", 13}, {L"c", 14}, {L"C", 14}, {L"z", 15}, {L"Z", 15}, {L"x", 16}, {L"X", 16}, {L"v", 17}, {L"V", 17}, {L"g", 18}, {L"G", 18} };
std::unordered_map<std::wstring, wchar_t> KoreanMergeManager::middle = { {L"k", 0}, {L"K", 0}, {L"o", 1}, {L"i", 2}, {L"I", 2}, {L"O", 3}, {L"j", 4}, {L"J", 4}, {L"p", 5}, {L"u", 6}, {L"U", 6}, {L"P", 7}, {L"h", 8}, {L"H", 8}, {L"hk", 9}, {L"hK", 9}, {L"Hk", 9}, {L"HK", 9}, {L"ho", 10}, {L"Ho", 10}, {L"hl", 11}, {L"hL", 11}, {L"Hl", 11}, {L"HL", 11}, {L"y", 12}, {L"Y", 12}, {L"n", 13}, {L"N", 13}, {L"nj", 14}, {L"nJ", 14}, {L"Nj", 14}, {L"NJ", 14}, {L"np", 15}, {L"Np", 15}, {L"nl", 16}, {L"nL", 16}, {L"Nl", 16}, {L"NL", 16}, {L"b", 17}, {L"B", 17}, {L"m", 18}, {L"M", 18}, {L"ml", 19}, {L"mL", 19}, {L"Ml", 19}, {L"ML", 19}, {L"l", 20}, {L"L", 20} };
std::unordered_map<std::wstring, wchar_t> KoreanMergeManager::last = { {L"r", 1}, {L"R", 2}, {L"rt", 3}, {L"s", 4}, {L"S", 4}, {L"sw", 5}, {L"Sw", 5}, {L"sg", 6}, {L"sG", 6}, {L"Sg", 6}, {L"SG", 6}, {L"e", 7}, {L"f", 8}, {L"F", 8}, {L"fr", 9}, {L"Fr", 9}, {L"fa", 10}, {L"fA", 10}, {L"Fa", 10}, {L"FA", 10}, {L"ft", 11}, {L"Ft", 11}, {L"fq", 12}, {L"Fq", 12}, {L"fx", 13}, {L"fX", 13}, {L"Fx", 13}, {L"FX", 13}, {L"fv", 14}, {L"fV", 14}, {L"Fv", 14}, {L"FV", 14}, {L"fg", 15}, {L"fG", 15}, {L"Fg", 15}, {L"FG", 15}, {L"a", 16}, {L"A", 16}, {L"q", 17}, {L"qt", 18}, {L"t", 19}, {L"T", 20}, {L"d", 21}, {L"D", 21}, {L"w", 22}, {L"W", 22}, {L"c", 23}, {L"C", 23}, {L"z", 24}, {L"Z", 24}, {L"x", 25}, {L"X", 25}, {L"v", 26}, {L"V", 26}, {L"g", 27}, {L"G", 27} };
std::unordered_map<std::wstring, wchar_t> KoreanMergeManager::single_consonants = { {L"r", 0}, {L"R", 1}, {L"rt", 2}, {L"s", 3}, {L"S", 3}, {L"sw", 4}, {L"Sw", 4}, {L"sg", 5}, {L"sG", 5}, {L"Sg", 5}, {L"SG", 5}, {L"e", 6}, {L"E", 7}, {L"f", 8}, {L"F", 8}, {L"fr", 9}, {L"Fr", 9}, {L"fa", 10}, {L"fA", 10}, {L"Fa", 10}, {L"FA", 10}, {L"fq", 11}, {L"Fq", 11}, {L"ft", 12}, {L"Ft", 12}, {L"fx", 13}, {L"fX", 13}, {L"Fx", 13}, {L"FX", 13}, {L"fv", 14}, {L"fV", 14}, {L"Fv", 14}, {L"FV", 14}, {L"fg", 15}, {L"fG", 15}, {L"Fg", 15}, {L"FG", 15}, {L"a", 16}, {L"A", 16 }, {L"q", 17}, {L"Q", 18}, {L"qt", 19 }, {L"t", 20}, {L"T", 21}, {L"d", 22}, {L"D", 22}, {L"w", 23}, {L"W", 24}, {L"c", 25}, {L"C", 25}, {L"z", 26}, {L"Z", 26}, {L"x", 27}, {L"X", 27}, {L"v", 28}, {L"V", 28}, {L"g", 29}, {L"G", 29} };

int KoreanMergeManager::ConsonantVowelConsonantMerge(const wchar_t m_first, const wchar_t m_middle, const wchar_t m_last)
{
	return 0xAC00 + (588 * m_first) + (28 * m_middle) + (m_last);
}

wchar_t* KoreanMergeManager::KoreanMerge(const wchar_t* p_english_text)
{
	std::vector<int> v_korean_text;

	std::wstring s_english_text = p_english_text;
	s_english_text += L"000000";

	size_t reading_pos = 0;
	size_t s_english_text_len = s_english_text.length() - 6;

	char first_letter_num = 0;
	char middle_letter_num = 0;
	char last_letter_num = 0;

	while (reading_pos < s_english_text_len)
	{
		size_t start_reading_pos = reading_pos;
		size_t p_english_text_value = p_english_text[reading_pos];


		//영어 아니면 제외
		if (!(p_english_text_value >= 'A' && p_english_text_value <= 'Z') && !(p_english_text_value >= 'a' && p_english_text_value <= 'z'))
		{
			v_korean_text.push_back(p_english_text_value);
			reading_pos += 1;
			continue;
		}
		

		//초성
		std::wstring substr1 = s_english_text.substr(reading_pos, 1);
		std::wstring substr2 = s_english_text.substr(reading_pos, 2);
		first_letter_num = 50;
		if (first.find(substr1) != first.end())
		{
			first_letter_num = first.at(substr1);
			reading_pos += 1;
		}
		

		//중성
		substr1 = s_english_text.substr(reading_pos, 1);
		substr2 = s_english_text.substr(reading_pos, 2);
		middle_letter_num = 50;
		if (middle.find(substr2) != middle.end())
		{
			middle_letter_num = middle.at(substr2);
			reading_pos += 2;
		}
		else if (middle.find(substr1) != middle.end())
		{
			middle_letter_num = middle.at(substr1);
			reading_pos += 1;
		}


		//초성 없으면 모음으로 처리
		if (first_letter_num == 50)
		{
			v_korean_text.push_back(0x314f + middle_letter_num);
			continue;
		}

		//중성 없으면 자음으로 처리
		if (middle_letter_num == 50)
		{
			reading_pos = start_reading_pos;
			substr1 = s_english_text.substr(reading_pos, 1);
			substr2 = s_english_text.substr(reading_pos, 2);
			char single_consonant_num = 0;
			if (middle.find(s_english_text.substr(reading_pos + 2, 1)) != middle.end())
			{
				if (single_consonants.find(substr1) != single_consonants.end())
				{
					single_consonant_num = single_consonants.at(substr1);
					reading_pos += 1;
				}
			}
			else
			{
				if (single_consonants.find(substr2) != single_consonants.end())
				{
					single_consonant_num = single_consonants.at(substr2);
					reading_pos += 2;
				}
				else if (single_consonants.find(substr1) != single_consonants.end())
				{
					single_consonant_num = single_consonants.at(substr1);
					reading_pos += 1;
				}
			}
			v_korean_text.push_back(0x3131 + single_consonant_num);
			continue;
		}


		//종성
		substr1 = s_english_text.substr(reading_pos, 1);
		substr2 = s_english_text.substr(reading_pos, 2);
		last_letter_num = 0;
		if (middle.find(s_english_text.substr(reading_pos + 1, 1)) != middle.end())
		{
			//nothing
		}
		else if (middle.find(s_english_text.substr(reading_pos + 2, 1)) != middle.end())
		{
			if (last.find(substr1) != last.end())
			{
				last_letter_num = last.at(substr1);
				reading_pos += 1;
			}
		}
		else
		{
			if (last.find(substr2) != last.end())
			{
				last_letter_num = last.at(substr2);
				reading_pos += 2;
			}
			else if (last.find(substr1) != last.end())
			{
				last_letter_num = last.at(substr1);
				reading_pos += 1;
			}
		}

		v_korean_text.push_back(ConsonantVowelConsonantMerge(first_letter_num, middle_letter_num, last_letter_num));
	}


	//vector 에서 wchar_t로 변환
	size_t v_korean_text_size = v_korean_text.size();
	wchar_t* p_korean_text = new wchar_t[v_korean_text_size + 1];
	for (size_t i = 0; i < v_korean_text_size; i++)
	{
		p_korean_text[i] = v_korean_text[i];
	}
	p_korean_text[v_korean_text_size] = '\0';

	return p_korean_text;
}
