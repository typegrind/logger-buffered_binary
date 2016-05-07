
#include "typegrind/buffered_binary/log_entry.h"

namespace typegrind
{
    namespace buffered_binary
    {
        log_entry::log_entry()
        {
            // no initialization required
        }

        log_entry::log_entry(typegrind::logger::entry_alloc const& info)
                : entryType(info.entryType)
                , timestamp(0) // TODO
                , typeStr_targetName(reinterpret_cast<uint64_t>(info.typeStr))
                , canonicalTypeStr_customName(reinterpret_cast<uint64_t>(info.canonicalTypeStr))
                , locationStr(reinterpret_cast<uint64_t>(info.locationStr))
                , ptr_null(reinterpret_cast<uint64_t>(info.ptr))
                , size_flags(static_cast<uint64_t>(info.size))
                , ownerTargetName_null(info.ownershipScope ? reinterpret_cast<uint64_t>(info.ownershipScope->targetName) : 0)
                , ownerCustomName_null(info.ownershipScope ? reinterpret_cast<uint64_t>(info.ownershipScope->customName) : 0)
                , ownerFlags_null(info.ownershipScope ? static_cast<uint64_t>(info.ownershipScope->flags) : 0)
        {
        }

        log_entry::log_entry(typegrind::logger::entry_free const& info)
                : entryType(info.entryType)
                , timestamp(0) // TODO
                , typeStr_targetName(reinterpret_cast<uint64_t>(info.typeStr))
                , canonicalTypeStr_customName(reinterpret_cast<uint64_t>(info.canonicalTypeStr))
                , locationStr(reinterpret_cast<uint64_t>(info.locationStr))
                , ptr_null(reinterpret_cast<uint64_t>(info.ptr))
                , size_flags(0)
                , ownerTargetName_null(0)
                , ownerCustomName_null(0)
                , ownerFlags_null(0)
        {
        }
    }
}
