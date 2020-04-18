#ifndef __MPXX_DEFINE_H__
#define __MPXX_DEFINE_H__

#include <mpxx/tpl/tpl.hpp>
#include <mpxx/macros/fields.hpp>
#include <mpxx/macros/define_base.hpp>

/// @file
///
/// Message and structure definition macros

/// @brief Defines an mstruct type with the specified fields
/// @hideinitializer
/// @param NAME mstruct type name
/// @param FIELDS a preprocessor sequence of field definitions
/// @par Example
/// @code
/// MPXX_STRUCT(
///     my_struct,
///     (std::size_t, id),
///     (std::string, label)
/// );
/// @endcode
#define MPXX_STRUCT(NAME, ...) \
    MPXX_DEFINE_BASE( \
        mpxx::mstruct, \
        NAME, \
        __VA_ARGS__ \
    )

/// @brief Defines an msg (mstruct with MessagePack support) type with the specified fields
/// @hideinitializer
/// @param NAME message type name
/// @param FIELDS a preprocessor sequence of field definitions
/// @par Example
/// @code
/// MPXX_MSG(
///     my_msg,
///     (std::size_t, id),
///     (std::string, label)
/// );
/// @endcode
#define MPXX_MSG(NAME, ...) \
    MPXX_DEFINE_BASE( \
        mpxx::msg, \
        NAME, \
        __VA_ARGS__ \
    )

#endif // __MPXX_DEFINE_H__
