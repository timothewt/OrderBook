#ifndef ORDERBOOK_TYPES_H
#define ORDERBOOK_TYPES_H

#include <cstdint>

using ID = std::uint64_t;
using Price = std::uint32_t;
using Volume = std::uint64_t;
using Length = std::uint64_t;

enum OrderType { BUY, SELL };

#endif //ORDERBOOK_TYPES_H
