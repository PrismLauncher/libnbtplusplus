/*
 * libnbt++ - A library for the Minecraft Named Binary Tag format.
 * Copyright (C) 2013, 2015  ljfa-ag
 *
 * This file is part of libnbt++.
 *
 * libnbt++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnbt++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libnbt++.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "value.h"
#include "nbt_tags.h"
#include <typeinfo>
#include <algorithm>
#include <initializer_list>
#include <cstdint>
#include <memory>

namespace nbt
{

value::value(tag&& t):
    tag_(std::move(t).move_clone())
{}

value::value(const value& rhs):
    tag_(rhs.tag_ ? rhs.tag_->clone() : nullptr)
{}

value& value::operator=(const value& rhs)
{
    if(this != &rhs)
    {
        tag_ = rhs.tag_ ? rhs.tag_->clone() : nullptr;
    }
    return *this;
}

value& value::operator=(tag&& t)
{
    set(std::move(t));
    return *this;
}

void value::set(tag&& t)
{
    if(tag_)
        tag_->assign(std::move(t));
    else
        tag_ = std::move(t).move_clone();
}

//Primitive assignment
namespace // helper functions local to this translation unit
{
    template<typename T>
    void assign_numeric_impl(std::unique_ptr<tag>& tag_ptr, T val,
                             tag_type default_type)
    {
        using nbt::tag_type;
        if(!tag_ptr)
        {
            tag_ptr = tag::create(default_type, val);
            return;
        }

        // Determine the incoming tag type for T
        auto incoming_type = detail::get_primitive_type<T>::value;

        // If the existing tag is of a narrower type than the incoming type,
        // reject the assignment to avoid widening the stored tag type.
        auto existing_type = tag_ptr->get_type();

        if(static_cast<int>(existing_type) < static_cast<int>(incoming_type))
        {
            throw std::bad_cast();
        }

        // Existing type is same or wider: write into the existing tag (may narrow)
        switch(existing_type)
        {
        case tag_type::Byte: static_cast<tag_byte&>(*tag_ptr).set(static_cast<int8_t>(val)); break;
        case tag_type::Short: static_cast<tag_short&>(*tag_ptr).set(static_cast<int16_t>(val)); break;
        case tag_type::Int: static_cast<tag_int&>(*tag_ptr).set(static_cast<int32_t>(val)); break;
        case tag_type::Long: static_cast<tag_long&>(*tag_ptr).set(static_cast<int64_t>(val)); break;
        case tag_type::Float: static_cast<tag_float&>(*tag_ptr).set(static_cast<float>(val)); break;
        case tag_type::Double: static_cast<tag_double&>(*tag_ptr).set(static_cast<double>(val)); break;
        default: throw std::bad_cast();
        }
    }
}

value& value::operator=(int8_t val)
{
    assign_numeric_impl(tag_, val, tag_type::Byte);
    return *this;
}

value& value::operator=(int16_t val)
{
    assign_numeric_impl(tag_, val, tag_type::Short);
    return *this;
}

value& value::operator=(int32_t val)
{
    assign_numeric_impl(tag_, val, tag_type::Int);
    return *this;
}

value& value::operator=(int64_t val)
{
    assign_numeric_impl(tag_, val, tag_type::Long);
    return *this;
}

value& value::operator=(float val)
{
    assign_numeric_impl(tag_, val, tag_type::Float);
    return *this;
}

value& value::operator=(double val)
{
    assign_numeric_impl(tag_, val, tag_type::Double);
    return *this;
}

//Primitive conversion
value::operator int8_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator int16_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator int32_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator int64_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();
    case tag_type::Long:
        return static_cast<tag_long&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator float() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();
    case tag_type::Long:
        return static_cast<tag_long&>(*tag_).get();
    case tag_type::Float:
        return static_cast<tag_float&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator double() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();
    case tag_type::Long:
        return static_cast<tag_long&>(*tag_).get();
    case tag_type::Float:
        return static_cast<tag_float&>(*tag_).get();
    case tag_type::Double:
        return static_cast<tag_double&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value& value::operator=(std::string&& str)
{
    if(!tag_)
        set(tag_string(std::move(str)));
    else
        dynamic_cast<tag_string&>(*tag_).set(std::move(str));
    return *this;
}

value::operator const std::string&() const
{
    return dynamic_cast<tag_string&>(*tag_).get();
}

value& value::at(const std::string& key)
{
    return dynamic_cast<tag_compound&>(*tag_).at(key);
}

const value& value::at(const std::string& key) const
{
    return dynamic_cast<const tag_compound&>(*tag_).at(key);
}

value& value::operator[](const std::string& key)
{
    return dynamic_cast<tag_compound&>(*tag_)[key];
}

value& value::operator[](const char* key)
{
    return (*this)[std::string(key)];
}

value& value::at(size_t i)
{
    return dynamic_cast<tag_list&>(*tag_).at(i);
}

const value& value::at(size_t i) const
{
    return dynamic_cast<const tag_list&>(*tag_).at(i);
}

value& value::operator[](size_t i)
{
    return dynamic_cast<tag_list&>(*tag_)[i];
}

const value& value::operator[](size_t i) const
{
    return dynamic_cast<const tag_list&>(*tag_)[i];
}

tag_type value::get_type() const
{
    return tag_ ? tag_->get_type() : tag_type::Null;
}

bool operator==(const value& lhs, const value& rhs)
{
    if(lhs.tag_ != nullptr && rhs.tag_ != nullptr)
        return *lhs.tag_ == *rhs.tag_;
    else
        return lhs.tag_ == nullptr && rhs.tag_ == nullptr;
}

bool operator!=(const value& lhs, const value& rhs)
{
    return !(lhs == rhs);
}

}
