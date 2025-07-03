/*
 * Error.h
 *
 *  Created on: Jul 3, 2025
 *      Author: Jakub
 */

#ifndef BRD_ERROR_H_
#define BRD_ERROR_H_

class Error
{
  public:
    Error();
    virtual ~Error();
    bool is_error = false;
    enum
    {

    };
};
Error inline error;
#endif /* BRD_ERROR_H_ */
