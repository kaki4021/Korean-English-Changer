#include "KoreanMergeManager.h"

std::unordered_map<std::string, char> KoreanMergeManager::first = { {"r", 0}, {"R", 1}, {"s", 2}, {"S", 2}, {"e", 3}, {"E", 4}, {"f", 5}, {"F", 5}, {"a", 6}, {"A", 6}, {"q", 7}, {"Q", 8}, {"t", 9}, {"T", 10}, {"d", 11}, {"D", 11}, {"w", 12}, {"W", 13}, {"c", 14}, {"C", 14}, {"z", 15}, {"Z", 15}, {"x", 16}, {"X", 16}, {"v", 17}, {"V", 17}, {"g", 18}, {"G", 18} };
std::unordered_map<std::string, char> KoreanMergeManager::middle = { {"k", 0}, {"K", 0}, {"o", 1}, {"i", 2}, {"I", 2}, {"O", 3}, {"j", 4}, {"J", 4}, {"p", 5}, {"u", 6}, {"U", 6}, {"P", 7}, {"h", 8}, {"H", 8}, {"hk", 9}, {"hK", 9}, {"Hk", 9}, {"HK", 9}, {"ho", 10}, {"Ho", 10}, {"hl", 11}, {"hL", 11}, {"Hl", 11}, {"HL", 11}, {"y", 12}, {"Y", 12}, {"n", 13}, {"N", 13}, {"nj", 14}, {"nJ", 14}, {"Nj", 14}, {"NJ", 14}, {"np", 15}, {"Np", 15}, {"nl", 16}, {"nL", 16}, {"Nl", 16}, {"NL", 16}, {"b", 17}, {"B", 17}, {"m", 18}, {"M", 18}, {"ml", 19}, {"mL", 19}, {"Ml", 19}, {"ML", 19}, {"l", 20}, {"L", 20} };
std::unordered_map<std::string, char> KoreanMergeManager::last = { {"r", 1}, {"R", 2}, {"rt", 3}, {"s", 4}, {"S", 4}, {"sw", 5}, {"Sw", 5}, {"sg", 6}, {"sG", 6}, {"Sg", 6}, {"SG", 6}, {"e", 7}, {"f", 8}, {"F", 8}, {"fr", 9}, {"Fr", 9}, {"fa", 10}, {"fA", 10}, {"Fa", 10}, {"FA", 10}, {"ft", 11}, {"Ft", 11}, {"fq", 12}, {"Fq", 12}, {"fx", 13}, {"fX", 13}, {"Fx", 13}, {"FX", 13}, {"fv", 14}, {"fV", 14}, {"Fv", 14}, {"FV", 14}, {"fg", 15}, {"fG", 15}, {"Fg", 15}, {"FG", 15}, {"a", 16}, {"A", 16}, {"q", 17}, {"qt", 18}, {"t", 19}, {"T", 20}, {"d", 21}, {"D", 21}, {"w", 22}, {"W", 22}, {"c", 23}, {"C", 23}, {"z", 24}, {"Z", 24}, {"x", 25}, {"X", 25}, {"v", 26}, {"V", 26}, {"g", 27}, {"G", 27} };
std::unordered_map<std::string, char> KoreanMergeManager::single_consonants = { {"r", 0}, {"R", 1}, {"rt", 2}, {"s", 3}, {"S", 3}, {"sw", 4}, {"Sw", 4}, {"sg", 5}, {"sG", 5}, {"Sg", 5}, {"SG", 5}, {"e", 6}, {"E", 7}, {"f", 8}, {"F", 8}, {"fr", 9}, {"Fr", 9}, {"fa", 10}, {"fA", 10}, {"Fa", 10}, {"FA", 10}, {"fq", 11}, {"Fq", 11}, {"ft", 12}, {"Ft", 12}, {"fx", 13}, {"fX", 13}, {"Fx", 13}, {"FX", 13}, {"fv", 14}, {"fV", 14}, {"Fv", 14}, {"FV", 14}, {"fg", 15}, {"fG", 15}, {"Fg", 15}, {"FG", 15}, {"a", 16}, { "A", 16 }, {"q", 17}, {"Q", 18}, { "qt", 19 }, {"t", 20}, {"T", 21}, {"d", 22}, {"D", 22}, {"w", 23}, {"W", 24}, {"c", 25}, {"C", 25}, {"z", 26}, {"Z", 26}, {"x", 27}, {"X", 27}, {"v", 28}, {"V", 28}, {"g", 29}, {"G", 29}};

int KoreanMergeManager::ConsonantVowelConsonantMerge(char m_first, char m_middle, char m_last)
{
	return 0xAC00 + (588 * m_first) + (28 * m_middle) + (m_last);
}

wchar_t* KoreanMergeManager::KoreanMerge(const char* p_english_text)
{
	std::vector<int> v_korean_text;

	std::string s_english_text = p_english_text;
	s_english_text += "000000";

	size_t reading_pos = 0;
	size_t s_english_text_len = s_english_text.length() - 6;

	char first_letter_num = 0;
	char middle_letter_num = 0;
	char last_letter_num = 0;

	while (reading_pos < s_english_text_len)
	{
		size_t start_reading_pos = reading_pos;
		size_t p_english_text_value = p_english_text[reading_pos];

		if (!(p_english_text_value >= 'A' && p_english_text_value <= 'Z') && !(p_english_text_value >= 'a' && p_english_text_value <= 'z'))
		{
			v_korean_text.push_back(p_english_text[reading_pos]);
			reading_pos += 1;
			continue;
		}
		
		std::string substr1 = s_english_text.substr(reading_pos, 1);
		std::string substr2 = s_english_text.substr(reading_pos, 2);
		first_letter_num = 50;
		if (first.find(substr1) != first.end())
		{
			first_letter_num = first.at(substr1);
			reading_pos += 1;
		}
		
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


		if (first_letter_num == 50)
		{
			v_korean_text.push_back(0x314f + middle_letter_num);
			continue;
		}
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

	size_t v_korean_text_size = v_korean_text.size();
	wchar_t* p_korean_text = new wchar_t[v_korean_text_size + 1];
	for (size_t i = 0; i < v_korean_text_size; i++)
	{
		p_korean_text[i] = v_korean_text[i];
	}
	p_korean_text[v_korean_text_size] = '\0';

	return p_korean_text;
}
