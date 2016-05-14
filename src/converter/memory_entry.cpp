
#include "memory_entry.h"

memory_entry::memory_entry(typegrind::buffered_binary::log_entry const& entry, callstack_entry* cse,
                           std::unordered_map<uint64_t, std::string> const& stringTable)
    : id(++lastId)
    , entryType(entry.entryType)
    , timestamp(entry.timestamp)
    , locationStr(stringTable.at(entry.locationStr))
    , typeStr(stringTable.at(entry.typeStr_targetName))
    , canonicalTypeStr(stringTable.at(entry.canonicalTypeStr_customName))
    , ownerCustomName(entry.ownerCustomName_null ? stringTable.at(entry.ownerCustomName_null) : "")
    , ptr(entry.ptr_null)
    , size(entry.size_flags)
    , callstackPosition(cse)
    , allocationPair(nullptr)
    , deleteCount(0) {}

uint64_t memory_entry::lastId = 0;
