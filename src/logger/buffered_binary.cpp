
#include "typegrind/logger/buffered_binary.h"
#include "typegrind/buffered_binary/thread_buffer.h"
#include "typegrind/buffered_binary/logger.h"

namespace typegrind
{
    namespace logger
    {
        void buffered_binary::log(entry_alloc const& info)
        {
            typegrind::buffered_binary::logger().add_entry(info);
        }

        void buffered_binary::log(entry_free const& info)
        {
            typegrind::buffered_binary::logger().add_entry(info);
        }



        thread_local const method_scope* currentScope = nullptr;

        entry_alloc::entry_alloc(entry_type entryType, const char *typeStr, const char *canonicalTypeStr, const char *locationStr, const unsigned int size)
        : entryType(entryType)
        , typeStr(typeStr)
        , canonicalTypeStr(canonicalTypeStr)
        , locationStr(locationStr)
        , size(size)
        , ptr(0)
        , ownershipScope(currentScope)
        {

        }

        method_scope::method_scope(const char* targetName, const char* locationStr, const char* customName, flags_type flags)
        : targetName(targetName)
        , locationStr(locationStr)
        , customName(customName)
        , flags(flags)
        {
        }

    }
}
