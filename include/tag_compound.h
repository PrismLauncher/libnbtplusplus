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
#ifndef TAG_COMPOUND_H_INCLUDED
#define TAG_COMPOUND_H_INCLUDED

#include "tag.h"
#include <map>
#include <memory>
#include <string>

namespace nbt
{

//TODO: Create actual proxy class
typedef tag& tag_ref_proxy;
typedef const tag& const_tag_ref_proxy;

///Tag that contains multiple unordered named tags of arbitrary types
class tag_compound : public tag
{
public:
    //Iterator types
    typedef void* iterator; //FIXME
    typedef const void* const_iterator;

    ///The type of the tag
    static constexpr tag_type type = tag_type::Compound;

    ///Constructs an empty compound
    tag_compound() {}

    /**
     * @brief Accesses a tag by key with bounds checking
     *
     * Returns a reference to the tag with the specified key, or throws an
     * exception if it does not exist.
     * @throw std::out_of_range if given key does not exist
     */
    tag& at(const std::string& key);
    const tag& at(const std::string& key) const;

    /**
     * @brief Accesses a tag by key
     *
     * Returns a proxy value that can be converted to @ref tag&.
     */
    tag_ref_proxy operator[](const std::string& key);
    const_tag_ref_proxy operator[](const std::string& key) const;

    /**
     * @brief Inserts a tag into the compound
     *
     * If the given key does not already exist, moves the pointed tag
     * into the compound.
     * @return true if the tag was inserted
     */
    bool insert(const std::string& key, std::unique_ptr<tag>&& ptr);

    /**
     * @brief Inserts or assigns a tag
     *
     * If the given key already exists, assigns the pointed tag to it.
     * Otherwise, it is inserted under the given key.
     * @return true if the key did not exist
     */
    bool put(const std::string& key, std::unique_ptr<tag>&& ptr);

    /**
     * @brief Constructs and inserts a tag into the compound
     *
     * If the given key does not exist, constructs a new tag of type @c T
     * with the given args and inserts it into the compound.
     * @return true if the tag was inserted
     */
    template<class T, class... Args>
    bool emplace(const std::string& key, Args&&... args);

    /**
     * @brief Constructs and assigns or inserts a tag into the compound
     *
     * Constructs a new tag of type @c T with the given args and inserts
     * or assigns it to the given key.
     * @return true if the key did not already exist.
     */
    template<class T, class... Args>
    bool emplace_put(const std::string& key, Args&&... args);

    /**
     * @brief Erases a tag from the compound
     * @return true if a tag was erased
     */
    bool erase(const std::string& key);

    ///Returns true if the given key exists in the compound
    bool has_key(const std::string& key);

    ///Returns the number of tags in the compound
    size_t size() const;

    ///Erases all tags from the compound
    void clear();

    //Iterators
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    tag_type get_type() const noexcept override;

private:

};

}

#endif // TAG_COMPOUND_H_INCLUDED