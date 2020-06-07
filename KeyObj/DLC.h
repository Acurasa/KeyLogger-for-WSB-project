#ifndef DLC_H
#define DLC_H

#include<string>
#include<ctime>
#include<fstream>
#include<sstream>
//#include<memory>

namespace DLC
{
    template<typename T>
    std::string ConvToString(const T &);

    struct DT //TODO (maybe class?)
    {
        int D,m,y,H,M,S;
        DT()
        {
            time_t localt;
            time(&localt);
            struct tm *gotinfo = localtime(&localt);

            D = gotinfo->tm_mday;
            m = gotinfo->tm_mon + 1;
            y = gotinfo->tm_year + 1900;
            M = gotinfo->tm_min;
            H = gotinfo->tm_hour;
            S = gotinfo->tm_sec;
        }

        DT(int D,int m,int y) : D(D),m(m),y(y),H(0),M(0),S(0) {};
        DT(int D,int m,int y,int H,int M,int S) : D(D),m(m),y(y),H(H),M(M),S(S) {};

        DT GetNow() const
            {
                return DT();
            }
         std::string GetDateAsString() const
         {
             /*if(D<10)
             {
                 return std::string "0" + ConvToString(D) +
             }
             else
             {
                 return std::string "" + ConvToString(D) +
             }*/
             return std::string(D<10?"0":"") + ConvToString(D) + std::string(m<10?".0":".") + ConvToString(m) + ConvToString(y);

         }
         std::string GetTimeAsString(const std::string &separate = ":") const
         {
           return std::string(H<10?"0":"") + ConvToString(H)+ separate + std::string(M<10?"0":"") + ConvToString(M)+ separate + std::string(S<10?"0":"") +  ConvToString(S);

         }
         std::string GetDtAsString(const std::string &separate = ":")
         {
            return GetDateAsString() + "    " + GetTimeAsString(separate);
         }


    };
    template <typename T>
    std::string ConvToString(const T &e)
    {
        std::ostringstream s;
        s << e;
        return s.str();
    }

    void ApplicationLogCreate (const std::string &s)
    {
        std::ofstream file("ApplicationLog.txt",std::ios::app);
        file << "[" << DT().GetDtAsString()<<"]"<<"\n"<<s<<"\n\n";
        file.close();
    }
}

#endif // DLC_H
