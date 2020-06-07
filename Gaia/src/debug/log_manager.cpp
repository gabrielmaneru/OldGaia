#include "gaia_pch.h"
#include "log_manager.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Gaia {
	namespace Log {
		void Init(){
			std::vector<spdlog::sink_ptr> log_sinks;
			log_sinks.emplace_back(create_shared<spdlog::sinks::stdout_color_sink_mt>());
			log_sinks[0]->set_pattern("%^[%T] %n: %v%$");
			//log_sinks.emplace_back(create_shared<spdlog::sinks::basic_file_sink_mt>("Gaia.log", true));
			//log_sinks[1]->set_pattern("[%T] [%l] %n: %v");


			s_engine_logger = std::make_shared<spdlog::logger>("ENGINE", begin(log_sinks), end(log_sinks));
			spdlog::register_logger(s_engine_logger);
			s_engine_logger->set_level(spdlog::level::trace);
			s_engine_logger->flush_on(spdlog::level::trace);

			s_program_logger = std::make_shared<spdlog::logger>("PROGRAM", begin(log_sinks), end(log_sinks));
			spdlog::register_logger(s_program_logger);
			s_program_logger->set_level(spdlog::level::trace);
			s_program_logger->flush_on(spdlog::level::trace);

		}
		Shared<spdlog::logger> s_engine_logger;
		Shared<spdlog::logger> s_program_logger;
	}
}
