/*
 * NoCopy.h
 *
 *  Created on: Aug 2, 2020
 *      Author: sdady
 */

#ifndef SRC_NOCOPY_H_
#define SRC_NOCOPY_H_

namespace bsk {

class NoCopy {
public:
   NoCopy();
   virtual ~NoCopy();
private:
   NoCopy (const NoCopy& copy);

};

} /* namespace bsk */

#endif /* SRC_NOCOPY_H_ */
