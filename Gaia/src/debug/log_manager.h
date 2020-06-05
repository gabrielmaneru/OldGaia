#pragma once
#include "gaia_pch.h"

#include <spdlog/spdlog.h>

namespace Gaia {
	namespace Log {
		void Init();
		extern Shared<spdlog::logger> s_core_logger;
		extern Shared<spdlog::logger> s_client_logger;
	}
}

#define GAIA_CORE_TRACE(...) ::Gaia::Log::s_core_logger->trace(__VA_ARGS__);
#define GAIA_CORE_INFO(...)  ::Gaia::Log::s_core_logger->info (__VA_ARGS__);
#define GAIA_CORE_WARN(...)  ::Gaia::Log::s_core_logger->warn (__VA_ARGS__);
#define GAIA_CORE_ERROR(...) ::Gaia::Log::s_core_logger->error(__VA_ARGS__);

#define GAIA_CLIENT_TRACE(...)  ::Gaia::Log::s_client_logger->trace (__VA_ARGS__);
#define GAIA_CLIENT_INFO(...)  ::Gaia::Log::s_client_logger->info (__VA_ARGS__);
#define GAIA_CLIENT_WARN(...)  ::Gaia::Log::s_client_logger->warn (__VA_ARGS__);
#define GAIA_CLIENT_ERROR(...) ::Gaia::Log::s_client_logger->critical(__VA_ARGS__);
