#pragma  once

#include <cstdint>
#include <string>
#include <variant>
#include <functional>

namespace wl {


    using VarVariantValueClass = std::variant<uint32_t, double, bool, std::string, std::function<void()> >;

    class VariantValue : public VarVariantValueClass {
    public:
        using VarVariantValueClass::VarVariantValueClass;
        using VarVariantValueClass::operator=;

        template<typename T>
        T get() {
            return std::get<T>(*this);
        }

        template<typename T>
        bool get(T &val) {
            if (std::holds_alternative<T>(*this)) {
                val = std::get<T>(*this);
                return true;
            }
            return false;
        }

//        virtual std::string toString() {
//            std::stringstream ss;
//            std::visit([&ss](auto &&arg) { ss << arg; }, (VarVariantValueClass) (*this));
//            return ss.str();
//        }
    };

    class Attr {

    };

}
