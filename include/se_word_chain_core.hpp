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

class DistanceElement{
    public:
        DistanceElement() {
            m_letter_distance = 0;
            m_word_distance = 0;
        }
        int GetDistance() const {
            return m_letter_distance;
        }
        void CopyWordBuffer(vector<string>& output_buffer) const {
            output_buffer.assign(m_word_buffer.begin(), m_word_buffer.end());
        }
        //se_errcode ApeendChainWord
    private:
        vector<string> m_word_buffer;
        int m_letter_distance;
        int m_word_distance;
        int GetLetterDistance() const {
            return m_letter_distance;
        }
        int GetWordDistance() const {
            return m_word_distance;
        }
};

class SearchInterface {
    public:
        virtual ~SearchInterface() = 0;
        virtual se_errcode Search() = 0;
        virtual se_errcode LookUp(vector<string>& output_buffer, const char& head, const char& tail) const = 0;
};

class NaiveSearch : public SearchInterface{
    using HWmap = unordered_map<char, unordered_map<char, WordMapElement> >;
    using TWmap = unordered_map<char, WordMapElement>;
    using HDmap = unordered_map<char, unordered_map<char, DistanceElement> >;
    using TDmap = unordered_map<char, DistanceElement>;
    public:
        NaiveSearch(const HWmap& map, const LongestWordChainType& type) : m_wmap(map), m_type(type){}
        ~NaiveSearch() {}
        se_errcode Search();
        se_errcode LookUp(vector<string>& output_buffer, const char& head, const char& tail) const;
    private:
        HWmap m_wmap;
        HDmap m_dmap;
        LongestWordChainType m_type;
};

string tolower(string str);

se_errcode ExtractWord(const string& input_text, vector<string>& input_buffer);

se_errcode GenerateWordMap(const vector<string>& input_buffer, unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map);

se_errcode CheckCircle(const unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map, bool& has_circle);

se_errcode CalculateLongestChain(const vector<string>& input_buffer, vector<string>& output_buffer, const LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

se_errcode OutputTransform(const vector<string>& output_buffer, string& output_text);

// public interface
se_errcode Calculate(const string& input_text, string& output_text, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

#endif // SE_WORD_CHAIN_CORE_HPP_
