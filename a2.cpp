////////////////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Haotian Zhu
// CS email:       hzhu226@wisc.edu
//
// Description:    The source file for a2.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A2.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions/methods.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
////////////////////////////////////////////////////////////////////////////////

#include "a2.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

void cleanData(std::ifstream &inFile, std::ofstream &outFile,
               std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // # of lines of code in Gerald's implementation: 13
    // Do the following operations on each review before
    // storing it to the output file:
    //   1. Replace hyphens with spaces.
    //   2. Split the line of text into individual words.
    //   3. Remove the punctuation marks from the words.
    //   5. Remove the short (1 or 0 letter) words. You should NOT remove
    //      numbers in this step because if you do so, you'll lose the ratings.
    //   7. Remove stopwords.
    string myline;
    
    while(getline(inFile, myline)) {
        vector<string> myword;
        vector<string> modified;
      
        // replace hyphens with spaces
        replaceHyphensWithSpaces(myline);
      
        // split the line into words
        splitLine(myline, myword);
        // remove the punctuation marks
        removePunctuation(myword, modified);
        // remove the short words
        removeShortWords(modified);
        // remove stopwords
        removeStopWords(modified, stopwords);
    
        // put clean data into output file
        stringstream output;
        for (vector<string>::iterator str = modified.begin(); str != modified.end(); ++str) {
            output << *str << " ";
        }
        string line = output.str();
      
        outFile << line << endl;
    }
}

void fillDictionary(std::ifstream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
    string line;
    while(getline(newInFile, line)) {
        long rating = line[0] - '0';
        vector<string> word;
        splitLine(line, word);
        
        for (vector<string>::iterator str = next(word.begin()); str != word.end(); ++str) {
            unordered_map<string, pair<long, long> >::iterator curr = dict.find(*str);

            // add new values if it doesn't exist
            if (curr == dict.end()) {
                dict[*str].first = rating;
                dict[*str].second = 1;
            }
            // update values if it exists
            else {
                pair<long, long> num = curr -> second;
                dict[*str].first = num.first + rating;
                dict[*str].second = ++num.second;
            }
        }
    }
}


void fillStopWords(std::ifstream &inFile,
                   std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    string myline;
    while(getline(inFile, myline)) {
        stopwords.insert(myline);
    }
}

void scoreReviews(std::ifstream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ofstream &ratingsFile) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
    string line;
    while(getline(testFile, line)) {
        // if the line is empty, give a neutral rate
        if (line == "") {
            double neutral = 2;
            ratingsFile << neutral << " ";
            ratingsFile << line << endl;
        } 
        else {
            double rating = 0;
            vector<string> word;
            splitLine(line, word);
            
            // calculate the correct ratings
            for (vector<string>::iterator str = word.begin(); str != word.end(); ++str) {
                unordered_map<string, pair<long, long> >::iterator curr = dict.find(*str);
                if (curr == dict.end()) {
                    rating += 2  ;
                }
                else {
                    pair<long, long> num = curr -> second;
                    double first = num.first;
                    double second = num.second;
                    rating += first / second;
                }
            }
            double predicted = rating / word.size();
            ratingsFile << fixed << setprecision(2) << predicted << " ";
            ratingsFile << line << endl;
        }
    }
}

void removePunctuation(std::vector<std::string> &inTokens,
                       std::vector<std::string> &outTokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    for (vector<string>::iterator str = inTokens.begin(); str != inTokens.end(); ++str) {
        // erase the punctuation
        (*str).erase(remove_if((*str).begin(), (*str).end(), ::ispunct),
                    (*str).end());
        outTokens.push_back(*str);
    }
}

void removeShortWords(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    vector<string> list = tokens;
    for (vector<string>::iterator str = list.begin(); str != list.end(); ++str) {
        if ((*str).size() == 1 && !isdigit((*str)[0])) {
            // erase the short words
            tokens.erase(remove(tokens.begin(), tokens.end(), *str), tokens.end());
        }
    }
}

void removeStopWords(std::vector<std::string> &tokens,
                     std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    vector<std::string> list = tokens;
    for (vector<string>::iterator str = list.begin(); str != list.end(); ++str) {
        if (stopwords.find(*str) != stopwords.end()) {
            // erase the stop words
            tokens.erase(remove(tokens.begin(), tokens.end(), *str), tokens.end());
        }
    }
}

void replaceHyphensWithSpaces(std::string &line) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    replace(line.begin(), line.end(), '-', ' ');
}

void splitLine(std::string &line, std::vector<std::string> &words) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    string word;
    stringstream str(line);
    while (str >> word) {
        words.push_back(word);
    }
}
