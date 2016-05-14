
#include "callstack_entry.h"

callstack_entry::callstack_entry(typegrind::buffered_binary::log_entry const& entry,
                                 callstack_entry* parent,
                                 std::unordered_map<uint64_t, std::string> const& stringTable)
    : id(++lastId)
    , timestamp(entry.timestamp)
    , locationStr(stringTable.at(entry.locationStr))
    , targetName(stringTable.at(entry.typeStr_targetName))
    , customName(stringTable.at(entry.canonicalTypeStr_customName))
    , flags(entry.size_flags)
    , parent(parent) {}

uint64_t callstack_entry::lastId = 0;
