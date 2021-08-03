/*
 * StringUtility.h
 *
 *  Created on: Aug 3, 2021
 *      Author: shawn
 */

#ifndef CORE_STRINGUTILITY_H_
#define CORE_STRINGUTILITY_H_

#include <vector>
#include <string>

namespace bsk {

class StringUtility {
public:
    StringUtility();
    virtual ~StringUtility();

    static std::vector<std::string> split(const std::string& str, const std::string& delimiters, bool removeEmpty = true);

};

} /* namespace bsk */

#endif /* CORE_STRINGUTILITY_H_ */
