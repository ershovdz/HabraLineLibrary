#include "shared_storage.h"

#include <boost/interprocess/managed_shared_memory.hpp>

//#include <boost/interprocess/sync/scoped_lock.hpp>
//#include <boost/interprocess/sync/named_mutex.hpp>
//#include <boost/interprocess/exceptions.hpp>
//typedef scoped_lock<named_mutex> NamedMutexLocker;

using namespace boost::interprocess;

#define STORAGE_SIZE_IN_BYTES 2097152

static managed_shared_memory& shm()
{
  static managed_shared_memory instance = managed_shared_memory(open_or_create, "HABRASTORAGE", STORAGE_SIZE_IN_BYTES);
  return instance;
}

void SharedStorage::addData(const char* name, const std::string& serializedData)
{
  size_t necessaryBufSize = serializedData.length();

  std::pair<char*, std::size_t> existedBuffer = shm().find_no_lock<char>(name);
  char* sharedBuff = existedBuffer.first;
  
  if(!sharedBuff)
  {
    sharedBuff = shm().construct<char>(name)[necessaryBufSize]();
  }
  else if(sharedBuff && existedBuffer.second != necessaryBufSize)
  {
    shm().destroy<char>(name);
    sharedBuff = shm().construct<char>(name)[necessaryBufSize]();
  }

  _ASSERT(sharedBuff);

  std::copy( serializedData.begin(), serializedData.end(), sharedBuff );
}

void SharedStorage::removeData(const char* name)
{
  std::pair<char*, std::size_t> ret = shm().find_no_lock<char>(name);
  if(ret.first)
  {
    shm().destroy<char>(name);
  }
}

std::string SharedStorage::getData(const char* name)
{
  std::pair<char*, std::size_t> mem = shm().find<char>(name);
  
  if(mem.first)
  {
    std::string serializedData(mem.first, mem.second); 
    return serializedData;
  }

  return std::string();
}
