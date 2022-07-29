#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Rengine
{
	class RENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define RE_CORE_TRACE(...)   ::Rengine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RE_CORE_INFO(...)    ::Rengine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RE_CORE_WARN(...)    ::Rengine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RE_CORE_ERROR(...)   ::Rengine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RE_CORE_CRITICAL(...)   ::Rengine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RE_TRACE(...)        ::Rengine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RE_INFO(...)         ::Rengine::Log::GetClientLogger()->info(__VA_ARGS__)
#define RE_WARN(...)         ::Rengine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RE_ERROR(...)        ::Rengine::Log::GetClientLogger()->error(__VA_ARGS__)
#define RE_CRITICAL(...)        ::Rengine::Log::GetClientLogger()->critical(__VA_ARGS__)