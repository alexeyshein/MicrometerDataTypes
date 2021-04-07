#pragma once

namespace rf
{
class IData
{
  public:
  virtual ~IData()=default;
  virtual uint64_t Id() const = 0 ;
};
}

