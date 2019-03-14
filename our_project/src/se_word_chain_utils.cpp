#include "se_word_chain_utils.hpp"
#include <string>
#include <stdio.h>

using std::string;


WordChainError::~WordChainError() {
    FILE* error_file = stderr;
    fprintf(error_file, "%s", this->ToString().c_str());
}

void WordChainError::AppendInfo(int error_code, const string& error_content) {
    m_error_info.push_back(ErrorInfo(error_code, error_content));
}

string WordChainError::ToString() const {
    string ret("");
    for (auto iter = m_error_info.begin(); iter != m_error_info.end(); ++iter) {
        switch (iter->error_code) {
            case SE_REPEAT_WORD: ret += "Error Type: repeat word\n"; break;
            case SE_HAS_CIRCLE: ret += "Error Type: input has circle but not enable circle\n"; break;
            case SE_INVALID_LONGEST_TYPE: ret += "Error Type: invalid longest word chain type, now support--'word' and 'letter'\n"; break;
            case SE_NO_AVAILABLE_WORD_CHAIN: ret += "Error Type: no available word chain\n"; break;
            case SE_INVALID_COMMAND_ARGUMENT: ret += "Error Type: invalid command argument\n"; break;
            case SE_ERROR_OPENING_INPUT_FILE: ret += "Error Type: can't open input file\n"; break;
            case SE_ERROR_OPENING_OUTPUT_FILE: ret += "Error Type: can't open output file\n"; break;
            default: return ret;
        }
        ret += "Error Content: " + iter->error_content;
    }
    return ret;
}
