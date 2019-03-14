/*
 * global error code definition
 */
#ifndef SE_WORD_CHAIN_UTILS_HPP_
#define SE_WORD_CHAIN_UTILS_HPP_
#include <string>

#define SE_OK 0
#define SE_REPEAT_WORD -1
#define SE_HAS_CIRCLE -2
#define SE_INVALID_LONGEST_TYPE -3
#define SE_NO_AVAILABLE_WORD_CHAIN -4
#define SE_INVALID_COMMAND_ARGUMENT -5
#define SE_ERROR_OPENING_INPUT_FILE -6
#define SE_ERROR_OPENING_OUTPUT_FILE -7
typedef int se_errcode;
using std::string;

class WordChainError {
    public:
        WordChainError(int error_code, string error_content) : m_error_code(error_code), m_error_content(error_content) {}
        ~WordChainError();
        string ToString() const;
    private:
        se_errcode m_error_code;
        string m_error_content;
};
#endif // SE_WORD_CHAIN_UTILS_HPP_
