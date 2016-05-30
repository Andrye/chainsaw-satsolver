#ifndef _IO_UTILS_H
#define _IO_UTILS_H 1

#include <fstream>
#include <string>
#include <initializer_list>
#include <iostream>

template <typename ISTR, typename OSTR, typename ERRSTR>
class dimacsIO
{
    public:
        dimacsIO(ISTR& _istr, OSTR& _ostr, ERRSTR& _errstr) : istr(_istr), ostr(_ostr), errstr(_errstr)  {}

        void printComment(const std::string& comments) const
        {
            ostr << "c " << comments << std::endl;
        }

        template <typename Val>
            void printResult(const Val& val) const {
                ostr << "v ";
                for (const auto& v : val)
                    ostr << v << " ";
                ostr << std::endl;
            }
        void read() const
        {
            char op;
            std::string s1, s2;
            uint32_t i1, i2;
            while (!istr.eof())
            {
                istr >> op;
                switch (op)
                {
                    case 'c':
                        getline(istr, s1);
#ifdef VERBOSE
                        printComment(s1);
#endif
                        break;
                    case 'p':
                        istr >> s1 >> i1 >> i2;
#ifdef VERBOSE
                        printComment(" solving " + s1 + " formula with " +
                                     std::to_string(i1) + " variables and " + std::to_string(i2) + " caluses");
#endif                        
                        readFormula();
                        break;
                    
                }
            }
        }

    private:
        void readFormula() const
        {
            
        }

        ISTR& istr;
        OSTR& ostr;
        ERRSTR& errstr;
};

typedef dimacsIO<std::istream, std::ostream, std::ostream> cdimacsIO;
typedef dimacsIO<std::fstream, std::fstream, std::fstream> fdimacsIO;

cdimacsIO io(std::cin, std::cout, std::cerr);

#endif // _IO_UTILS_H
