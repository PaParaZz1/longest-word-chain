/*
 * global error code definition
 */
#ifndef SE_WORD_CHAIN_UTILS_HPP_
#define SE_WORD_CHAIN_UTILS_HPP_
#include <string>
#include <vector>

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
using std::vector;

class WordChainError {
    public:
        WordChainError() {}
        void AppendInfo(int error_code, const string& error_content);
        ~WordChainError();
        string ToString() const;
    private:
        typedef struct _info {
            se_errcode error_code;
            string error_content;
            _info(se_errcode _error_code, const string& _error_content) {
                error_code = _error_code;
                error_content = _error_content;
            }
        } ErrorInfo; 
        vector<ErrorInfo> m_error_info;
};
#endif // SE_WORD_CHAIN_UTILS_HPP_
