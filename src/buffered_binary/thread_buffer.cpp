
#include "typegrind/buffered_binary/thread_buffer.h"

#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

namespace {
std::string thread_id_str(std::thread::id const& id) {
  static int i = 0;
  static std::mutex m;
  std::lock_guard<std::mutex> g(m);
  return std::to_string(++i);
}
};

namespace typegrind {
namespace buffered_binary {
thread_buffer::thread_buffer(std::string const& baseDirectory)
    : filenameBase(baseDirectory + "/" + thread_id_str(std::this_thread::get_id()))
    , currentIndex(0) {}

thread_buffer::~thread_buffer() {
  flushBuffer();
  flushStrings();
}

void thread_buffer::add_entry(typegrind::logger::entry_alloc const& info) {
  logBuffer[currentIndex++] = log_entry(info);
  strings.insert(info.locationStr);
  strings.insert(info.typeStr);
  strings.insert(info.canonicalTypeStr);
  if (info.ownershipScope) {
    strings.insert(info.ownershipScope->targetName);
    strings.insert(info.ownershipScope->customName);
  }

  if (currentIndex == 0) {
    flushBuffer();
  }
}

void thread_buffer::add_entry(typegrind::logger::entry_free const& info) {
  logBuffer[currentIndex++] = log_entry(info);
  strings.insert(info.locationStr);
  strings.insert(info.typeStr);
  strings.insert(info.canonicalTypeStr);
  if (currentIndex == 0) {
    flushBuffer();
  }
}

void thread_buffer::flushBuffer() const {
  auto f = fopen((filenameBase + ".run").c_str(), "a");
  fwrite(logBuffer, sizeof(log_entry), currentIndex == 0 ? 65536 : currentIndex, f);
  fclose(f);
}

void thread_buffer::flushStrings() const {
  auto f = fopen((filenameBase + ".str").c_str(), "w");
  for (auto str : strings) {
    fprintf(f, "%p;%s\n", str, str);
  }
  fclose(f);
}
}
}
