#ifndef BASE64_H

#define BASE64_H

#include<vector>
#include<string>

namespace Base64
{
    std::string base64_enc(const std::string &);    //to encrypt

    const std::string &K1="WSHD::DHFG::RYFG";
    const std::string &K2="@;.__/::";
    const std::string &K3="gkh;'_/";

    std::string enc(const std::string &sc)   //masking string
    {
        std::string s=sc;
        //pass1
        s=K1+s+K2+K3;       //changing string
        s=base64_enc(s);    //encoding 1
        s.insert(7,K1);     //again changing
        //pass2
        s+=K1;
        s=base64_enc(s);
        s=K3+s+K2+K1;
        //pass3
        s=base64_enc(s);
        s.insert(10,K3);
        s.insert(1,"lku");

        return s;
    }

    const std::string &bcodes = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64_enc(const std::string &s)    //to encrypt
    {
        std::string r;
        int v=0,b=-6;
        const unsigned int b64=0x3F;

        for(const auto &c:s)
        {
            v=(v<<8)+c;
            b+=8;
            while(b>=0)
            {
                r.push_back(bcodes[(v>>b) & b64]);
                b-=6;
            }

        }

        if(b>-6)
        {
            r.push_back(bcodes[((v<<8)>>(b+8)) & b64]);
        }

        while(r.size()%4)
            r.push_back('=');

        return r;

    }

}

#endif // BASE64_H
