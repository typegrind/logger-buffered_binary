
#include "loader.h"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Converter requires one argument, a directory name!" << std::endl;
    }
    loader l(argv[1]);

    std::string dbName = std::string(argv[1]) + ".ejdb";

    if (argc >= 3)
    {
        dbName = argv[2];
    }

    l.writeDb(dbName);

}
