#pragma once
namespace Gaia {
	class Context
	{
	public:
		virtual void swap_buffers() = 0;
		static Context* create_context(void* native);
	};
}