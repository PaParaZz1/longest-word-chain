/*
 * core calculation for longest word chain
 */
#ifndef SE_WORD_CHAIN_CORE_HPP_
#define SE_WORD_CHAIN_CORE_HPP_

#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include "se_word_chain.hpp"
#include "se_word_chain_utils.hpp"

using std::vector;
using std::string;
using std::set;
using std::unordered_map;

class Word {
    public:
        Word(const string& word) : m_word(word) {
            m_head = m_word[0];
            m_tail = m_word[m_word.size() - 1];
            char tmp[2];
            tmp[0] = m_head;
            tmp[1] = m_tail;
            m_key = string(tmp);
        } 
        char GetHead() const {
            return m_head;
        }
        char GetTail() const {
            return m_tail;
        }
        string GetKey() const {
            return m_key;
        }
        string GetWord() const {
            return m_word;
        }
    private:
        char m_head;
        char m_tail;
        string m_key;
        string m_word;
};

class WordMapElement {
    /*
     * word with the same head and tail in a set
     */
    public:
        WordMapElement(Word& word) {
            m_head = word.GetHead();
            m_tail = word.GetTail();
            m_key = word.GetKey();
            m_current_longest_len = 0;
        }
        se_errcode AppendWord(const string& word);
        string GetLongestWord() const {
            return m_current_longest_word;
        }
        int GetLongestLen() const {
            return m_current_longest_len;
        }
    private:
        char m_head;
        char m_tail;
        string m_key;
        string m_current_longest_word;
        int m_current_longest_len;
        set<string, std::greater<string> > m_word_set;
};

string tolower(string str);

se_errcode ExtractWord(const string& input_text, vector<string>& input_buffer);

se_errcode GenerateWordMap(const vector<string>& input_buffer, unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map);

se_errcode CheckCircle(const unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map, bool& has_circle);

se_errcode CalculateLongestChain(const vector<string>& input_buffer, vector<string>& output_buffer, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

se_errcode OutputTransform(const vector<string>& output_buffer, string& output_text);

// public interface
se_errcode Calculate(const string& input_text, string& output_text, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

#endif // SE_WORD_CHAIN_CORE_HPP_
