#ifndef TYPEGRIND_BUFFERED_BINARY_H_H
#define TYPEGRIND_BUFFERED_BINARY_H_H

#define TYPEGRIND_LOG_NEW(locationStr, typeStr, canonicalTypeStr, typeSize, newExpression) (typegrind::logger::entry_alloc(typegrind::logger::NEW, typeStr, canonicalTypeStr, locationStr, static_cast<unsigned int>(typeSize)) * newExpression)
#define TYPEGRIND_LOG_NEW_ARRAY(locationStr, typeStr, canonicalTypeStr, typeSize, size, newExpression) (typegrind::logger::entry_alloc(typegrind::logger::NEW_ARR, typeStr, canonicalTypeStr, locationStr, static_cast<unsigned int>(size) * typeSize) * newExpression)
#define TYPEGRIND_LOG_OP_NEW(locationStr, typeStr, canonicalTypeStr, typeSize, size, newExpression) (typegrind::logger::entry_alloc(typegrind::logger::OP_NEW, typeStr, canonicalTypeStr, locationStr, static_cast<unsigned int>(size)) * newExpression)
#define TYPEGRIND_LOG_OP_NEW_ARRAY(locationStr, typeStr, canonicalTypeStr, typeSize, size, newExpression) (typegrind::logger::entry_alloc(typegrind::logger::OP_NEW_ARR, typeStr, canonicalTypeStr, locationStr, static_cast<unsigned int>(size)) * newExpression)

#define TYPEGRIND_LOG_DELETE(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free(typegrind::logger::DELETE, typeStr, canonicalTypeStr, locationStr) = deleteExpression)
#define TYPEGRIND_LOG_DELETE_ARRAY(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free(typegrind::logger::DELETE_ARR, typeStr, canonicalTypeStr, locationStr) = deleteExpression)
#define TYPEGRIND_LOG_OP_DELETE(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free(typegrind::logger::OP_DELETE, typeStr, canonicalTypeStr, locationStr) = deleteExpression)
#define TYPEGRIND_LOG_OP_DELETE_ARRAY(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free(typegrind::logger::OP_DELETE_ARR, typeStr, canonicalTypeStr, locationStr) = deleteExpression)

#define TYPEGRIND_LOG_FUNCTION_ENTER(locationStr, targetName, customName, flags) static typegrind::logger::method_scope typegrind_scope(targetName, locationStr, customName, flags); typegrind::logger::method_scope_guard typegrind_scope_guard(typegrind_scope);
#define TYPEGRIND_LOG_FUNCTION_AUTO_ENTER(locationStr, targetName) /* nop */

#define TYPEGRIND_CANONICAL_TYPE(typeName) (typegrind_logger_canonical_type< typeName >::name)
#define TYPEGRIND_SPECIFIC_TYPE(typeName, idx) (typegrind_logger_specific_type< typeName, idx >::name)

#define TYPEGRIND_STRINGIFY(P) #P
#define TYPEGRIND_CANONICAL_SPECIALIZATION(typeName) template<> const char* typegrind_logger_canonical_type< typeName >::name = TYPEGRIND_STRINGIFY(typeName)
#define TYPEGRIND_SPECIFIC_SPECIALIZATION(typeName, idx) template<> const char* typegrind_logger_specific_type< typeName, idx >::name = TYPEGRIND_STRINGIFY(typeName)

#define TYPEGRIND_TYPE(...) __VA_ARGS__

#define TYPEGRIND_RECORD_APPEND(loc) template<typename TYPEGRIND_PARAM> friend struct ::typegrind_logger_canonical_type; template<typename TYPEGRIND_PARAM1, int TYPEGRIND_PARAM2> friend struct ::typegrind_logger_specific_type;  

template<typename T>
struct typegrind_logger_canonical_type
{
    static const char* name;
};

template<typename T, int N>
struct typegrind_logger_specific_type
{
    static const char* name;
};

namespace typegrind
{
    namespace logger
    {
        struct entry_alloc;
        struct entry_free;
        struct method_scope;

        class buffered_binary
        {
        public:
            static void log(entry_alloc const& info);
            static void log(entry_free const& info);
        };

        typedef buffered_binary logger_implementation;

        enum entry_type {
            NEW,
            NEW_ARR,
            OP_NEW,
            OP_NEW_ARR,
            DELETE,
            DELETE_ARR,
            OP_DELETE,
            OP_DELETE_ARR,
            FUNC_ENTER,
            FUNC_EXIT,
            FUNC_AUTO_ENTER,
            FUNC_AUTO_EXIT
        };

        struct entry_alloc {
            entry_type entryType;
            const    char *typeStr;
            const char *canonicalTypeStr;
            const char *locationStr;
            const unsigned int size;
            const void *ptr;
            const method_scope* ownershipScope;

            entry_alloc(entry_type entryType, const char *typeStr, const char *canonicalTypeStr, const char *locationStr, const unsigned int size);
        };

        template<typename T>
        T* operator*(entry_alloc info, T* ptr)
        {
            info.ptr = ptr;
            logger_implementation::log(info);
            return ptr;
        }

        template<typename T>
        const T* operator*(entry_alloc info, const T* ptr)
        {
            info.ptr = ptr;
            logger_implementation::log(info);
            return ptr;
        }

        struct entry_free
        {
            entry_type entryType;
            const char*         typeStr;
            const char*         canonicalTypeStr;
            const char*         locationStr;
            const void*         ptr;

            entry_free(entry_type entryType, const char* typeStr, const char* canonicalTypeStr, const char* locationStr)
            : entryType(entryType)
            , typeStr(typeStr)
            , canonicalTypeStr(canonicalTypeStr)
            , locationStr(locationStr)
            , ptr(0)
            {}


            template<typename T>
            const T* operator=(const T* ptr)
            {
                this->ptr = ptr;
                logger_implementation::log(*this);
                return ptr;
            }

            template<typename T>
            T* operator=(T* ptr)
            {
                this->ptr = ptr;
                logger_implementation::log(*this);
                return ptr;
            }

        };

        struct method_scope
        {
            typedef unsigned long flags_type;

            const char*         targetName;
            const char*         locationStr;
            const char*         customName;
            flags_type          flags;

            method_scope(const char* targetName, const char* locationStr, const char* customName, flags_type flags);
        };

        extern thread_local const method_scope* currentScope;

        struct method_scope_guard
        {
            const method_scope* prevScope;


            inline method_scope_guard(method_scope const& scope)
                    :prevScope(currentScope)
            {
                currentScope = &scope;
            }

            inline ~method_scope_guard()
            {
                currentScope = prevScope;
            }
        };
    }

}

#endif //TYPEGRIND_BUFFERED_BINARY_H_H
