#include "se_word_chain_interface.hpp"
#include "se_word_chain_core.hpp"
#include <string>
#include <vector>
#include <string.h>

using std::string;
using std::vector;

void StringSplit(const string& input, vector<string>& result, const string& s) {
    string::size_type pos1, pos2;
    pos1 = 0;
    pos2 = input.find(s);
    size_t s_size = s.size();
    while (pos2 != string::npos) {
        result.__emplace_back(input.substr(pos1, pos2));
        pos1 = pos2 + s_size;
        pos2 = input.find(s, pos1);
    }
    if (pos1 != input.size()) {
        result.__emplace_back(input.substr(pos1));
    }
}

int get_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    LongestWordChainType longest_type = word_longest;
    string input_text;
    string output_text;
    for (int i=0; i<len; ++i) {
        input_text += string(words[i]) + "\n";
    }
    WordChainError handle_error;
    Calculate(input_text, output_text, longest_type, head, tail, enable_loop, handle_error);
    int result_word_num = 0;
    vector<string> result_vec;
    StringSplit(output_text, result_vec, "\n");
    result_word_num = result_vec.size();
    for (int i=0; i<result_word_num; ++i) {
        strcpy(result[i], result_vec[i].c_str());
    }
    return result_word_num;
}

int get_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    LongestWordChainType longest_type = letter_longest;
    string input_text;
    string output_text;
    for (int i=0; i<len; ++i) {
        input_text += string(words[i]) + "\n";
    }
    WordChainError handle_error;
    Calculate(input_text, output_text, longest_type, head, tail, enable_loop, handle_error);
    int result_word_num = 0;
    vector<string> result_vec;
    StringSplit(output_text, result_vec, "\n");
    result_word_num = result_vec.size();
    for (int i=0; i<result_word_num; ++i) {
        strcpy(result[i], result_vec[i].c_str());
    }
    return result_word_num;
}
void GetErrorInfo(WordChainError& handle_error) {

}

