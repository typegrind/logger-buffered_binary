#ifndef TYPEGRIND_LOGGER_COMMON_H_H
#define TYPEGRIND_LOGGER_COMMON_H_H

// common macros useful for any typegrind logger

// expands to another macro call with type parameters as decltype(expr)
#define TYPEGRIND_EXPAND_DECLTYPE(locationStr, macroName, positionCode, expr, ...)                 \
  macroName(                                                                                       \
      locationStr,                                                                                 \
      TYPEGRIND_TYPE(typegrind_static_type_info::typegrind_logger_canonical_type<decltype(expr)>), \
      TYPEGRIND_TYPE(typegrind_static_type_info::typegrind_logger_specific_type<decltype(expr),    \
                                                                                positionCode>),    \
      ##__VA_ARGS__, expr)

// expands to another macro call with type parameters as decltype(expr) and sizeof(expr)
#define TYPEGRIND_EXPAND_DECLTYPE_SIZEOF(locationStr, macroName, positionCode, expr, ...)          \
  macroName(                                                                                       \
      locationStr,                                                                                 \
      TYPEGRIND_TYPE(typegrind_static_type_info::typegrind_logger_canonical_type<decltype(expr)>), \
      TYPEGRIND_TYPE(typegrind_static_type_info::typegrind_logger_specific_type<decltype(expr),    \
                                                                                positionCode>),    \
      sizeof(decltype(expr)), ##__VA_ARGS__, expr)


// stringifies every argument
#define TYPEGRIND_STRINGIFY(...) #__VA_ARGS__

// wrapper macro used by clang-typegrind to avoid comma problems in typenames
#define TYPEGRIND_TYPE(...) __VA_ARGS__

#endif //TYPEGRIND_LOGGER_COMMON_H_H
