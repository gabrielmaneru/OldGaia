#pragma once
#include <json/json.h>
#include <scene/serializable.h>
#include <gaia_pch.h>

namespace Gaia {
	// Invalid
	template<typename T, typename=void>
	struct Save {
		static void fn(const T&, Json::Value&) {};
		static_assert(!std::is_same<T, T>::value, "Type not valid for serialization");
	};
	template<typename T, typename = void>
	struct Load
	{
		static void fn(T&, const Json::Value&) {}
		static_assert(!std::is_same<T, T>::value, "Type not supported for deserialization");
	};


	// Fundamental types
	template<typename T>
	struct Save<T, typename std::enable_if<std::is_fundamental<T>::value>::type>
	{
		static void fn(const T& val, Json::Value& json)
		{
			json = val;
		};
	};
	template<>
		struct Save<std::string>
	{
		static void fn(const std::string& val, Json::Value& json)
		{
			json = val;
		}
	};
	template<typename T>
	struct ReturnType{};
	template<typename T, typename C>
	struct ReturnType<T(C::*)()const> { using type = T; };
	#define LOAD_IMPL(Func)																	\
	template<>																				\
	struct Load<ReturnType<decltype(&##Func)>::type>{										\
		static void fn(ReturnType<decltype(&##Func)>::type& val, const Json::Value& json) {	\
			if(!json.isNull() && !json.isObject() && !json.isArray())						\
				val = json.Func();															\
		}																					\
	};
	LOAD_IMPL(Json::Value::asBool)
	LOAD_IMPL(Json::Value::asCString)
	LOAD_IMPL(Json::Value::asDouble)
	LOAD_IMPL(Json::Value::asFloat)
	LOAD_IMPL(Json::Value::asInt)
	LOAD_IMPL(Json::Value::asInt64)
	LOAD_IMPL(Json::Value::asString)
	LOAD_IMPL(Json::Value::asUInt)
	LOAD_IMPL(Json::Value::asUInt64)
	#undef LOAD_IMPL


	// Serializable
	template<typename T>
	struct Save<T, typename std::enable_if<std::is_base_of<Serializable, T>::value>::type>{
		static void fn(const T& val, Json::Value& json)
		{
			val.serialize(json[val.get_type_name()]);
		};
	};
	template<typename T>
	struct Load<T, typename std::enable_if<std::is_base_of<Serializable, T>::value>::type>
	{
		static void fn(T& val, const Json::Value& json)
		{
			val.deserialize(json[val.get_type_name()]);
		}
	};


	// Custom types
	template<glm::length_t N>
	struct Save<glm::vec<N, float, glm::defaultp>>
	{
		static void fn(const glm::vec<N, float, glm::defaultp>& val, Json::Value& json)
		{
			for(glm::length_t i=0; i < val.length(); ++i)
				json[i] = val[i];
		}
	};
	template<glm::length_t N>
	struct Load<glm::vec<N, float, glm::defaultp>>
	{
		static void fn(glm::vec<N, float, glm::defaultp>& val, const Json::Value& json)
		{
			if(!json.isNull())
				for (glm::length_t i = 0; i < val.length(); ++i)
					Load<float>::fn(val[i], json[i]);
		}
	};
	template<>
	struct Save<quat>
	{
		static void fn(const quat& val, Json::Value& json)
		{
			for (glm::length_t i = 0; i < val.length(); ++i)
				json[i] = val[i];
		}
	};
	template<>
	struct Load<quat>
	{
		static void fn(quat& val, const Json::Value& json)
		{
			if (!json.isNull())
				for (glm::length_t i = 0; i < val.length(); ++i)
					Load<float>::fn(val[i], json[i]);
		}
	};
	template<typename T>
	struct Save<std::vector<T>>
	{
		static void fn(const std::vector<T>& val, Json::Value& json)
		{
			for (auto& itr : val)
				Save<T>::fn(itr, json[json.size()]);
		};
	};
	template<typename T>
	struct Load<std::vector<T>>
	{
		static void fn(std::vector<T>& val, const Json::Value& json)
		{
			if (!json.isNull() && json.isArray())
			{
				val.clear();
				for (Json::ArrayIndex i = 0; i < json.size(); ++i)
				{
					T element;
					Load<T>::fn(element, json[i]);
					val.emplace_back(std::move(element));
				}
			}
		}
	};
	template<typename T>
	struct Save<std::vector<T*>>
	{
		static void fn(const std::vector<T*>& val, Json::Value& json)
		{
			for (auto& itr : val)
				Save<T>::fn(*itr, json[json.size()]);
		};
	};
	template<typename T>
	struct Load<std::vector<T*>>
	{
		static void fn(std::vector<T*>& val, const Json::Value& json)
		{
			if (!json.isNull() && json.isArray())
			{
				val.clear();
				for (Json::ArrayIndex i = 0; i < json.size(); ++i)
				{
					T* element = new T();
					Load<T>::fn(*element, json[i]);
					val.emplace_back(std::move(element));
				}
			}
		}
	};

	//Shorteners
	template<typename T> void save(const T& val, Json::Value& json_val) { Save<T>::fn(val, json_val); }
	template<typename T> void load(T& val, const Json::Value& json_val) { Load<T>::fn(val, json_val); }
}