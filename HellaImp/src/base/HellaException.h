#pragma once
#include <string>
#include <wrl.h>
#include "Status.h"
#include "utils.h"


//failed.
#define HELLA_STATUS_FAILED(sta) (sta != Hella::Status::HELLA_OK && sta != Hella::Status::HELLA_TRUE )

#define HELLA_STATUS_JUDGE(x)                                              \
{                                                                                                           \
    std::string wfn = (__FILE__);                       \
    if(HELLA_STATUS_FAILED(x)) { throw Hella::HellaException(x, wfn, __LINE__); } \
}


/*
    @author:Haruluya.
    @function: exception for test.
*/
namespace Hella {

    class HellaException
    {
    public:
        HellaException() = default;
        HellaException(Status sta, const std::string& filename, int lineNumber);

        std::string ToString()const;

        Status m_ErrorCode = Status::HELLA_OK;
        std::string m_Filename;
        int m_LineNumber = -1;
    };
}