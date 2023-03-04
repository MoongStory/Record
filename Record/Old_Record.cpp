#include "Old_Record.h"

#include "../../ConvertDataType/ConvertDataType/ConvertDataType.h"
#include "../../StringTool/StringTool/StringTool.h"
#include "../../Time/Time/Time.h"

#include <windows.h>
#include <strsafe.h>

const std::string MOONG::Old_Record::TRACE_ = "[TRACE]";
const std::string MOONG::Old_Record::DEBUG_ = "[DEBUG]";
const std::string MOONG::Old_Record::INFO_ = "[INFO]";
const std::string MOONG::Old_Record::WARN_ = "[WARN]";
const std::string MOONG::Old_Record::ERROR_ = "[ERROR]";
const std::string MOONG::Old_Record::FATAL_ = "[FATAL]";

std::string MOONG::Old_Record::delimiter_ = "[MOONG_DEBUG]";
unsigned int MOONG::Old_Record::log_level_ = MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_TRACE;

void MOONG::Old_Record::trace(const std::string format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_TRACE)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::TRACE_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Old_Record::trace(const std::wstring format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_TRACE)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::TRACE_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Old_Record::debug(const std::string format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_DEBUG)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::DEBUG_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Old_Record::debug(const std::wstring format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_DEBUG)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::DEBUG_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Old_Record::info(const std::string format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_INFO)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::INFO_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Old_Record::info(const std::wstring format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_INFO)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::INFO_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Old_Record::warn(const std::string format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_WARN)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::WARN_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Old_Record::warn(const std::wstring format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_WARN)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::WARN_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Old_Record::error(const std::string format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_ERROR)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::ERROR_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Old_Record::error(const std::wstring format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_ERROR)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::ERROR_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Old_Record::fatal(const std::string format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_FATAL)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::FATAL_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Old_Record::fatal(const std::wstring format, ...)
{
	if(MOONG::Old_Record::get_log_level() <= MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_FATAL)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Old_Record::print_(MOONG::Old_Record::FATAL_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Old_Record::print(const std::string format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	MOONG::Old_Record::print_("", format, arg_ptr);
	va_end(arg_ptr);
}

void MOONG::Old_Record::print(const std::wstring format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	MOONG::Old_Record::print_("", MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
	va_end(arg_ptr);
}



const std::string MOONG::Old_Record::get_delimiter()
{
	return MOONG::Old_Record::delimiter_;
}

void MOONG::Old_Record::set_delimiter(const std::string delimiter)
{
	if (delimiter.empty())
	{
		MOONG::Old_Record::delimiter_ = "[MOONG_DEBUG]";
	}
	else
	{
		MOONG::Old_Record::delimiter_ = delimiter;
	}
}

void MOONG::Old_Record::set_delimiter(const std::wstring wDelimiter)
{
	MOONG::Old_Record::set_delimiter(MOONG::ConvertDataType::wstring_to_string(wDelimiter));
}

unsigned int MOONG::Old_Record::get_log_level()
{
	return MOONG::Old_Record::log_level_;
}

void MOONG::Old_Record::set_log_level(unsigned int log_level)
{
	MOONG::Old_Record::log_level_ = log_level;

	if (log_level < MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_TRACE || log_level > MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_FATAL)
	{
		MOONG::Old_Record::fatal("Log Level 설정값이 잘못되어 Log Level이 Error Level로 초기화 됩니다.");
		MOONG::Old_Record::log_level_ = MOONG::OLD_RECORD::LOG_LEVEL::LEVEL_ERROR;
	}
	else
	{
		MOONG::Old_Record::log_level_ = log_level;
	}
}





void MOONG::Old_Record::print_(const std::string token, const std::string format, va_list arg_ptr)
{
	std::string debug_string = "";

	debug_string += MOONG::Time::make_date_format(
		MOONG::Time::get_current_time(),
		"[year-month-day hour:minute:second.milliseconds](month_format:%02d)(day_format:%02d)(hour_format:%02d)(minute_format:%02d)(second_format:%02d)(milliseconds_format:%03d)"
		);
	debug_string += MOONG::StringTool::format("[PID:%04X]", GetCurrentProcessId());
	debug_string += MOONG::StringTool::format("[TID:%04X]", GetCurrentThreadId());
	debug_string += " ";
	debug_string += MOONG::Old_Record::get_delimiter();
	debug_string += " ";
	if (token.length() > 0)
	{
		debug_string += token;
		debug_string += " ";
	}
	debug_string += MOONG::StringTool::format(format, arg_ptr);;
	
	// TODO:
	//		파일에 쓰기.
	//		용량 단위로 쪼개기
	//		daily
	OutputDebugStringA(debug_string.c_str());
}
