#include "habra_line.h"

HabraLine::HabraLine()
  : _start(0,0)
  , _end(0,0)
{
#ifdef _DEBUG
  debugger::scope_helper<HabraLine> forDebugger(_debugHelper, this);
#endif
}

HabraLine::HabraLine(HabraPoint start, HabraPoint end)
  : _start(start)
  , _end(end)
{
#ifdef _DEBUG
  debugger::scope_helper<HabraLine> forDebugger(_debugHelper, this);
#endif
}

void HabraLine::modify(HabraPoint newStart, HabraPoint newEnd)
{
#ifdef _DEBUG
  debugger::scope_helper<HabraLine> forDebugger(_debugHelper, this);
#endif
  
  _start = newStart;
  _end = newEnd;
}


#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <sstream>

namespace boost
{
  namespace serialization
  {
    template<class Archive>
    void serialize(Archive & ar, HabraPoint& point, const unsigned int version)
    {
      ar & point._x;
      ar & point._y;
    }

    template<class Archive>
    void serialize(Archive & ar, HabraLine& line, const unsigned int version)
    {
      ar & line._start;
      ar & line._end;
    }
  }
}

std::string HabraLine::toString() const
{
  std::stringstream ss(std::ios::out | std::ios::binary);

  { 
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa & *this;
  }

  return ss.str();
}

std::shared_ptr<HabraLine> HabraLine::fromString(const std::string& serializedData)
{
  try
  {
    std::stringstream is(serializedData, std::ios_base::binary | std::ios_base::in);

    std::shared_ptr<HabraLine> spDeserializedLine = std::make_shared<HabraLine>();
    boost::archive::binary_iarchive ia(is, boost::archive::no_header);
    ia & *spDeserializedLine;
    return spDeserializedLine;
  }
  catch (std::exception&)
  {
  }

  return nullptr;
}


