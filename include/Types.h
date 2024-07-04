#ifndef ORDERBOOK_TYPES_H
#define ORDERBOOK_TYPES_H

#include <cstdint>

/**
 * @file Types.h
 * @brief Defines custom types used in the order book system.
 */

/**
 * @typedef ID
 * @brief Represents a unique identifier for orders.
 */
using ID = std::uint64_t;

/**
 * @typedef Quantity
 * @brief Represents the quantity of orders or trades.
 */
using Quantity = std::uint32_t;

/**
 * @typedef Price
 * @brief Represents the price of orders or trades.
 */
using Price = std::uint32_t;

#endif //ORDERBOOK_TYPES_H
