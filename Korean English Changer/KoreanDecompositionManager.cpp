#include "KoreanDecompositionManager.h"

//한글 분해 저장
std::unordered_map<wchar_t, char> KoreanDecompositionManager::first = { {0, 'r'}, {1, 'R'}, {2, 's'}, {3, 'e'}, {4, 'E'}, {5, 'f'}, {6, 'a'}, {7, 'q'}, {8, 'Q'}, {9, 't'}, {10, 'T'}, {11, 'd'}, {12, 'w'}, {13, 'W'}, {14, 'c'}, {15, 'z'}, {16, 'x'}, {17, 'v'}, {18, 'g'} };
std::unordered_map<wchar_t, char> KoreanDecompositionManager::middle1 = { {0 , 'k'}, {1 ,'o'}, {2, 'i'}, {3, 'O'}, {4, 'j'}, {5, 'p'}, {6, 'u'}, {7, 'P'}, {8, 'h'}, {9, 'h'}, {10, 'h'}, {11, 'h'}, {12, 'y'}, {13, 'n'}, {14, 'n'}, {15, 'n'}, {16, 'n'}, {17, 'b'}, {18, 'm'}, {19, 'm'}, {20, 'l'}};
std::unordered_map<wchar_t, char> KoreanDecompositionManager::middle2 = { {9, 'k'}, {10, 'o'}, {11, 'l'}, {14, 'j'}, {15, 'p'}, {16, 'l'}, {19, 'l'} };
std::unordered_map<wchar_t, char> KoreanDecompositionManager::last1 = { {1, 'r'}, {2, 'R'}, {3, 'r'}, {4, 's'}, {5, 's'}, {6, 's'}, {7, 'e'}, {8, 'f'}, {9, 'f'}, {10, 'f'}, {11, 'f'}, {12, 'f'}, {13, 'f'}, {14, 'f'}, {15, 'f'}, {16, 'a'}, {17, 'q'}, {18, 'q'}, {19, 't'}, {20, 'T'}, {21, 'd'}, {22, 'w'}, {23, 'c'}, {24, 'z'}, {25, 'x'}, {26, 'v'}, {27, 'g'} };
std::unordered_map<wchar_t, char> KoreanDecompositionManager::last2 = { {3, 't'}, {5, 'w'}, {6, 'g'}, {9, 'r'}, {10, 'a'}, {11, 't'}, {12, 'q'}, {13, 'x'}, {14, 'v'}, {15, 'g'}, {18, 't'} };
std::unordered_map<wchar_t, char> KoreanDecompositionManager::single_consonants1 = { {0, 'r'}, {1, 'R'}, {2, 'r'}, {3, 's'}, {4, 's'}, {5, 's'}, {6, 'e'}, {7, 'E'}, {8, 'f'}, {9, 'f'}, {10, 'f'}, {11, 'f'}, {12, 'f'}, {13, 'f'}, {14, 'f'}, {15, 'f'}, {16, 'a'},  {17, 'q'}, {18, 'Q'}, {19, 'q'}, {20, 't'}, {21, 'T'}, {22, 'd'}, {23, 'w'}, {24, 'W'}, {25, 'c'}, {26, 'z'}, {27, 'x'}, {28, 'v'}, {29, 'g'} };
std::unordered_map<wchar_t, char> KoreanDecompositionManager::single_consonants2 = { {2, 't'}, {4, 'w'}, {5, 'g'}, {9, 'r'}, {10, 'a'}, {11, 'q'}, {12, 't'}, {13, 'x'}, {14, 'v'}, {15, 'g'}, {19, 't'} };

wchar_t* KoreanDecompositionManager::KoreanDecomposition(const wchar_t* p_korean_text)
{
	std::vector<int> v_english_text;

	size_t p_korean_text_len = wcslen(p_korean_text);

	for (size_t i = 0; i < p_korean_text_len; i++)
	{
		wchar_t p_korean_text_value = p_korean_text[i];

		//완전한 한글
		if (p_korean_text_value >= 0xAC00 && p_korean_text_value <= 0xD7A3)
		{
			p_korean_text_value -= 0xAC00;

			//초성
			wchar_t first_letter_num = p_korean_text_value / 588;
			v_english_text.push_back(first.at(first_letter_num));

			//중성
			wchar_t middle_letter_num = (p_korean_text_value - (first_letter_num * 588)) / 28;
			v_english_text.push_back(middle1.at(middle_letter_num));
			if (middle2.find(middle_letter_num) != middle2.end())
			{
				v_english_text.push_back(middle2.at(middle_letter_num));
			}

			//종성
			wchar_t last_letter_num = p_korean_text_value - (first_letter_num * 588) - (middle_letter_num * 28);
			if (last_letter_num != 0)
			{
				v_english_text.push_back(last1.at(last_letter_num));
				if (last2.find(last_letter_num) != last2.end())
				{
					v_english_text.push_back(last2.at(last_letter_num));
				}
			}
		}
		//자음만
		else if (p_korean_text_value >= 0x3131 && p_korean_text_value <= 0x314E)
		{
			p_korean_text_value -= 0x3131;
			v_english_text.push_back(single_consonants1.at(p_korean_text_value));
			if (single_consonants2.find(p_korean_text_value) != single_consonants2.end())
			{
				v_english_text.push_back(single_consonants2.at(p_korean_text_value));
			}
		}
		//모음만
		else if (p_korean_text_value >= 0x314F && p_korean_text_value <= 0x3163)
		{
			p_korean_text_value -= 0x314F;
			v_english_text.push_back(middle1.at(p_korean_text_value));
			if (middle2.find(p_korean_text_value) != middle2.end())
			{
				v_english_text.push_back(middle2.at(p_korean_text_value));
			}
		}
		//한글 아님
		else
		{
			v_english_text.push_back(p_korean_text_value);
		}
	}


	//vector에서 wchar_t로 변환
	size_t v_english_text_size = v_english_text.size();
	wchar_t* p_english_text = new wchar_t[v_english_text_size + 1];
	for (size_t i = 0; i < v_english_text_size; i++)
	{
		p_english_text[i] = v_english_text[i];
	}
	p_english_text[v_english_text_size] = '\0';

	return p_english_text;
}
