#pragma once

#include "hlpch.h"
#include "HellaException.h"
#include <comdef.h>

#include <typeinfo>


namespace Hella {
    HellaException::HellaException(Status sta, const std::string& filename, int lineNumber) :
        m_ErrorCode(sta),
        m_Filename(filename),
        m_LineNumber(lineNumber)
    {
    }


    std::string HellaException::ToString()const
    {
        // Get the string description of the error code.
        std::string msg = Hella::Util::GetStatusMsg(m_ErrorCode);

        return  "\n\tfailed in " + m_Filename + "\n\tline " + std::to_string(m_LineNumber) + "\n\terror: " + msg + "\n";
    }
    
}