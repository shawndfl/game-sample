/*
 * StringUtility.cc
 *
 *  Created on: Aug 3, 2021
 *      Author: shawn
 */

#include "StringUtility.h"

namespace bsk {

/*************************************************/
StringUtility::StringUtility() {

}

/*************************************************/
StringUtility::~StringUtility() {
}

/*************************************************/
std::vector<std::string> StringUtility::split(const std::string& str, const std::string& delimiters, bool removeEmpty) {
    std::vector<std::string> parts;
    std::string token;
    for(size_t i = 0; i< str.size(); i++) {
        char ch = str[i];

        bool foundDelimter = false;
        for(size_t j =0; j < delimiters.size(); j++) {
            if(ch == delimiters[j]){
                foundDelimter = true;
                break;
            }
        }

        if(foundDelimter) {
            // save the token
            if(!(removeEmpty && token.size() == 0)) {
                parts.push_back(token);
            }
            token = "";
        } else {
            // build up the token
            token += ch;
        }
    }
    return parts;
}

} /* namespace bsk */
