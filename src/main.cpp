#include "sat_include_all.h"
#include <unistd.h>
#include <sstream>

int main(int argc, char* argv[])
{
    stringstream sstr;
    sstr << "c to jest komentarz" << std::endl;
    sstr << "c to jest drugi komentarz" << std::endl;
    sstr << "p cnf 77 12";
    dimacsIO<std::stringstream, std::ostream, std::ostream> _io(sstr, std::cout, std::cerr);
    _io.read<clause>();
}
