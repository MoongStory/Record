#pragma once

#include <string>
#include <wtypes.h>

// TODO: static 으로 변경.

namespace NexessClient
{
	class Log
	{
		typedef	enum _LOG_LEVEL
		{
			LL_DEBUG = 0,	// DEBUG
			LL_TRACE = 1,	// TRACE
			LL_INFO = 2,	// INFO
			LL_WARN = 3,	// WARN
			LL_FATAL = 4	// FATAL
		} LOG_LEVEL;

	public:
		std::string current_time_string_;
	private:
		unsigned long limit_file_size_;
		std::string producer_;
		std::string log_file_;
		LOG_LEVEL log_level_;
		unsigned long buf_size_;
		CRITICAL_SECTION critical_section_log_;

		const std::string TOKEN_DEBUG_LEVEL;
		const std::string TOKEN_TRACE_LEVEL;
		const std::string TOKEN_INFO_LEVEL;
		const std::string TOKEN_WARN_LEVEL;
		const std::string TOKEN_FATAL_LEVEL;





	public:
		Log(std::string log_file = "");
		~Log(void);

		void check_log_file_name();
		int set_limit_file_size(unsigned long limit_file_size);
		unsigned long get_limit_file_size();

		LOG_LEVEL get_log_level();

		int read_properties(std::string config_file);

		UINT get_buf_size();
		int set_buf_size(UINT buf_size);

		void set_log_file(std::string log_file);
		std::string	get_log_file();

		void set_producer(std::string producer);
		std::string	get_producer();

		LOG_LEVEL set_log_level(LOG_LEVEL level);
		LOG_LEVEL set_log_level(std::string log_level);

		std::string	error_lookup(DWORD error_code);

		std::string	get_time();


		void debug(const std::string format, ...);
		void trace(const std::string format, ...);
		void info(const std::string format, ...);
		void warn(const std::string format, ...);
		void fatal(const std::string format, ...);

	private:
		void backup_log_file();
		unsigned long get_file_size();

		int write_log(const LOG_LEVEL log_level, const std::string format, va_list arg_ptr);
	};
}
