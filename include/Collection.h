#ifndef COLLECTION_H
#define COLLECTION_H

#include <cstddef>
#include <functional>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>
#include <ostream>

template <typename T>
class Collection {
private:
    std::vector<T> items;

public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    void add(const T& value) {
        items.push_back(value);
    }

    void add(T&& value) {
        items.push_back(std::move(value));
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        items.emplace_back(std::forward<Args>(args)...);
    }

    bool removeAt(std::size_t index) {
        if (index >= items.size()) {
            return false;
        }

        items.erase(items.begin() + static_cast<std::ptrdiff_t>(index));
        return true;
    }

    T& get(std::size_t index) {
        return items.at(index);
    }

    const T& get(std::size_t index) const {
        return items.at(index);
    }

    std::optional<std::size_t> find(const T& value) const {
        for (std::size_t i = 0; i < items.size(); ++i) {
            if (items[i] == value) {
                return i;
            }
        }

        return std::nullopt;
    }

    template <typename Predicate>
    std::optional<std::size_t> findIf(Predicate predicate) const {
        for (std::size_t i = 0; i < items.size(); ++i) {
            if (predicate(items[i])) {
                return i;
            }
        }

        return std::nullopt;
    }

    std::size_t size() const noexcept {
        return items.size();
    }

    bool empty() const noexcept {
        return items.empty();
    }

    void clear() noexcept {
        items.clear();
    }

    T& operator[](std::size_t index) {
        return items[index];
    }

    const T& operator[](std::size_t index) const {
        return items[index];
    }

    iterator begin() noexcept { return items.begin(); }
    iterator end() noexcept { return items.end(); }
    const_iterator begin() const noexcept { return items.begin(); }
    const_iterator end() const noexcept { return items.end(); }
    const_iterator cbegin() const noexcept { return items.cbegin(); }
    const_iterator cend() const noexcept { return items.cend(); }

    template <typename OutputFunction>
    void display(std::ostream& output, OutputFunction formatter) const {
        for (const T& item : items) {
            formatter(output, item);
        }
    }
};

template <typename T, typename Predicate>
std::optional<std::size_t> findByPredicate(
    const Collection<T>& collection,
    Predicate predicate) {
    return collection.findIf(predicate);
}

#endif