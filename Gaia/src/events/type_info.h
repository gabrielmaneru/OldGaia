#pragma once
#include <typeinfo>
#include <string>

namespace Gaia{
    class TypeInfo
    {
    public:
        template<typename T>
		TypeInfo(const T& t)
			: name(typeid(t).name()) {}
        TypeInfo(const std::type_info & t)
			: name(t.name()) {}
		
		const std::string& get_name() const { return name; };
		bool operator==(const TypeInfo &rhs) const { return name == rhs.get_name(); };
		bool operator!=(const TypeInfo &rhs) const { return name != rhs.get_name();	};
		bool operator< (const TypeInfo &rhs) const { return name <  rhs.get_name(); };
		
    private:
        const std::string name;
    };

    template<typename T>
    TypeInfo type_of(const T& t)
    {
        return TypeInfo(typeid(t));
    }
    
    template<typename T>
    TypeInfo type_of()
    {
        return TypeInfo(T());
    }
}