#include "utility.h"
#include <map>

QString convert_error(const core::Error& err)
{
    QString dst{err.msg};
    dst += "\n";

    using MAP_ERR_DESC = std::map<core::Error::TYPE, const char*>;

    static const MAP_ERR_DESC map{[]()
                                  {
                                      MAP_ERR_DESC map;
                                      map[core::Error::TYPE::UNKNOW]        = "Unknown error.";
                                      map[core::Error::TYPE::INVALID_ARG]   = "Invalid argument";
                                      map[core::Error::TYPE::INVALID_STATE] = "Invalid state";
                                      map[core::Error::TYPE::OUT_OF_BOUNDS] = "Index out of bounds";
                                      map[core::Error::TYPE::OUT_OF_MEMORY] = "Out of memory";
                                      map[core::Error::TYPE::TEST]          = "Test Error";
                                      return map;
                                  }()};

    dst += map.at(err.type);
    return dst;
}