#pragma once

#include <type_traits>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <tuple>
#include <string>
#include <optional>
#include <memory>
#include <forward_list>
#include <variant>

namespace otas_serializer {

// Maximum number of members allowed in a serializable struct
static constexpr std::size_t MAX_MEMBER_COUNT = 16;

// Forward declaration for is_serializable
template <class T, class = void>
struct is_serializable_impl : std::false_type {};

// Helper to check if type has only default constructor or no constructor
template <class T, class = void>
struct has_only_default_constructor : std::false_type {};

template <class T>
struct has_only_default_constructor<T, std::void_t<
    std::enable_if_t<std::is_default_constructible_v<T> && std::is_aggregate_v<T>>
>> : std::true_type {};

// Helper to check if type contains raw pointers
template <class T>
struct contains_raw_pointer : std::false_type {};

template <class T>
struct contains_raw_pointer<T*> : std::true_type {};

// Helper to check if type is a derived class
template <class T>
struct is_derived_class : std::conditional_t<
    std::is_class_v<T> && std::is_polymorphic_v<T>,
    std::true_type,
    std::false_type
> {};

// Helper to check if type is supported STL container
template <class T>
struct is_supported_stl_container : std::false_type {};

// Specialize for supported containers
template <class T, class Alloc>
struct is_supported_stl_container<std::vector<T, Alloc>> : std::true_type {};

template <class T, class Alloc>
struct is_supported_stl_container<std::list<T, Alloc>> : std::true_type {};

template <class Key, class T, class Compare, class Alloc>
struct is_supported_stl_container<std::map<Key, T, Compare, Alloc>> : std::true_type {};

template <class Key, class T, class Hash, class KeyEqual, class Alloc>
struct is_supported_stl_container<std::unordered_map<Key, T, Hash, KeyEqual, Alloc>> : std::true_type {};

template <class Key, class Compare, class Alloc>
struct is_supported_stl_container<std::set<Key, Compare, Alloc>> : std::true_type {};

template <class Key, class Hash, class KeyEqual, class Alloc>
struct is_supported_stl_container<std::unordered_set<Key, Hash, KeyEqual, Alloc>> : std::true_type {};

template <class T, std::size_t N>
struct is_supported_stl_container<std::array<T, N>> : std::true_type {};

template <class... Args>
struct is_supported_stl_container<std::tuple<Args...>> : std::true_type {};

template <class T, class U>
struct is_supported_stl_container<std::pair<T, U>> : std::true_type {};

// Helper to check member count using aggregate initialization
namespace detail {
    struct any_type {
        template<typename T>
        constexpr operator T(); // non-explicit
    };
    
    template<typename T, std::size_t N, typename = void>
    struct is_aggregate_constructible_with_n : std::false_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 0, std::void_t<decltype(T{})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 1, std::void_t<decltype(T{any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 2, std::void_t<decltype(T{any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 3, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 4, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 5, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 6, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 7, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 8, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 9, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 10, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 11, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 12, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 13, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 14, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 15, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 16, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T>
    struct is_aggregate_constructible_with_n<T, 17, std::void_t<decltype(T{any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}, any_type{}})>> : std::true_type {};
    
    template<typename T, std::size_t N>
    constexpr std::size_t count_aggregate_members() {
        if constexpr (N > MAX_MEMBER_COUNT + 1) {
            return MAX_MEMBER_COUNT + 1;
        } else if constexpr (is_aggregate_constructible_with_n<T, N>::value && !is_aggregate_constructible_with_n<T, N + 1>::value) {
            return N;
        } else if constexpr (is_aggregate_constructible_with_n<T, N>::value) {
            return count_aggregate_members<T, N + 1>();
        } else {
            return N - 1;
        }
    }
}

template <class T>
struct member_count {
public:
    static constexpr std::size_t value = []() {
        if constexpr (std::is_aggregate_v<T> && std::is_class_v<T>) {
            return detail::count_aggregate_members<T, 0>();
        } else {
            return 0;
        }
    }();
};

// Main type trait to check if a type is serializable
template <class T>
struct is_serializable_impl<T, std::void_t<
    std::enable_if_t<
        // Check if it's a supported STL container
        (is_supported_stl_container<T>::value) ||
        // Or check if it's a valid struct/class
        (std::is_class_v<T> &&
         has_only_default_constructor<T>::value &&
         !contains_raw_pointer<T>::value &&
         !is_derived_class<T>::value &&
         member_count<T>::value <= MAX_MEMBER_COUNT)
    >
>> : std::true_type {};

// Convenience alias for easier usage
template <class T>
constexpr bool is_serializable_v = is_serializable_impl<T>::value;

// Alternative interface using struct
template <class T>
struct is_serializable : is_serializable_impl<T> {};

}