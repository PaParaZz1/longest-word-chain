#include "stdafx.h"
#include "CppUnitTest.h"
#include "se_word_chain.hpp"
#include "se_word_chain_utils.hpp"
#include "se_word_chain_core.hpp"
#include "se_word_chain_core.cpp"
#include <iostream>
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
			string input_text1 = "_this is      a!@#$test of0extract!word...... ";
			vector<string>  input_buffer1;
			vector<string> result1 = { "this","is","a","test","of","extract","word" };
			ExtractWord(input_text1, input_buffer1);
			Assert::AreEqual(result1.size(), input_buffer1.size());
			for (int i = 0; i < result1.size(); i++) {
				Assert::AreEqual(result1[i], input_buffer1[i]);
			}

			string input_text2 = "_this___is___another======test of extract[][][]word. ";
			vector<string>  input_buffer2;
			vector<string> result2 = { "this","is","another","test","of","extract","word" };
			ExtractWord(input_text2, input_buffer2);
			Assert::AreEqual(result2.size(), input_buffer2.size());
			for (int i = 0; i < result2.size(); i++) {
				Assert::AreEqual(result2[i], input_buffer2[i]);
			}

			string input_text3 = "_[][][]....";
			vector<string>  input_buffer3;
			vector<string> result3 = { };
			ExtractWord(input_text3, input_buffer3);
			Assert::AreEqual(result3.size(), input_buffer3.size());
			for (int i = 0; i < result3.size(); i++) {
				Assert::AreEqual(result3[i], input_buffer3[i]);
			}
		}

		TEST_METHOD(Test_OutputTransform)
		{
			//TEST  OutputTransform
			string output_text1 = "";
			string result1 = "this\nis\na\ntest\nof\nextract\nword\n";
			vector<string> output_buffer1 = { "this","is","a","test","of","extract","word" };
			OutputTransform(output_buffer1, output_text1);
			Assert::AreEqual(result1, output_text1);

			string output_text2 = "";
			string result2 = "";
			vector<string> output_buffer2 = {  };
			OutputTransform(output_buffer2, output_text2);
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

		TEST_METHOD(Test_AppendWord)
		{
			//TEST  AppendWord
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

			Word test2 = "phycho";
			WordMapElement testElement2 = WordMapElement(test2);
			Assert::AreEqual(testElement2.GetLongestLen(), 6);
			Assert::AreEqual(testElement2.GetLongestWord(), string("phycho"));
			testElement2.AppendWord("phy");
			Assert::AreEqual(testElement2.GetLongestLen(), 6);
			Assert::AreEqual(testElement2.GetLongestWord(), string("phycho"));
			testElement2.AppendWord("phyphychocho");
			Assert::AreEqual(testElement2.GetLongestLen(), 12);
			Assert::AreEqual(testElement2.GetLongestWord(), string("phyphychocho"));
		}

		TEST_METHOD(Test_CheckCircle)
		{
			//TEST  CheckCircle
			CCmap wordmap1;
			vector<string> test1 = { "this","map","does","not","have","circle" };
			GenerateWordMap(test1, wordmap1);
			bool hascircle1;
			CheckCircle(wordmap1, hascircle1);
			Assert::AreEqual(hascircle1, false);

			CCmap wordmap2;
			vector<string> test2 = { "this","map","should","have","circles","doesnt","it"};
			GenerateWordMap(test2, wordmap2);
			bool hascircle2;
			CheckCircle(wordmap2, hascircle2);
			Assert::AreEqual(hascircle2, true);

			CCmap wordmap3;
			vector<string> test3 = { "this","map","should","not","have","circle","algebra","TNT"};
			GenerateWordMap(test3, wordmap3);
			bool hascircle3;
			CheckCircle(wordmap3, hascircle3);
			Assert::AreEqual(hascircle3, false);
		}
	};
}