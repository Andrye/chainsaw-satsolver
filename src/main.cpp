#include "sat_include_all.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    solver s;
    s.solve();
    io.read();
}
