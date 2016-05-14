#ifndef TYPEGRIND_LOG_ENTRY_H
#define TYPEGRIND_LOG_ENTRY_H

#include <cstdint>

#include "typegrind/logger/buffered_binary.h"

namespace typegrind {
namespace buffered_binary {
struct log_entry {
  typegrind::logger::entry_type entryType;  // keep it at 64 bit for simplicity
  uint64_t timestamp;
  uint64_t locationStr;
  uint64_t typeStr_targetName;
  uint64_t canonicalTypeStr_customName;
  uint64_t ptr_null;
  uint64_t size_flags;
  uint64_t ownerTargetName_null;
  uint64_t ownerCustomName_null;
  uint64_t ownerFlags_null;

  log_entry();
  log_entry(typegrind::logger::entry_alloc const& info);
  log_entry(typegrind::logger::entry_free const& info);
};
}
}

#endif  // TYPEGRIND_LOG_ENTRY_H
