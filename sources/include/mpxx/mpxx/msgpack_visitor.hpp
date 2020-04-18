#ifndef __MSGPACK_VISITOR_HPP__
#define __MSGPACK_VISITOR_HPP__

#include <stdint.h>

#include <iostream>
#include <cstddef>
#include <type_traits>

#include <mpxx/msgpack.hpp>

namespace mpxx {

template <
    std::size_t Count,
    typename Packer
>
struct pack_visitor
{
    pack_visitor(Packer& p)
    : p_(p)
    { p_.pack_array(Count); }

    template <typename T>
    void operator()(T& v)
    {
        typename std::is_enum<T>::type tag;
        (*this)(v, tag);
    }

    template <typename T>
    void operator()(T& v, const std::false_type& tag)
    { p_.pack(v); }

    template <typename T>
    void operator()(T& v, const std::true_type& tag)
    {
        using type = typename std::underlying_type<T>::type;
        p_.pack(static_cast<type>(v));
    }

    Packer& p_;
};

template <std::size_t Count>
struct unpack_visitor
{
    unpack_visitor(const msgpack::object& o)
    : o_(o)
    {
        if (o_.type != msgpack::type::ARRAY) {
            throw msgpack::type_error();
        }

        size_ = o_.via.array.size;
    }

    template <typename T>
    void operator()(T& v, std::size_t pos)
    {
        if (pos > size_) {
            return;
        }

        typename std::is_enum<T>::type tag;
        (*this)(v, pos, tag);
    }

    template <typename T>
    void operator()(T& v, std::size_t pos, const std::false_type& tag)
    { o_.via.array.ptr[pos].convert(&v); }

    template <typename T>
    void operator()(T& v, std::size_t pos, const std::true_type& tag)
    {
        using type = typename std::underlying_type<T>::type;
        type tv;
        o_.via.array.ptr[pos].convert(&tv);

        v = std::move(static_cast<T>(tv));
    }

    const msgpack::object& o_;
    std::size_t size_;
};

template <std::size_t Count>
struct object_visitor
{
    object_visitor(msgpack::object* o, msgpack::zone* z)
    : o_(o),
    z_(z)
    {
        o_->type = msgpack::type::ARRAY;
        o_->via.array.ptr = (msgpack::object*) z->allocate_align(
            sizeof(msgpack::object) * Count
        );
        o_->via.array.size = Count;
    }

    template <typename T>
    void operator()(T& v, std::size_t pos)
    { o_->via.array.ptr[pos] = object(v, z_); }

    msgpack::object* o_;
    msgpack::zone* z_;
};

}   // namespace mpxx

#endif
