
#pragma once

#include <cstdint>
#include <unordered_map>

#include "typegrind/buffered_binary/log_entry.h"

struct callstack_entry;

struct memory_entry
{
  uint64_t id;
  typegrind::logger::entry_type entryType;
  uint64_t timestamp;
  std::string locationStr;
  std::string typeStr;
  std::string canonicalTypeStr;
  std::string ownerCustomName;
  uint64_t ptr;
  uint64_t size;

  callstack_entry* callstackPosition;

  // postprocessed
  memory_entry* allocationPair;
  unsigned deleteCount;

  memory_entry(typegrind::buffered_binary::log_entry const& entry, callstack_entry* cse, std::unordered_map<uint64_t, std::string> const& stringTable);

  static uint64_t lastId;
};
