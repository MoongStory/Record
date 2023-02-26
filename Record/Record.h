/*******************************************************************************
MIT License

Copyright (c) 2023 Moong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

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
