#include "stdafx.h"
#include "CppUnitTest.h"
#include "se_word_chain.hpp"
#include "se_word_chain_utils.hpp"
#include "se_word_chain_core.hpp"
#include "se_word_chain_core.cpp"
#include "se_word_chain_utils.hpp"
#include "se_word_chain_utils.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using CCmap = unordered_map<char, unordered_map<char, WordMapElement> >;
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Test_tolower)
		{
			//TEST  tolower
			string ret;
			string test1 = "HELLO";
			ret = tolower(test1);
			Assert::AreEqual(ret, string("hello"));

			string test2 = "HellO!";
			ret = tolower(test2);
			Assert::AreEqual(ret, string("hello!"));

			string test3 = "_hello_There";
			ret = tolower(test3);
			Assert::AreEqual(ret, string("_hello_there"));
		}

		TEST_METHOD(Test_ExtractWord)
		{
			//TEST  ExtractWord
			WordChainError error1;
			string input_text1 = "_this is      a!@#$test of0extract!word...... ";
			vector<string>  input_buffer1;
			vector<string> result1 = { "this","is","a","test","of","extract","word" };
			ExtractWord(input_text1, input_buffer1,error1);
			Assert::AreEqual(result1.size(), input_buffer1.size());
			for (int i = 0; i < result1.size(); i++) {
				Assert::AreEqual(result1[i], input_buffer1[i]);
			}

			WordChainError error2;
			string input_text2 = "_this___is___another======test of extract[][][]word. ";
			vector<string>  input_buffer2;
			vector<string> result2 = { "this","is","another","test","of","extract","word" };
			ExtractWord(input_text2, input_buffer2,error2);
			Assert::AreEqual(result2.size(), input_buffer2.size());
			for (int i = 0; i < result2.size(); i++) {
				Assert::AreEqual(result2[i], input_buffer2[i]);
			}

			WordChainError error3;
			string input_text3 = "_[][][]....";
			vector<string>  input_buffer3;
			vector<string> result3 = { };
			ExtractWord(input_text3, input_buffer3,error3);
			Assert::AreEqual(result3.size(), input_buffer3.size());
			for (int i = 0; i < result3.size(); i++) {
				Assert::AreEqual(result3[i], input_buffer3[i]);
			}
		}

		TEST_METHOD(Test_OutputTransform)
		{
			//TEST  OutputTransform
			WordChainError error1;
			string output_text1 = "";
			string result1 = "this\nis\na\ntest\nof\nextract\nword\n";
			vector<string> output_buffer1 = { "this","is","a","test","of","extract","word" };
			OutputTransform(output_buffer1, output_text1,error1);
			Assert::AreEqual(result1, output_text1);

			WordChainError error2;
			string output_text2 = "";
			string result2 = "";
			vector<string> output_buffer2 = {  };
			OutputTransform(output_buffer2, output_text2,error2);
			Assert::AreEqual(result2, output_text2);
		}

		TEST_METHOD(Test_Class_Word)
		{
			//TEST  Class_Word
			Word test1 = Word("a");
			Assert::AreEqual(test1.GetHead(), 'a');
			Assert::AreEqual(test1.GetTail(), 'a');
			Assert::AreEqual(test1.GetWord(), string("a"));
			Assert::AreEqual(test1.GetKey(), string("aa"));

			Word test2 = Word("phycho");
			Assert::AreEqual(test2.GetHead(), 'p');
			Assert::AreEqual(test2.GetTail(), 'o');
			Assert::AreEqual(test2.GetWord(), string("phycho"));
			Assert::AreEqual(test2.GetKey(), string("po"));
		}

		TEST_METHOD(Test_Class_WordMapElement)
		{
			//TEST  Class_WordMapElement
			Word test1 = "a";
			WordMapElement testElement1 = WordMapElement(test1);
			Assert::AreEqual(testElement1.GetLongestLen(), 1);
			Assert::AreEqual(testElement1.GetLongestWord(), string("a"));

			Word test2 = "phycho";
			WordMapElement testElement2 = WordMapElement(test2);
			Assert::AreEqual(testElement2.GetLongestLen(), 6);
			Assert::AreEqual(testElement2.GetLongestWord(), string("phycho"));
		}

		TEST_METHOD(Test_Class_WordMapElement_Method)
		{
			//TEST  Class_WordMapElement_Method: Append/GetLongestLen/GetLongestWord/GetSetSize/ToString
			Word test1 = "a";
			WordMapElement testElement1 = WordMapElement(test1);
			Assert::AreEqual(testElement1.GetLongestLen(), 1);
			Assert::AreEqual(testElement1.GetLongestWord(), string("a"));
			testElement1.AppendWord("abc");
			Assert::AreEqual(testElement1.GetLongestLen(), 3);
			Assert::AreEqual(testElement1.GetLongestWord(), string("abc"));
			testElement1.AppendWord("ab");
			Assert::AreEqual(testElement1.GetLongestLen(), 3);
			Assert::AreEqual(testElement1.GetLongestWord(), string("abc"));
			Assert::AreEqual(testElement1.GetSetSize(), 3);
			Assert::AreEqual(testElement1.ToString(), string("abcaba"));

			Word test2 = "phycho";
			WordMapElement testElement2 = WordMapElement(test2);
			Assert::AreEqual(testElement2.GetLongestLen(), 6);
			Assert::AreEqual(testElement2.GetLongestWord(), string("phycho"));
			testElement2.AppendWord("phy");
			Assert::AreEqual(testElement2.GetLongestLen(), 6);
			Assert::AreEqual(testElement2.GetLongestWord(), string("phycho"));
			Assert::AreEqual(testElement2.GetSetSize(), 2);
			Assert::AreEqual(testElement2.ToString(), string("phychophy"));
			testElement2.AppendWord("phyphychocho");
			Assert::AreEqual(testElement2.GetLongestLen(), 12);
			Assert::AreEqual(testElement2.GetLongestWord(), string("phyphychocho"));
			Assert::AreEqual(testElement2.ToString(), string("phyphychochophychophy"));
		}

		TEST_METHOD(Test_CheckCircle)
		{
			//TEST  CheckCircle
			CCmap wordmap1;
			WordChainError error1;
			vector<string> test1 = { "this","map","does","not","have","circle" };
			GenerateWordMap(test1, wordmap1,error1);
			bool hascircle1;
			CheckCircle(wordmap1, hascircle1,error1);
			Assert::AreEqual(hascircle1, false);

			CCmap wordmap2;
			WordChainError error2;
			vector<string> test2 = { "this","map","should","have","circles","doesnt","it"};
			GenerateWordMap(test2, wordmap2,error2);
			bool hascircle2;
			CheckCircle(wordmap2, hascircle2,error2);
			Assert::AreEqual(hascircle2, true);

			CCmap wordmap3;
			WordChainError error3;
			vector<string> test3 = { "this","map","should","not","have","circle","algebra","TNT"};
			GenerateWordMap(test3, wordmap3,error3);
			bool hascircle3;
			CheckCircle(wordmap3, hascircle3,error3);
			Assert::AreEqual(hascircle3, false);

			CCmap wordmap4;
			WordChainError error4;
			vector<string> test4 = { "this","map","should","not","have","circle","algebra","TNT","alalgegebrabra" };
			GenerateWordMap(test4, wordmap4,error4);
			bool hascircle4;
			CheckCircle(wordmap4, hascircle4,error4);
			Assert::AreEqual(hascircle4, true);
		}

		TEST_METHOD(Test_Class_DistanceElement)
		{
			//TEST  Class_DistanceElement
			LongestWordChainType type1 = letter_longest;
			DistanceElement testElement1 = DistanceElement(type1);
			Assert::AreEqual(testElement1.GetDistance(), 0);

			LongestWordChainType type2 = word_longest;
			DistanceElement testElement2 = DistanceElement(type2);
			Assert::AreEqual(testElement2.GetDistance(), 0);
		}

		TEST_METHOD(Test_Class_DistanceElement_Method)
		{
			//TEST  Class_DistanceElement_Method: SetDistance/GetDistance/SetWordChain/CopyWordBuffer/ToString
			LongestWordChainType type1 = letter_longest;
			DistanceElement testElement1 = DistanceElement(type1);
			Assert::AreEqual(testElement1.GetDistance(), 0);
			vector<string> input1 = { "a","test","of","it" };
			vector<string> output1;
			testElement1.SetWordChain(input1);
			testElement1.CopyWordBuffer(output1);
			for (int i = 0; i < input1.size(); i++) {
				Assert::AreEqual(output1[i], input1[i]);
			}
			testElement1.SetDistance(6);
			Assert::AreEqual(testElement1.GetDistance(), 6);
			Assert::AreEqual(testElement1.ToString(), string("a-test-of-it"));

			LongestWordChainType type2 = word_longest;
			DistanceElement testElement2 = DistanceElement(type2);
			Assert::AreEqual(testElement2.GetDistance(), 0);
			vector<string> input2 = { "another","test","of","it" };
			vector<string> output2;
			testElement2.SetWordChain(input2);
			testElement2.CopyWordBuffer(output2);
			for (int i = 0; i < input2.size(); i++) {
				Assert::AreEqual(output2[i], input2[i]);
			}
			testElement2.SetDistance(2);
			Assert::AreEqual(testElement2.GetDistance(), 2);
			Assert::AreEqual(testElement2.ToString(), string("another-test-of-it"));
		}
	
		TEST_METHOD(Test_GenerateWordMap)
		{
			//Test GenerateWordMap

			CCmap test_word_map;
			WordChainError error;
			vector<string> input_buffer = { "algebra","apple","zoo","elephant","under","fox","dog","moon","leaf","trick","pseudopseudohypoparathyroidism" };
			GenerateWordMap(input_buffer, test_word_map,error);
			Assert::AreEqual(int(test_word_map.size()), 10);
			auto iter = test_word_map.find('a');
			Assert::AreEqual(int(iter->second.size()), 2);
			iter = test_word_map.find('z');
			Assert::AreEqual(int(iter->second.size()), 1);
			iter = test_word_map.find('e');
			Assert::AreEqual(int(iter->second.size()), 1);
		}

		TEST_METHOD(Test_Class_NaiveSearch_Method)
		{
			//Test Class_NaiveSearch_Method: DfsSearch/Search/LookUp
			CCmap test_word_map;
			WordChainError error;
			vector<string> input_buffer = { "algebra","apple","zoo","elephant","under","fox","dog","moon","leaf","trick","pseudopseudohypoparathyroidism" };
			GenerateWordMap(input_buffer, test_word_map,error);
			SearchInterface* handle_search1 = NULL;
			LongestWordChainType type1 = word_longest;
			handle_search1 = new NaiveSearch(test_word_map, type1);
			handle_search1->Search();
			vector<string> output;
			vector<string> result1 = { "algebra","apple","elephant","trick" };
			vector<string> result2 = { "elephant","trick" };
			vector<string> result3 = { "pseudopseudohypoparathyroidism","moon" };
			vector<string> result4 = { "dog" };
			handle_search1->LookUp(output, NO_ASSIGN_HEAD, NO_ASSIGN_TAIL,error);
			for (int i = 0; i < output.size(); i++) {
				Assert::AreEqual(output[i], result1[i]);
			}
			handle_search1->LookUp(output, 'e', NO_ASSIGN_TAIL,error);
			for (int i = 0; i < output.size(); i++) {
				Assert::AreEqual(output[i], result2[i]);
			}
			handle_search1->LookUp(output, NO_ASSIGN_HEAD, 'n',error);
			for (int i = 0; i < output.size(); i++) {
				Assert::AreEqual(output[i], result3[i]);
			}
			handle_search1->LookUp(output, 'd', 'g',error);
			for (int i = 0; i < output.size(); i++) {
				Assert::AreEqual(output[i], result4[i]);
			}
			SearchInterface* handle_search2 = NULL;
			LongestWordChainType type2 = letter_longest;
			handle_search2 = new NaiveSearch(test_word_map, type2);
			handle_search2->Search();
			handle_search2->LookUp(output, NO_ASSIGN_HEAD, NO_ASSIGN_TAIL,error);
			for (int i = 0; i < output.size(); i++) {
				Assert::AreEqual(output[i], result3[i]);
			}
		}
	
		TEST_METHOD(Test_Calculate)
		{
			//Test Calculate: include CalculateLongestChain/ChainSearch
			WordChainError error;
			string input_text ="Algebra))Apple 123Zoo Elephant  Under  Fox_Dog-Moon Leaf`;;Trick Pseudopseudohypoparathyroidism";
			string output_text1 = "";
			LongestWordChainType type1 = word_longest;
			Calculate(input_text, output_text1, type1, NO_ASSIGN_HEAD, NO_ASSIGN_TAIL, false,error);
			string result1 = "algebra\napple\nelephant\ntrick\n";
			Assert::AreEqual(result1, output_text1);
			string output_text2 = "";
			LongestWordChainType type2 = letter_longest;
			Calculate(input_text, output_text2, type2, NO_ASSIGN_HEAD, NO_ASSIGN_TAIL, false,error);
			string result2 = "pseudopseudohypoparathyroidism\nmoon\n";
			Assert::AreEqual(result2, output_text2);
			string input_text_ring = "Algebra))Apple aaaaa 123Zoo Elephant  Under  Fox_Dog-Moon Leaf`;;Trick Pseudopseudohypoparathyroidism";
			string output_text3 = "";
			string result3 = "algebra\naaaaa\napple\nelephant\ntrick\n";
			LongestWordChainType type3 = word_longest;
			Calculate(input_text_ring, output_text3, type3, NO_ASSIGN_HEAD, NO_ASSIGN_TAIL, true, error);
			Assert::AreEqual(result3, output_text3);
		}

		TEST_METHOD(Test_Error)
		{
			WordChainError error1;
			string input_text1 = "Algebra))Apple aaaaa 123Zoo Elephant  Under  Fox_Dog-Moon Leaf`;;Trick Pseudopseudohypoparathyroidism";
			string output_text1 = "";
			string errortext1;
			LongestWordChainType type1 = word_longest;
			Calculate(input_text1, output_text1, type1, NO_ASSIGN_HEAD, NO_ASSIGN_TAIL,false, error1);
			errortext1 = error1.ToString();
			Assert::AreEqual(errortext1,string("Error Type: input has circle but not enable circle\nError Content: Error Type: input has circle but not enable circle\n"));

			WordChainError error2;
			string input_text2 = "Algebra Zoo";
			string output_text2 = "";
			string errortext2;
			LongestWordChainType type2 = word_longest;
			Calculate(input_text2, output_text2, type2, 'i', NO_ASSIGN_TAIL, false, error2);
			errortext2 = error2.ToString();
			Assert::AreEqual(errortext2, string("Error Type: no available word chain\nError Content: no available word chain for head(i) and tail(0)\n"));

			std::ifstream in("notexist.txt");
			std::stringstream buffer1;
			WordChainError error3;
			if (!in.is_open()) {
				char buffer1[MAX_BUFFER_SIZE];
				sprintf(buffer1, "Error Type: can't open input file\n");
				string error_content(buffer1);
				int error_code = SE_ERROR_OPENING_INPUT_FILE;
				error3.AppendInfo(error_code, error_content);
			}
			string errortext3 = error3.ToString();
			Assert::AreEqual(errortext3, string("Error Type: can't open input file\nError Content: Error Type: can't open input file\n"));

			std::stringstream buffer2;
			std::ofstream out("close.txt");
			WordChainError error4;
			out.close();
			if (!out.is_open()) {
				char buffer2[MAX_BUFFER_SIZE];
				sprintf(buffer2, "Error Type: can't open output file\n");
				string error_content(buffer2);
				int error_code = SE_ERROR_OPENING_OUTPUT_FILE;
				error4.AppendInfo(error_code, error_content);
			}
			string errortext4 = error4.ToString();
			Assert::AreEqual(errortext4, string("Error Type: can't open output file\nError Content: Error Type: can't open output file\n"));
		}
	};
}