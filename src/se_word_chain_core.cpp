#include <vector>
#include <string>
#include "se_word_chain.hpp"
#include "se_word_chain_utils.hpp"
#include "se_word_chain_core.hpp"

using std::vector;
using std::string;

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
    return SE_OK;
}

se_errcode CalculateLongestChain(const vector<string>& input_buffer, vector<string>& output_buffer, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle) {
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
    return SE_OK;
}

se_errcode Calculate(const string& input_text, string& output_text, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle) {
    return SE_OK;
}

se_errcode WordMapSet::AppendWord(const string& word) {
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
