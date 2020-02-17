#ifndef HELPER_H

#define HELPER_H
#include<string>
#include<ctime>
#include<sstream>
#include<fstream>

namespace HELPER
{
    template <class T>
    std::string tostring(const T &);    //function to change any type to string
    struct datetime
    {
        int S,M,H,D,m,y;
        datetime()
        {
            time_t ms;
            time(&ms);
            struct tm *info = localtime(&ms);

            S=info->tm_sec;
            M=info->tm_min;
            H=info->tm_hour;
            D=info->tm_mday;
            m=info->tm_mon+1;
            y=info->tm_year+1900;
        }
        datetime(int S,int M,int H,int D,int m,int y) : S(S),M(M),H(H),D(D),m(m),y(y) {}
        datetime(int D,int m,int y) : D(D),m(m),y(y),S(0),M(0),H(0) {}

        const datetime Now()
        {
            return datetime();
        }

        //date in formate DD.mm.yyyy
        const std::string getdatestring()
        {
            return (std::string (D<10?"0":"") + tostring(D) + std::string(m<10?".0":".") + tostring(m) + "." + tostring(y));
        }

        //time in formate HH:MM:SS
        const std::string gettimestring(const std::string &sep=":")
        {
            return (std::string (H<10?"0":"") + tostring(H) + sep + std::string(M<10?"0":"") + tostring(M) + sep + tostring(S));
        }

        //combine date time
        const std::string getdatetimestring(const std::string &sep=":")
        {
            return getdatestring() + " " + gettimestring(sep);
        }

    };

    void p_log_file(const std::string &log) //error records
    {
        std::ofstream file;
        file.open("log.txt",std::ios::app);
        file<<"["<<HELPER::datetime().getdatetimestring()<<"]\t\t"<<log<<std::endl;
        file.close();
    }

    template <class T>
    std::string tostring(const T &e)    //function to change any type to string
    {
        std::ostringstream s;
        s<<e;
        return s.str();
    }
}

#endif // HELPER_H
