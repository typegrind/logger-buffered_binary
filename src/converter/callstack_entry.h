
#pragma once

#include <cstdint>
#include <unordered_map>

#include "typegrind/buffered_binary/log_entry.h"

struct callstack_entry
{
  uint64_t id;
  uint64_t timestamp;
  std::string locationStr;
  std::string targetName;
  std::string customName;
  uint64_t flags;

  callstack_entry* parent;

  callstack_entry(typegrind::buffered_binary::log_entry const& entry, callstack_entry* parent, std::unordered_map<uint64_t, std::string> const& stringTable);

  static uint64_t lastId;
};
