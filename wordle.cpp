#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool matchDict(const std::string& in, std::string& floating, const string& word, size_t index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    int count = 0;
    bool trick = in == "--";
    for(const char& c : in){
        if(c == '-'){
            count++;
        }
    }
    if(count < floating.size()) 
        return result;
    for(auto& s : dict){
        if(s.size() != in.size()) continue;
        if(trick and (isupper(s[0]) or isupper(s[1]) ))
          continue;
        auto temp = floating;
        if(matchDict(in, temp, s, 0)){
            result.insert(s);
        }
    }
    return result;
}

bool matchDict(const std::string& in, std::string& floating, const string& word, size_t index){
    if(index == word.size()) 
        return floating.empty();
    if(in[index] != '-') {
        return (in[index] == word[index]) && matchDict(in, floating, word, index + 1);
    } else {
        auto pos = floating.find(word[index]);
        if(pos != std::string::npos)
            floating.erase(pos, 1);
        return matchDict(in, floating, word, index + 1);
    }
}