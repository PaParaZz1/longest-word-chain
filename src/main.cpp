/*
 * command line entrance for longest word chain 
 */
#include <cstdio>
#include <cstring>
#include "se_word_chain.hpp"
#include "se_word_chain_core.hpp"
#define MAX_FILE_LEN 512

int main(int argc, char** argv) {
    // parse command argument
    // WordList.exe -w -c -h h -t t -r
    const char usage[] = "Usage: WordList.exe -w/c <input_file> [-h <head>] [-t <tail>] [-r]";
    const bool DEBUG = true;
    bool longest_type_flag = false;
    LongestWordChainType longest_type;
    char head = NO_ASSIGN_HEAD;
    char tail = NO_ASSIGN_TAIL;
    bool enable_circle = false;
    char input_file[MAX_FILE_LEN]; 

    for (int i=1; i<argc; ++i) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'w': {
                    if (!longest_type_flag) {
                        longest_type_flag = true;    
                        longest_type = word_longest;
                        i++;
                        strcpy(input_file, argv[i]);
                        break;
                    } else {
                        fprintf(stderr, "%s\n", usage);
                        return SE_INVALID_COMMAND_ARGUMENT;
                    }
                }
                case 'c': {
                    if (!longest_type_flag) {
                        longest_type_flag = true;    
                        longest_type = letter_longest;
                        i++;
                        strcpy(input_file, argv[i]);
                        break;
                    } else {
                        fprintf(stderr, "%s\n", usage);
                        return SE_INVALID_COMMAND_ARGUMENT;
                    }
                }
                case 'r': {
                    enable_circle = true;
                    break;
                }
                case 'h': {
                    i++;
                    if (isalpha(argv[i][0])) {
                        head = argv[i][0];
                        break;
                    } else {
                        fprintf(stderr, "%s\n", usage);
                        return SE_INVALID_COMMAND_ARGUMENT;
                    }
                }
                case 't': {
                    i++;
                    if (isalpha(argv[i][0])) {
                        tail = argv[i][0];
                        break;
                    } else {
                        fprintf(stderr, "%s\n", usage);
                        return SE_INVALID_COMMAND_ARGUMENT;
                    }
                }
                default: {
                    fprintf(stderr, "%s\n", usage);
                    return SE_INVALID_COMMAND_ARGUMENT;
                }
            } 
        } else {
            fprintf(stderr, "%s\n", usage);
            return SE_INVALID_COMMAND_ARGUMENT;
        }
    }
    if (!longest_type_flag) {
        fprintf(stderr, "%s\n", usage);
        return SE_INVALID_COMMAND_ARGUMENT;
    }
    fprintf(stdout, "cmd argument parse OK!\n");
    if (DEBUG) {
        switch (longest_type) {
            case word_longest: fprintf(stdout, "longest type: word_longest\n"); break;
            case letter_longest: fprintf(stdout, "longest type: letter_longest\n"); break;
            default:
                fprintf(stderr, "invalid longest type\n");
                return SE_INVALID_LONGEST_TYPE;
        }
        fprintf(stdout, "input_file path:%s\n", input_file);
        fprintf(stdout, "head:%c\n", head);
        fprintf(stdout, "tail:%c\n", tail);
        fprintf(stdout, "enable_circle:%s\n", enable_circle ? "true" : "false");        
    }
    // get file content and push it into input buffer
    //
    // calculate
    //
    // output to target file
    return 0;
}
