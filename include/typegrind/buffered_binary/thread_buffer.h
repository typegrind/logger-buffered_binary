
#ifndef TYPEGRIND_THREAD_BUFFER_H
#define TYPEGRIND_THREAD_BUFFER_H

#include <string>
#include <unordered_set>

#include "log_entry.h"

namespace typegrind {
namespace buffered_binary {
struct thread_buffer {
  static const int bufferSize = 65536;

  std::string filenameBase;

  uint16_t currentIndex;
  log_entry logBuffer[bufferSize];

  std::unordered_set<const char*> strings;

  thread_buffer(std::string const& baseDirectory);
  ~thread_buffer();

  thread_buffer(thread_buffer const& other) = delete;
  thread_buffer const& operator=(thread_buffer const& other) = delete;

  void add_entry(typegrind::logger::entry_alloc const& info);
  void add_entry(typegrind::logger::entry_free const& info);

  void flushBuffer() const;
  void flushStrings() const;
};
}
}

#endif  // TYPEGRIND_THREAD_BUFFER_H
