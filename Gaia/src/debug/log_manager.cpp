#include "gaia_pch.h"
#include "log_manager.h"
#include <spdlog/spdlog.h>

namespace Gaia {
	namespace Log {
		void Init(){

			spdlog::set_pattern("%^[%T] %n: %v%$");

			s_engine_logger = spdlog::stdout_color_mt("ENGINE");
			s_engine_logger->set_level(spdlog::level::trace);

			s_program_logger = spdlog::stdout_color_mt("PROGRAM");
			s_program_logger->set_level(spdlog::level::trace);

		}
		std::shared_ptr<spdlog::logger> s_engine_logger;
		std::shared_ptr<spdlog::logger> s_program_logger;
	}
}
