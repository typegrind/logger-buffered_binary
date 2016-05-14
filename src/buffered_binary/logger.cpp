
#include "typegrind/buffered_binary/logger.h"

#include <chrono>
#include <experimental/filesystem>
#include <string>

#include "typegrind/buffered_binary/thread_buffer.h"

namespace typegrind {
namespace buffered_binary {
std::string directoryCreator() {
  std::string directory(
      ".typegrind-" +
      std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
  // using std::experimntal instead of boost to avoid a library dependency for every project using
  // the logger
  std::experimental::filesystem::create_directory(directory);
  return directory;
}

thread_buffer& logger() {
  static std::string directory(directoryCreator());
  thread_local thread_buffer buffer(directory);
  return buffer;
}
}
}