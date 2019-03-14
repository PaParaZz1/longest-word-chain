#ifndef SE_WORD_CHAIN_INTERFACE_HPP_
#define SE_WORD_CHAIN_INTERFACE_HPP_
#include "se_word_chain_utils.hpp"


int get_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
int get_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
void GetErrorInfo(WordChainError& handle_error);

#endif // SE_WORD_CHAIN_INTERFACE_HPP_
