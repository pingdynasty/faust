/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _FAUST_EXCEPTION_
#define _FAUST_EXCEPTION_

#include <stdexcept>
#include <iostream>
#include <unistd.h>

#ifndef EMCC
#include <execinfo.h>
#endif

class faustexception : public std::runtime_error {

    public:

    #ifdef EMCC
        static const char* gJSExceptionMsg;
    
        faustexception(const std::string& msg):std::runtime_error(msg)
        {
            gJSExceptionMsg = strdup(msg.c_str());
        }
        faustexception(char* msg):std::runtime_error(msg)
        {
            gJSExceptionMsg = strdup(msg);
        }
        faustexception(const char* msg):std::runtime_error(msg)
        {
            gJSExceptionMsg = strdup(msg);
        }
    #else
        faustexception(const std::string& msg):std::runtime_error(msg)
        {}
        faustexception(char* msg):std::runtime_error(msg)
        {}
        faustexception(const char* msg):std::runtime_error(msg)
        {}
    #endif

        std::string Message()
        {
            return what();
        }

        void PrintMessage()
        {
            std::cerr << what();
        }
};

inline void faustassert(bool cond)
{
    if (!cond) {
    #ifndef EMCC
        void* array[20];
        backtrace_symbols_fd(array, backtrace(array, 20), STDERR_FILENO);
    #endif
        throw faustexception("ASSERT : please report the stack trace and the failing DSP file to Faust developers.\n");
    }
}
            
            

#endif
