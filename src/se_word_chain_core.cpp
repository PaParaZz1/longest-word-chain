#include <vector>
#include <string>
#include <unordered_map>
#include "se_word_chain.hpp"
#include "se_word_chain_utils.hpp"
#include "se_word_chain_core.hpp"

using std::vector;
using std::string;
using std::unordered_map;
using Cmap = unordered_map<char, WordMapElement>;
using CCmap = unordered_map<char, unordered_map<char, WordMapElement> >;

SearchInterface::~SearchInterface() {}

se_errcode NaiveSearch::Search() {
    return SE_OK;
}

se_errcode NaiveSearch::LookUp(vector<string>& output_buffer, const char& head, const char& tail) const {
    se_errcode ret = SE_OK;
    char longest_head = NO_ASSIGN_HEAD;
    char longest_tail = NO_ASSIGN_TAIL;
    int temp_head_longest = 0;

    if (head == NO_ASSIGN_HEAD) {
        for (auto iter_h = m_dmap.begin(); iter_h != m_dmap.end(); ++iter_h) {
            auto tail_map = iter_h->second;
            if (tail == NO_ASSIGN_TAIL) {
                int temp_tail_longest = 0;
                char longest_tail_temp = NO_ASSIGN_TAIL;
                for (auto iter_t = tail_map.begin(); iter_t != tail_map.end(); ++iter_t) {
                    if (iter_t->second.GetDistance() > temp_tail_longest) {
                        temp_tail_longest = iter_t->second.GetDistance();
                        longest_tail_temp = iter_t->first;
                    }
                }
                if (temp_tail_longest > temp_head_longest) {
                    temp_head_longest = temp_tail_longest;
                    longest_head = iter_h->first;
                    longest_tail = longest_tail_temp;
                }
            } else {
                auto tail_find_iter = tail_map.find(tail);
                if (tail_find_iter != tail_map.end()) {
                    if (tail_find_iter->second.GetDistance() > temp_head_longest) {
                        temp_head_longest = tail_find_iter->second.GetDistance();
                        longest_head = iter_h->first;
                        longest_tail = tail;
                    }
                }
            }
        }
    } else {
        if (tail == NO_ASSIGN_TAIL) {
            longest_head = head;
            auto tail_map_iter = m_dmap.find(head);
            if (tail_map_iter != m_dmap.end()) {
                auto tail_map = tail_map_iter->second;
                for (auto iter_t = tail_map.begin(); iter_t != tail_map.end(); ++iter_t) {
                    if (iter_t->second.GetDistance() > temp_head_longest) {
                        temp_head_longest = iter_t->second.GetDistance();
                        longest_tail = iter_t->first;
                    }
                }
            }
        } else {
            longest_head = head;
            longest_tail = tail;
        }
    }

    if (temp_head_longest == 0) {
        fprintf(stderr, "no available word chain for head(%c) and tail(%c)\n", head, tail);
        return SE_NO_AVAILABLE_WORD_CHAIN;
    } else {
        auto tail_map_iter = m_dmap.find(longest_head);
        auto element_iter = tail_map_iter->second.find(longest_tail);
        element_iter->second.CopyWordBuffer(output_buffer);
        return SE_OK;
    }
}

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
    se_errcode ret = SE_OK;

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
                if ((ret = tail_find_flag->second.AppendWord(word_item.GetWord())) != SE_OK) {
                    fprintf(stderr, "repeat word: %s\n", word_item.GetWord().c_str());
                }
            }
        }
    }
    return ret;
}

se_errcode CheckCircle(const unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map, bool& has_circle) {
    /*
     * Brief:
     *     check whether there is circle in map
     * Param:
     *     origin_word_map: word map established by head and tail letter(<head, <tail, element>)
     *     has_circle: whether has circle in map
     * Return:
     *     if has circle, return true, otherwise return false
     */
    return SE_OK;
}

se_errcode ChainSearch(const unordered_map<char, unordered_map<char, WordMapElement> >& origin_word_map, vector<string>& output_buffer, const LongestWordChainType& longest_type, const char& head, const char& tail) {
    SearchInterface* handle_search = NULL;
    int search_type = 0;
    switch (search_type) {
        case 0: {
            handle_search = new NaiveSearch(origin_word_map, longest_type);
            break;
        }   
    }
    handle_search->Search();
    handle_search->LookUp(output_buffer, head, tail);
    delete(handle_search);
    return SE_OK;
}

se_errcode CalculateLongestChain(const vector<string>& input_buffer, vector<string>& output_buffer, const LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle) {
    CCmap origin_word_map;
    se_errcode ret = SE_OK;
    // generate word map
    ret = GenerateWordMap(input_buffer, origin_word_map);
    switch (ret) {
        case SE_REPEAT_WORD: ret = SE_OK;// fall through
        case SE_OK: break;
        default: return ret;
    }
    // check circle
    bool has_circle;
    CheckCircle(origin_word_map, has_circle);
    if (!enable_circle && has_circle) {
        return SE_HAS_CIRCLE;
    }
    // calculate longest chain
    switch (longest_type) {
        case word_longest:
        case letter_longest:
        default: {
            fprintf(stderr, "invalid longest_type argument: %d\n", longest_type);
            return SE_INVALID_LONGEST_TYPE;
        }
    }
    return ret;
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
