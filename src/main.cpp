/*
 * command line entrance for longest word chain 
 */
#include "se_word_chain.hpp"
#include "se_word_chain_core.hpp"
#include "se_word_chain_utils.hpp"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#define MAX_FILE_LEN 512
#define MAX_BUFFER_SIZE 128
int main(int argc, char** argv) {
    // parse command argument
    // WordList.exe -w -c -h h -t t -r
	WordChainError handle_error;
    const char usage[] = "Usage: WordList.exe -w/c <input_file> [-h <head>] [-t <tail>] [-r]";
    bool longest_type_flag = false;
    LongestWordChainType longest_type;
    char head = NO_ASSIGN_HEAD;
    char tail = NO_ASSIGN_TAIL;
    bool enable_circle = false;
    char input_file[MAX_FILE_LEN]; 
    const char output_file[MAX_FILE_LEN] = "solution.txt";
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
						char buffer[MAX_BUFFER_SIZE];
						sprintf(buffer, "Error Type: invalid longest word chain type, now support--'word' and 'letter'\n");
						string error_content(buffer);
						int error_code = SE_INVALID_LONGEST_TYPE;
						handle_error.AppendInfo(error_code, error_content);
                        fprintf(stderr, "%s\n", usage);
                        return SE_INVALID_LONGEST_TYPE;
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
						char buffer[MAX_BUFFER_SIZE];
						sprintf(buffer, "Error Type: invalid longest word chain type, now support--'word' and 'letter'\n");
						string error_content(buffer);
						int error_code = SE_INVALID_LONGEST_TYPE;
						handle_error.AppendInfo(error_code, error_content);
                        fprintf(stderr, "%s\n", usage);
                        return SE_INVALID_LONGEST_TYPE;
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
						char buffer[MAX_BUFFER_SIZE];
						sprintf(buffer, "Error Type: invalid command argument\n");
						string error_content(buffer);
						int error_code = SE_INVALID_COMMAND_ARGUMENT;
						handle_error.AppendInfo(error_code, error_content);
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
						char buffer[MAX_BUFFER_SIZE];
						sprintf(buffer, "Error Type: invalid command argument\n");
						string error_content(buffer);
						int error_code = SE_INVALID_COMMAND_ARGUMENT;
						handle_error.AppendInfo(error_code, error_content);
                        fprintf(stderr, "%s\n", usage);
                        return SE_INVALID_COMMAND_ARGUMENT;
                    }
                }
                default: {
					char buffer[MAX_BUFFER_SIZE];
					sprintf(buffer, "Error Type: invalid command argument\n");
					string error_content(buffer);
					int error_code = SE_INVALID_COMMAND_ARGUMENT;
					handle_error.AppendInfo(error_code, error_content);
                    fprintf(stderr, "%s\n", usage);
                    return SE_INVALID_COMMAND_ARGUMENT;
                }
            } 
        } else {
			char buffer[MAX_BUFFER_SIZE];
			sprintf(buffer, "Error Type: invalid command argument\n");
			string error_content(buffer);
			int error_code = SE_INVALID_COMMAND_ARGUMENT;
			handle_error.AppendInfo(error_code, error_content);
            fprintf(stderr, "%s\n", usage);
            return SE_INVALID_COMMAND_ARGUMENT;
        }
    }
    if (!longest_type_flag) {
		char buffer[MAX_BUFFER_SIZE];
		sprintf(buffer, "Error Type: invalid longest word chain type, now support--'word' and 'letter'\n");
		string error_content(buffer);
		int error_code = SE_INVALID_LONGEST_TYPE;
		handle_error.AppendInfo(error_code, error_content);
        fprintf(stderr, "%s\n", usage);
        return SE_INVALID_LONGEST_TYPE;
    }
    if (DEBUG) {
        fprintf(stdout, "cmd argument parse OK!\n");
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
    string input_text;
    string output_text;
	std::ifstream in(input_file);
	std::stringstream buffer;
	std::ofstream out(output_file);
	if (!in.is_open()) {
		char buffer[MAX_BUFFER_SIZE];
		sprintf(buffer, "Error Type: can't open input file\n");
		string error_content(buffer);
		int error_code = SE_ERROR_OPENING_INPUT_FILE;
		handle_error.AppendInfo(error_code, error_content);
		fprintf(stderr, "error opening input file\n");
		return SE_ERROR_OPENING_INPUT_FILE;
	} else {
		buffer << in.rdbuf();
		input_text = buffer.str();
	}

    // calculate
    int ret = SE_OK;
    ret = Calculate(input_text, output_text, longest_type, head, tail, enable_circle, handle_error);
    // output to target file
	if (!out.is_open()) {
		char buffer[MAX_BUFFER_SIZE];
		sprintf(buffer, "Error Type: can't open output file\n");
		string error_content(buffer);
		int error_code = SE_ERROR_OPENING_OUTPUT_FILE;
		handle_error.AppendInfo(error_code, error_content);
		fprintf(stderr, "error opening output file\n");
		return SE_ERROR_OPENING_OUTPUT_FILE;
	} else {
		out << output_text;
		out.close();
	}
    return ret;

ERROR_MAIN:
    fprintf(stderr, "error code:%d\n", ret);
    return ret;
}
