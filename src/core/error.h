#pragma once

#include <variant>

namespace core
{
struct Error
{
    enum class TYPE : int
    {
        UNKNOW,
        INVALID_ARG,
        OUT_OF_MEMORY,
        OUT_OF_BOUNDS,
        INVALID_STATE,
        INVALID_RETURN_TYPE_CAST,
        INVALID_ERROR_REQUEST,
        TEST, // intentially triggered error
    };

    constexpr Error(const char* m) noexcept : msg(m) {}

    constexpr Error(const char* m, TYPE t) noexcept : msg(m), type(t) {}

    const char* const msg = nullptr;
    const TYPE type       = TYPE::UNKNOW;
};

template <typename T> class ReturnValue
{
    static_assert(std::is_pod<T>::value);

private:
    template <typename T, typename X>
    static constexpr std::variant<T, Error> construct_variant(const ReturnValue<X>& ret)
    {
        static_assert(std::is_same<T, X>::value, "Handle return values of different types explicitly.");

        if (ret.isError())
            return ret.getError();

        return ret.getValue();
    }

public:
    template <typename X>
    constexpr ReturnValue(const ReturnValue<X>& ret) noexcept : m_variant(construct_variant<T, X>(ret))
    {
    }

    constexpr ReturnValue(T v) noexcept : m_variant(v) {}

    constexpr ReturnValue(const Error& e) noexcept : m_variant(e) {}

    [[nodiscard]] constexpr auto isError() const noexcept
    {
        return std::holds_alternative<Error>(m_variant);
    }

    [[nodiscard]] constexpr auto isSuccess() const noexcept
    {
        return !isError();
    }

    [[nodiscard]] constexpr auto isValue() const noexcept
    {
        return !isError();
    }

    [[nodiscard]] constexpr auto getError() const noexcept
    {
        if (!isError())
            return Error("Return object does not store error!", Error::TYPE::INVALID_ERROR_REQUEST);

        return std::get<Error>(m_variant);
    }

    [[nodiscard]] constexpr T getValue() const
    {
        static_assert(std::is_same<T, std::monostate>::value == false);
        return std::get<T>(m_variant);
    }

    explicit constexpr operator T() const
    {
        return getValue();
    }

    constexpr operator bool() const noexcept
    {
        return !isError();
    }

    template <typename DST> explicit constexpr operator DST() const noexcept
    {
        static_assert(false, "Use cast() instead.");
    }

    template <typename DST> constexpr ReturnValue<DST> cast() const noexcept
    {
        static_assert(std::is_same<T, std::monostate>::value == false);

        if (isError())
            return getError();

        return static_cast<DST>(getValue());
    }

private:
    const std::variant<T, Error> m_variant;
};

using ReturnVoid              = ReturnValue<std::monostate>;
static constexpr auto SUCCESS = ReturnVoid{std::monostate{}};

template <typename T> constexpr ReturnVoid cast_to_success(const ReturnValue<T>& rv)
{
    static_assert(std::is_same<T, std::monostate>::value == false);

    if (rv.isError())
        return rv.getError();

    return SUCCESS;
}

} // namespace core
