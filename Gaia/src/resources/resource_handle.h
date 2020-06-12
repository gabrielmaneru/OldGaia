#pragma once
#include <gaia_pch.h>

namespace Gaia {
	template<typename T>
	class ResourceHandle {
	public:
		ResourceHandle() :m_resource(nullptr) {}
		ResourceHandle(const std::string& name);
		ResourceHandle(T*);
		ResourceHandle(const ResourceHandle<T>& handle);
		~ResourceHandle();

		T* operator->();
		const T* operator->()const;
		explicit operator bool()const;
		bool operator<(const Re)


	private:
		T* m_resource;
	};

	template<typename T>
	inline ResourceHandle<T>::ResourceHandle(const std::string & name)
	{
	}
	template<typename T>
	inline ResourceHandle<T>::ResourceHandle(T *)
	{
	}
	template<typename T>
	inline ResourceHandle<T>::ResourceHandle(const ResourceHandle<T>& handle)
	{
	}
	template<typename T>
	inline ResourceHandle<T>::~ResourceHandle()
	{
	}
}