#pragma once
#include <json/json.h>

namespace Gaia {
	class Serializable {
	public:
		virtual ~Serializable()=default;

	private:
		template<typename T, typename>
		friend struct Save;
		template<typename T, typename>
		friend struct Load;
		virtual void serialize(Json::Value& json)const {}
		virtual void deserialize(const Json::Value& json) {}
		virtual std::string get_type_name()const = 0;
	};
}