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
            char tmp[3];
            tmp[0] = m_head;
            tmp[1] = m_tail;
			tmp[2] = '\0';
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
        WordMapElement() {
           fprintf(stderr, "error call WordMapElement\n");
        }
        explicit WordMapElement(Word& word) {
            m_head = word.GetHead();
            m_tail = word.GetTail();
            m_key = word.GetKey();
            WordElement item(std::move(word.GetWord()));
            m_word_set.push_back(item);
            m_cur_longest_index = 0;
        }
        se_errcode AppendWord(const string& word);
        string GetLongestWord() const {
            return m_word_set[m_cur_longest_index].data;
        }
        int GetLongestLen() const {
            return m_word_set[m_cur_longest_index].size;
        }
        bool GetVisitFlag() const {
            if (m_cur_longest_index >= m_word_set.size()) {
                return false;
            } else {
                return m_word_set[m_cur_longest_index].flag;
            }
        }
        void SetVisitFlag(bool _flag) {
            m_word_set[m_cur_longest_index].flag = _flag;
            /*if (_flag) {
                m_cur_longest_index++;
            } else {
                m_cur_longest_index--;
            */
        }
        string ToString() const;
    private:
        typedef struct _WordElement{
            string data;
            int size;
            bool flag;
            _WordElement(string _data) {
                size = _data.size();
                data = _data;
                flag = false;
            }
        } WordElement;
        char m_head;
        char m_tail;
        string m_key;
        int m_cur_longest_index;
        vector<WordElement> m_word_set;
};

class DistanceElement{
    public:
        DistanceElement() {
            fprintf(stderr, "error call WordMapElement\n");
        }
        DistanceElement(const LongestWordChainType& longest_type) : m_longest_type(longest_type) {
            m_letter_distance = 0;
            m_word_distance = 0;
        }
        int GetDistance() const {
            switch (m_longest_type) {
                case word_longest: return GetWordDistance();
                case letter_longest: return GetLetterDistance();
                default: return 0;
            }
        }
        void SetDistance(int distance) {
            switch (m_longest_type) {
                case word_longest: SetWordDistance(distance); break;
                case letter_longest: SetLetterDistance(distance); break;
                default: return;
            }
        }
        void CopyWordBuffer(vector<string>& output_buffer) const {
            output_buffer.assign(m_word_buffer.begin(), m_word_buffer.end());
        }
        void SetWordChain(const vector<string>& others);
        string ToString() const;
    private:
        vector<string> m_word_buffer;
        LongestWordChainType m_longest_type;
        int m_letter_distance;
        int m_word_distance;
        int GetLetterDistance() const {
            return m_letter_distance;
        }
        int GetWordDistance() const {
            return m_word_distance;
        }
        void SetWordDistance(int distance) {
            m_word_distance = distance;
        }
        void SetLetterDistance(int distance) {
            m_letter_distance = distance;
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
        NaiveSearch(const HWmap& map, const LongestWordChainType& type) : m_wmap(map), m_type(type){
            for (char t1 = 'a'; t1 <= 'z'; ++t1) {
                for (char t2 = 'a'; t2 <= 'z'; ++t2) {
                    if (t2 == 'a') {
                        TDmap item;
                        item.insert(TDmap::value_type(t2, DistanceElement(m_type)));
                        m_dmap.insert(HDmap::value_type(t1, item));
                    } else {
                        auto iter = m_dmap.find(t1);
                        iter->second.insert(TDmap::value_type(t2, DistanceElement(m_type)));
                    }
                }
            }
            m_cur_search_len = 0;
        }
        ~NaiveSearch() {}
        se_errcode Search();
        se_errcode Search(const char& head);
        se_errcode LookUp(vector<string>& output_buffer, const char& head, const char& tail) const;
    private:
        HWmap m_wmap;
        HDmap m_dmap;
        LongestWordChainType m_type;
        int m_cur_search_len;
        char m_begin_item;
        vector<string> m_cur_search_chain;
        se_errcode DfsSearch(char cur_head);
};

string tolower(string str);

template<class T> void PrintMap(const unordered_map<char, unordered_map<char, T> >& input_map);

se_errcode ExtractWord(const string& input_text, vector<string>& input_buffer);

se_errcode GenerateWordMap(const vector<string>& input_buffer, unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map);

se_errcode CheckCircle(const unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map, bool& has_circle);

se_errcode CalculateLongestChain(const vector<string>& input_buffer, vector<string>& output_buffer, const LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

se_errcode OutputTransform(const vector<string>& output_buffer, string& output_text);

// public interface
se_errcode Calculate(const string& input_text, string& output_text, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

#endif // SE_WORD_CHAIN_CORE_HPP_
