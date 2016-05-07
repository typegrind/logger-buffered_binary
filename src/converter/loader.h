
#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "memory_entry.h"
#include "callstack_entry.h"

class loader
{
public:
    loader(std::string directory);
    
    bool writeDb(std::string dbname);
private:

    static bool loadStrings(std::string const& directory, unsigned threadId, std::unordered_map<uint64_t, std::string>& strings);
    bool loadRun(std::string const& directory, unsigned threadId, std::unordered_map<uint64_t, std::string> const& strings);

    void pairSamePointers();


    std::vector<std::unique_ptr<callstack_entry>> callstackEntries;
    std::vector<memory_entry> memoryEntries;
};
