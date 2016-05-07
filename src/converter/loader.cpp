
#include "loader.h"

#include <deque>
#include <fstream>
#include <ejdb/ejdb.h>

#include <iostream>


namespace
{

  std::istream& operator >> (std::istream& in, typegrind::buffered_binary::log_entry& le)
  {
    in.read(reinterpret_cast<char*>(&le), sizeof(le));
    return in;
  }
}

loader::loader(std::string directory)
{
    unsigned loadingThread = 1;

    std::unordered_map<uint64_t, std::string> strings;
    while(
      loadStrings(directory, loadingThread, strings)
      && loadRun(directory, loadingThread, strings)
    ) loadingThread++;

    pairSamePointers();
}

bool  loader::loadStrings(std::string const& directory, unsigned threadId, std::unordered_map<uint64_t, std::string>& strings)
{
    std::ifstream f(directory + "/" + std::to_string(threadId) + ".str");
    if (!f.is_open()) return false;

    std::string str;
    while(std::getline(f, str))
    {
        auto delimPos = str.find(';');
        uint64_t ptr = std::stoul(str.substr(0, delimPos), nullptr, 16);
        strings.insert(std::pair<uint64_t, std::string>(ptr, str.substr(delimPos+1)));
    }

    return true;
}

bool loader::loadRun(std::string const& directory, unsigned threadId, std::unordered_map<uint64_t, std::string> const& strings)
{
    using namespace typegrind::logger;
    using namespace typegrind::buffered_binary;

    std::ifstream f(directory + "/" + std::to_string(threadId) + ".run", std::ios::binary);
    if (!f.is_open()) return false;

    std::deque< callstack_entry* > callstack;
    callstack_entry* currentFunction = nullptr;

    log_entry le;
    while(f >> le)
    {
      switch(le.entryType)
      {
        case NEW:
        case NEW_ARR:
        case OP_NEW:
        case OP_NEW_ARR:
        case DELETE:
        case DELETE_ARR:
        case OP_DELETE:
        case OP_DELETE_ARR:
          memoryEntries.push_back(memory_entry(le, currentFunction, strings));
        break;
        case FUNC_ENTER:
        std::cout << "cs enter" << std::endl;
          callstackEntries.push_back(std::make_unique<callstack_entry>(le, currentFunction, strings));
          currentFunction = callstackEntries.back().get();
          callstack.push_back(currentFunction);
          break;
        case FUNC_EXIT:
        std::cout << "cs exit" << std::endl;
          callstack.pop_back();
          currentFunction = callstack.empty() ? nullptr : callstack.back();
        break;
        case FUNC_AUTO_ENTER:
        case FUNC_AUTO_EXIT:
        // NOP
        break;
      }
    }

    return true;
}

void loader::pairSamePointers()
{

}

bool loader::writeDb(std::string dbname)
{
  EJDB *jb;

  jb = ejdbnew();

  if (!ejdbopen(jb, dbname.c_str(), JBOWRITER | JBOCREAT | JBOTRUNC))
  {
    return false;
  }

  EJCOLL *coll = ejdbcreatecoll(jb, "callstack", NULL);

  bson bsrec;
  bson_oid_t oid;

  for(auto const& ce: callstackEntries)
  {
    bson_init(&bsrec);
    //bson_append_string(&bsrec, )

    ejdbsavebson(coll, &bsrec, &oid);
    bson_destroy(&bsrec);
  }

  ejdbclose(jb);
}
