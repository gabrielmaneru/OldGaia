#pragma once
#include "gaia_pch.h"

#include <spdlog/spdlog.h>

namespace Gaia {
	namespace Log {
		void Init();
		extern Shared<spdlog::logger> s_engine_logger;
		extern Shared<spdlog::logger> s_program_logger;
	}
}

#define GAIA_ELOG_TRACE(...) ::Gaia::Log::s_engine_logger->trace(__VA_ARGS__);
#define GAIA_ELOG_INFO(...)  ::Gaia::Log::s_engine_logger->info (__VA_ARGS__);
#define GAIA_ELOG_WARN(...)  ::Gaia::Log::s_engine_logger->warn (__VA_ARGS__);
#define GAIA_ELOG_ERROR(...) ::Gaia::Log::s_engine_logger->error(__VA_ARGS__);
#define GAIA_ELOG_CRITICAL(...) ::Gaia::Log::s_engine_logger->critical(__VA_ARGS__);

#define GAIA_LOG_TRACE(...) ::Gaia::Log::s_program_logger->trace (__VA_ARGS__);
#define GAIA_LOG_INFO(...)  ::Gaia::Log::s_program_logger->info (__VA_ARGS__);
#define GAIA_LOG_WARN(...)  ::Gaia::Log::s_program_logger->warn (__VA_ARGS__);
#define GAIA_LOG_ERROR(...) ::Gaia::Log::s_program_logger->error(__VA_ARGS__);
#define GAIA_LOG_CRITICAL(...) ::Gaia::Log::s_program_logger->critical(__VA_ARGS__);
