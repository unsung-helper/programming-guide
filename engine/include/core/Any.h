/*
 * Copyright (c) 2024-2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */

#pragma once

#include <any>
#include <cassert>
#include <functional>
#include <memory>
#include <type_traits>
#include <typeindex>

namespace us {

template<typename T, typename = void>
struct has_equality_operator : std::false_type
{};

template<typename T>
struct has_equality_operator<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>>
    : std::true_type
{};

template<typename T, typename = void>
struct has_std_hash : std::false_type
{};

template<typename T>
struct has_std_hash<T, std::void_t<decltype(std::declval<std::hash<T>>()(std::declval<T>()))>>
    : std::true_type
{};

template<typename T>
inline constexpr bool has_std_hash_function = has_std_hash<T>::value;

class Any
{
public:

    Any();

    Any(const char *aValue);

    template <typename T> Any(std::shared_ptr<T> aValue);

    template <typename T> Any(T aValue );

    template <typename T> Any(std::unique_ptr<T> aValue );

    template <typename T> Any(T *aValue );

    Any(const Any & aOther) = default;
    Any( Any && aOther) = default;
    Any & operator = (const Any & aOther) = default;
    Any & operator = (Any && aOther) = default;

    bool operator==(const Any &aOther) const;

    bool operator!=(const Any &aOther) const;

    /**
     * Returns the instance held by this Any.
     */
    template <typename T> T get() const;

    /**
     * Returns a pointer to the data held by this Any.
     */
    template <typename T> T* data();

    /**
     * Returns a pointer to the data held by this Any.
     */
    template <typename T> const T* data() const;

    /**
     * Returns whether this Any holds a value of given type
     */
    template <typename T> bool holdsType() const;

    /**
     * Returns the type held by this Any
     */
    std::type_index type() const;
    /**
     * Returns true if this Any does not hold anything
     */
    bool empty() const;

    /**
     * Creates a deep copy of this Any
     */
    Any clone() const;

private:
    friend struct std::hash<Any>;

    //value
    std::any _value;
    //strategy used to create a deep copy of this Any
    using CloneFunction = std::function<Any(const Any &)>;
    CloneFunction _cloneFunction;
    //strategy to check for equality
    using EqualsFunction = std::function<bool(const Any &, const Any &)>;
    EqualsFunction _equalsFunction;
    using HashFunction = std::function<std::size_t(const Any &)>;
    HashFunction _hashFunction;
};


//TEMPLATE IMPLEMENTATIONS
template<typename T> bool Any::holdsType() const {
    return type() == typeid(T);
}

template<typename T> const T *Any::data() const {
    if(!_value.has_value()){
        return nullptr;
    }
    try{
        return std::any_cast<T>(&_value);
    }catch(...){
        return nullptr;
    }
}

template<typename T> T *Any::data() {
    if(!_value.has_value()){
        return nullptr;
    }
    try{
        return std::any_cast<T>(&_value);
    }catch(...){
        return nullptr;
    }
}

template<typename T>
T Any::get() const
{
    if (!_value.has_value()) {
        return T();
    }
    try {
        return std::any_cast<T>(_value);
    } catch (...) {
        return T();
    }
}

template<>
std::type_index Any::get() const;

template<typename T>
Any::Any(T *aValue)
{
    assert(false);
}

template<typename T> Any::Any(std::unique_ptr<T> aValue)
{
    assert(false);
}

template<typename T>
Any::Any(T aValue)
    : _value(aValue)
    , _cloneFunction([](const Any &aSource) { return Any(aSource.get<T>()); })
    , _equalsFunction([](const Any &aFirst, const Any &aSecond) {
        if (aFirst.type() != aSecond.type()) {
            return false;
        }
        if constexpr (has_equality_operator<T>::value) {
            return aFirst.get<T>() == aSecond.get<T>();
        } else {
            return false;
        }
    })
    , _hashFunction([](const Any &aVal) -> size_t {
        if constexpr (has_std_hash_function<T>) {
            return std::hash<T>()(aVal.get<T>());
        }
        return 0;
    })
{}

template<typename T> Any::Any(std::shared_ptr<T> aValue)
    : _value(aValue)
{
    T * ptr = aValue.get();
    _cloneFunction = [ptr](const Any &aSource) {
        return (ptr != nullptr) ? Any(std::make_shared<T>(*ptr)) : Any(std::shared_ptr<T>(nullptr));
    };
    _equalsFunction = [ptr](const Any &aFirst, const Any &aSecond) {
        if (aFirst.type() != aSecond.type()) {
            return false;
        }
        return aFirst.get<std::shared_ptr<T>>().get() == aSecond.get<std::shared_ptr<T>>().get();
    };
    _hashFunction = [](const Any &aVal) -> size_t {
        return std::hash<T *>()(aVal.get<std::shared_ptr<T>>().get());
    };
}


} // namespace us

namespace std {
template<>
struct hash<us::Any>
{
    std::size_t operator()(const us::Any &aValue) const;
};
} // namespace std
