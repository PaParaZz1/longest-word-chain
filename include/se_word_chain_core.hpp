/*
 * core calculation for longest word chain
 */
#ifndef SE_WORD_CHAIN_CORE_HPP_
#define SE_WORD_CHAIN_CORE_HPP_

#include <vector>
#include <string>
#include "se_word_chain.hpp"
#include "se_word_chain_utils.hpp"

using std::vector;
using std::string;

se_errcode ExtractWord(const string& input_text, vector<string>& input_buffer);

se_errcode CalculateLongestChain(const vector<string>& input_buffer, vector<string>& output_buffer, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

se_errcode OutputTransform(const vector<string>& output_buffer, string& output_text);

// public interface
se_errcode Calculate(const string& input_text, string& output_text, LongestWordChainType& longest_type, const char& head, const char& tail, bool enable_circle);

#endif // SE_WORD_CHAIN_CORE_HPP_
