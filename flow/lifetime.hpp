#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>

namespace flow {

    struct lifetime {
        int id;

        static std::size_t total;
        static std::size_t alive;

        lifetime() : id(0) {
            m_on_create();
            fmt::print("lifetime() [default constructor]\n");
        }

        explicit lifetime(int i) : id(i) {
            m_on_create();
            fmt::print("lifetime(int) [int constructor]\n");
        }

        lifetime(const lifetime& other) : id(other.id) {
            m_on_create();
            fmt::print("lifetime(const lifetime&) [copy constructor]\n");
        }

        lifetime(lifetime&& other) noexcept : id(other.id) {
            m_on_create();
            fmt::print("lifetime(lifetime&&) [move constructor]\n");
        }

        lifetime& operator=(const lifetime& rhs) {
            fmt::print("lifetime& operator=(const lifetime&) [copy assignment] {} = {}\n", id, rhs.id);
            id = rhs.id;
            return *this;
        }

        lifetime& operator=(lifetime&& rhs) noexcept {
            fmt::print("lifetime& operator=(lifetime&&) [move assignment] {} = {}\n", id, rhs.id);
            id = rhs.id;
            return *this;
        }

        ~lifetime() noexcept {
            --alive;
            fmt::print("~lifetime({}) [destructor]\n", id);
        }

#ifdef __cpp_impl_three_way_comparison
        auto operator<=>(const lifetime& rhs) const {
            fmt::print("lifetime::operator <=> [three-way comparison operator] {} <=> {}\n", id, rhs.id);
            return id <=> rhs.id;
        }
#endif

        bool operator==(const lifetime& rhs) const {
            fmt::print("lifetime::operator == [equality operator] {} == {}\n", id, rhs.id);
            return id == rhs.id;
        }

        bool operator!=(const lifetime& rhs) const {
            fmt::print("lifetime::operator != [inequality operator] {} != {}\n", id, rhs.id);
            return id != rhs.id;
        }

        bool operator<(const lifetime& rhs) const {
            fmt::print("lifetime::operator < [less operator] {} < {}\n", id, rhs.id);
            return id < rhs.id;
        }

        bool operator<=(const lifetime& rhs) const {
            fmt::print("lifetime::operator <= [less equality operator] {} < {}\n", id, rhs.id);
            return id <= rhs.id;
        }

        bool operator>(const lifetime& rhs) const {
            fmt::print("lifetime::operator > [greater operator] {} > {}\n", id, rhs.id);
            return id > rhs.id;
        }

        bool operator>=(const lifetime& rhs) const {
            fmt::print("lifetime::operator >= [greater equality operator] {} >= {}\n", id, rhs.id);
            return id >= rhs.id;
        }

        template <typename CharT, typename Traits>
        friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const lifetime& l) {
            return os << fmt::format("lifetime({})", l.id);
        }

    private:
        static void m_on_create() {
            ++total;
            ++alive;
        }
    };

    std::size_t lifetime::total = 0;
    std::size_t lifetime::alive = 0;

} // namespace flow

template <>
struct fmt::formatter<flow::lifetime> : fmt::ostream_formatter {};
