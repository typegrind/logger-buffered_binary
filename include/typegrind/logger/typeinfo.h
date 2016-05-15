#ifndef TYPEGRIND_LOGGER_TYPEINFO_H_H
#define TYPEGRIND_LOGGER_TYPEINFO_H_H

// defines and classes for handling template types

// _TYPE macros are used by other macros
// _SPECIALIZATION macros are added at the end of the source

// basic idea:
// * we can't define a specialized template after it is used, but we can add a new specialization to
// a static const member variable
// * extern C context doesn't allow templates (even for friends), so we have to wrap it in a
// non-template struct.

// canonical typename based on a static structure
#define TYPEGRIND_CANONICAL_TYPE(typeName) \
  (::typegrind_static_type_info::canonical_type<typeName>::name)

// specific (typedef) typename based on a static structure
#define TYPEGRIND_SPECIFIC_TYPE(typeName, idx) \
  (::typegrind_static_type_info::specific_type<typeName, idx>::name)

// adds a new canonical name to the static structure
#define TYPEGRIND_CANONICAL_SPECIALIZATION(typeName)                       \
  template <>                                                              \
  const char* typegrind_static_type_info::canonical_type<typeName>::name = \
      TYPEGRIND_STRINGIFY(typeName)

// adds a new specific name to the static structure
#define TYPEGRIND_SPECIFIC_SPECIALIZATION(typeName, specName, idx)             \
  template <>                                                                  \
  const char* typegrind_static_type_info::specific_type<typeName, idx>::name = \
      TYPEGRIND_STRINGIFY(specName)

// C++ structs/classes should be friends of our static structure
#define TYPEGRIND_RECORD_APPEND(loc) friend struct ::typegrind_static_type_info;

// C structs/classes should be friends of our static structure
#define TYPEGRIND_RECORD_APPEND_C(loc) friend struct ::typegrind_static_type_info;

struct typegrind_static_type_info {
  template <typename T>
  struct canonical_type {
    static const char* name;
  };

  template <typename T, int N>
  struct specific_type {
    static const char* name;
  };
};

#endif  // TYPEGRIND_LOGGER_TYPEINFO_H_H
