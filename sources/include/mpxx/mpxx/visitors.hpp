#ifndef __MPXX_VISITORS_H__
#define __MPXX_VISITORS_H__

#include <stdint.h>

#include <iostream>
#include <cstddef>
#include <type_traits>

namespace mpxx {

/// @file
///
/// standard mstruct visitors
/// @anchor visit_tags Visit tags

/// Visit by field value
struct value_visit {};
/// Visit by field position
struct pos_visit {};
/// Visit by field value and position
struct value_pos_visit {};
/// Visit by field name, field value and position
struct name_value_pos_visit {};
/// Visit by field and position
struct field_pos_visit {};

template <std::size_t Count>
struct describe_visitor
{
    describe_visitor(std::ostream& os)
    : os_(os)
    {}

    void operator()(const char* name, const uint8_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":uint8"; }

    void operator()(const char* name, const int8_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":sint8"; }

    void operator()(const char* name, const uint16_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":uint16"; }

    void operator()(const char* name, const int16_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":sint16"; }

    void operator()(const char* name, const uint32_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":uint32"; }

    void operator()(const char* name, const int32_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":sint32"; }

    void operator()(const char* name, const uint64_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":uint64"; }

    void operator()(const char* name, const int64_t&, std::size_t pos)
    { os_ << sep(pos) << name << ":sint64"; }

    void operator()(const char* name, const float&, std::size_t pos)
    { os_ << sep(pos) << name << ":flt"; }

    void operator()(const char* name, const double&, std::size_t pos)
    { os_ << sep(pos) << name << ":dbl"; }

    void operator()(const char* name, const std::string&, std::size_t pos)
    { os_ << sep(pos) << name << ":string"; }

    void operator()(const char* name, const char*&, std::size_t pos)
    { os_ << sep(pos) << name << ":string"; }

    template <typename T>
    void operator()(const char* name, const T& v, std::size_t pos)
    { os_ << sep(pos) << name << ":unknown"; }

    const char* sep(std::size_t pos) const
    { return (pos > 0 ? "," : ""); }

    std::ostream& os_;
};

} // namespace mpxx

#endif // __MPXX_VISITORS_H__
