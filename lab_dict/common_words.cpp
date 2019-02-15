/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */

        for(size_t j = 0; j < words.size(); j++){

          map<string, unsigned int>::iterator lookup = file_word_maps[i].find(words[j]);
          if(lookup == file_word_maps[i].end()){ //does not exist
            (file_word_maps[i])[words[j]] = 1;
          }
          else{
            lookup->second++;
          }

        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for(size_t i = 0; i < file_word_maps.size(); i++){
      for (std::pair<string, unsigned int> key_val : file_word_maps[i]){

        map<string, unsigned int>::iterator lookup = common.find(key_val.first);
        if(lookup == common.end()){ //does not exist
          common[key_val.first] = 1;
        }
        else{
          lookup->second++;
        }

      }
    }

}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for(std::pair<string, unsigned int> key_val : common){
      if(key_val.second == file_word_maps.size()){  //if appears in every file
        bool all_at_least_n_times = true;

        for(size_t i = 0; i < file_word_maps.size(); i++){
          //use const_iterator
          map<string, unsigned int>::const_iterator lookup = file_word_maps[i].find(key_val.first);

          if(lookup->second < n){
            all_at_least_n_times = false;
          }
        }

        if(all_at_least_n_times){
          out.push_back(key_val.first);
        }

      }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
