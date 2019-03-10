#include <vector>
#include <string>
#include <unordered_map>
#include "se_word_chain.hpp"
#include "se_word_chain_utils.hpp"
#include "se_word_chain_core.hpp"

using std::vector;
using std::string;
using std::unordered_map;

string tolower(string str){
    for(int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

se_errcode ExtractWord(const string& input_text, vector<string>& input_buffer) {
    /*
     * Brief:
     *     extract all the correct word in the input, transform it into lower case letters and store it in input buffer
     *     all the word in the input_text are seperated with non-alpha character
     * Param:
     *     input_text: input text including word
     *     input_buffer: a vector including all the correctly seperated word
     * Return:
     *     all: SE_OK
     */
    int len=input_text.length();
    for(int i=0;i<len;i++){
        if(isalpha(input_text[i])){
            for(int j=i;j<len;j++){
                if(!isalpha(input_text[j])){
                    input_buffer.push_back(tolower(input_text.substr(i,j-i)));
                    i=j;
                    break;
                }
            }
        }
    }
    return SE_OK;
}

se_errcode GenerateWordMap(const vector<string>& input_buffer, unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map) {
    using Cmap = unordered_map<char, WordMapElement>;
    using CCmap = unordered_map<char, unordered_map<char, WordMapElement> >;

    for (auto iter = input_buffer.begin(); iter != input_buffer.end(); ++iter) {
        string item = *iter;
        Word word_item = Word(item);
        auto head_find_flag = origin_word_map.find(word_item.GetHead());
        if (head_find_flag == origin_word_map.end()) {
            Cmap tail_map;
            tail_map.insert(Cmap::value_type(word_item.GetTail(), WordMapElement(word_item)));
            origin_word_map.insert(CCmap::value_type(word_item.GetHead(), tail_map));
        } else {
            Cmap tail_map = head_find_flag->second;
            auto tail_find_flag =  tail_map.find(word_item.GetTail());
            if (tail_find_flag == tail_map.end()) {
                tail_map.insert(Cmap::value_type(word_item.GetTail(), WordMapElement(word_item)));
            } else {
                se_errcode ret = SE_OK;
                if ((ret = tail_find_flag->second.AppendWord(word_item.GetWord())) != SE_OK) {
                    fprintf(stderr, "repeat word: %s\n", word_item.GetWord().c_str());
                    return ret;
                }
            }
        }
    }
    return SE_OK;
}

se_errcode CalculateLongestChain(const vector<string>& input_buffer, vector<string>& output_buffer, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle) {
    unordered_map<char, unordered_map<char, WordMapElement> > origin_word_map;
    
    return SE_OK;
}

se_errcode OutputTransform(const vector<string>& output_buffer, string& output_text) {
    /*
     * Brief:
     *     transform word into output text
     *     all the word in output_text need to be seperated with line break
     * Param:
     *     output_buffer: a buffer including all the correct word to be output
     *     output_text: a string including all the word in correct form
     * Return:
     *     all: SE_OK
     */
    int size=output_buffer.size();
    for(int i=0;i<size;i++){
        output_text+=output_buffer[i]+"\n";
    }
    return SE_OK;
}

se_errcode Calculate(const string& input_text, string& output_text, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle) {
    int ret = SE_OK;
    vector<string> input_buffer;
    vector<string> output_buffer;
    if (ret ==ExtractWord(input_text, input_buffer) != SE_OK) {
        goto ERROR_CAL;
    }

    if (ret == CalculateLongestChain(input_buffer, output_buffer, longest_type, head, tail, enable_circle) != SE_OK) {
        goto ERROR_CAL;
    }

    if (ret == OutputTransform(output_buffer, output_text) != SE_OK) {
        goto ERROR_CAL;
    }
    return SE_OK;
    
ERROR_CAL:
    return ret;
}

se_errcode WordMapElement::AppendWord(const string& word) {
    auto iter = m_word_set.find(word);
    if (iter != m_word_set.end()) {
        return SE_REPEAT_WORD;
    }

    m_word_set.insert(word);
    int cur_len = word.size();
    if (cur_len > m_current_longest_len) {
        m_current_longest_len = cur_len;
        m_current_longest_word = word;
    }
    return SE_OK;
}
