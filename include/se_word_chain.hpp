/*
 * global data structure definition
 */
#ifndef SE_WORD_CHAIN_HPP_
#define SE_WORD_CHAIN_HPP_

#define NO_ASSIGN_HEAD ('\0')
#define NO_ASSIGN_TAIL ('\0')
#define DEBUG false
#if DEBUG
#define SE_WORD_CHAIN_LOG(...) fprintf(stdout, __VA_ARGS__);\
                               fprintf(stdout, "\n");
#else 
#define SE_WORD_CHAIN_LOG(...) 0
#endif // DEBUG

typedef enum {
    word_longest,
    letter_longest
} LongestWordChainType;


#endif // SE_WORD_CHAIN_HPP_
