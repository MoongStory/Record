#include "Record.h"

#include "../../ConvertDataType/ConvertDataType/ConvertDataType.h"
#include "../../FileInformation/FileInformation/FileInformation.h"
#include "../../StringTool/StringTool/StringTool.h"
#include "../../Time/Time/Time.h"

#include <fstream>
#include <strsafe.h>

const std::string MOONG::Record::TRACE_ = "[TRACE]";
const std::string MOONG::Record::DEBUG_ = "[DEBUG]";
const std::string MOONG::Record::INFO_ = "[INFO]";
const std::string MOONG::Record::WARN_ = "[WARN]";
const std::string MOONG::Record::ERROR_ = "[ERROR]";
const std::string MOONG::Record::FATAL_ = "[FATAL]";

std::string MOONG::Record::delimiter_ = "[MOONG_DEBUG]";
unsigned int MOONG::Record::record_level_ = MOONG::RECORD::LEVEL::TRACE_;
std::string MOONG::Record::record_file_path_ = "MoongRecord.log";
LONGLONG MOONG::Record::maximum_record_file_size_ = 0;
std::string MOONG::Record::record_mode_ = MOONG::RECORD::MODE::DAILY;
std::string MOONG::Record::record_file_path_currently_use_ = "";

void MOONG::Record::trace(const std::string format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::TRACE_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::TRACE_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Record::trace(const std::wstring format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::TRACE_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::TRACE_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Record::debug(const std::string format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::DEBUG_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::DEBUG_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Record::debug(const std::wstring format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::DEBUG_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::DEBUG_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Record::info(const std::string format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::INFO_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::INFO_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Record::info(const std::wstring format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::INFO_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::INFO_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Record::warn(const std::string format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::WARN_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::WARN_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Record::warn(const std::wstring format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::WARN_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::WARN_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Record::error(const std::string format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::ERROR_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::ERROR_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Record::error(const std::wstring format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::ERROR_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::ERROR_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}



void MOONG::Record::fatal(const std::string format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::FATAL_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::FATAL_, format, arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Record::fatal(const std::wstring format, ...)
{
	if(MOONG::Record::get_record_level() <= MOONG::RECORD::LEVEL::FATAL_)
	{
		va_list arg_ptr;

		va_start(arg_ptr, format);
		MOONG::Record::print_(MOONG::Record::FATAL_, MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
		va_end(arg_ptr);
	}
}

void MOONG::Record::print(const std::string format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	MOONG::Record::print_("", format, arg_ptr);
	va_end(arg_ptr);
}

void MOONG::Record::print(const std::wstring format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	MOONG::Record::print_("", MOONG::ConvertDataType::wstring_to_string(format), arg_ptr);
	va_end(arg_ptr);
}



const std::string MOONG::Record::get_delimiter()
{
	return MOONG::Record::delimiter_;
}

void MOONG::Record::set_delimiter(const std::string& delimiter)
{
	if (delimiter.empty())
	{
		MOONG::Record::delimiter_ = "[MOONG_DEBUG]";
	}
	else
	{
		MOONG::Record::delimiter_ = delimiter;
	}
}

void MOONG::Record::set_delimiter(const std::wstring& wDelimiter)
{
	MOONG::Record::set_delimiter(MOONG::ConvertDataType::wstring_to_string(wDelimiter));
}

unsigned int MOONG::Record::get_record_level()
{
	return MOONG::Record::record_level_;
}

void MOONG::Record::set_record_level(const unsigned int record_level)
{
	MOONG::Record::record_level_ = record_level;

	if (record_level < MOONG::RECORD::LEVEL::TRACE_ || record_level > MOONG::RECORD::LEVEL::FATAL_)
	{
		MOONG::Record::fatal("Log Level 설정값이 잘못되어 Log Level이 Error Level로 초기화 됩니다.");
		MOONG::Record::record_level_ = MOONG::RECORD::LEVEL::ERROR_;
	}
	else
	{
		MOONG::Record::record_level_ = record_level;
	}
}

const std::string MOONG::Record::get_record_file_path()
{
	return MOONG::Record::record_file_path_;
}

void MOONG::Record::set_record_file_path(const std::string& record_file_path)
{
	MOONG::Record::record_file_path_ = record_file_path;
}

void MOONG::Record::set_record_file_path(const std::wstring& record_file_path)
{
	MOONG::Record::record_file_path_ = MOONG::ConvertDataType::wstring_to_string(record_file_path);
}

const LONGLONG MOONG::Record::get_maximum_record_file_size()
{
	return MOONG::Record::maximum_record_file_size_;
}

void MOONG::Record::set_maximum_record_file_size(const LONGLONG maximum_record_file_size)
{
	MOONG::Record::maximum_record_file_size_ = maximum_record_file_size;
}

const std::string MOONG::Record::get_record_mode()
{
	return MOONG::Record::record_mode_;
}

void MOONG::Record::set_record_mode(const std::string& record_mode)
{
	MOONG::Record::record_mode_ = MOONG::StringTool::tolower_keep_origin(record_mode);
}

void MOONG::Record::set_record_mode(const std::wstring& record_mode)
{
	MOONG::Record::set_record_mode(MOONG::ConvertDataType::wstring_to_string(record_mode));
}

const std::string MOONG::Record::get_record_file_path_currently_use()
{
	return MOONG::Record::record_file_path_currently_use_;
}





void MOONG::Record::print_(const std::string& token, const std::string format, va_list arg_ptr)
{
	if (MOONG::Record::check_record_file_available(MOONG::Record::get_record_file_path_currently_use()) == false)
	{
		MOONG::Record::record_file_path_currently_use_ = "";

		generate_next_available_record_file_path();
	}

	// 경로가 없는 경우 새로 생성한다.
	CreateDirectoryA(MOONG::FileInformation::get_directory(MOONG::Record::get_record_file_path_currently_use()).c_str(), NULL);

	std::ofstream write_file(MOONG::Record::get_record_file_path_currently_use(), std::ios::app);

	if (write_file.is_open())
	{
		std::string debug_string = "";

		debug_string += MOONG::Time::make_date_format(
			MOONG::Time::get_current_time(),
			"[year-month-day hour:minute:second.milliseconds](month_format:%02d)(day_format:%02d)(hour_format:%02d)(minute_format:%02d)(second_format:%02d)(milliseconds_format:%03d)"
		);
		debug_string += MOONG::StringTool::format("[PID:%04X]", GetCurrentProcessId());
		debug_string += MOONG::StringTool::format("[TID:%04X]", GetCurrentThreadId());
		debug_string += " ";
		debug_string += MOONG::Record::get_delimiter();
		debug_string += " ";
		if (token.length() > 0)
		{
			debug_string += token;
			debug_string += " ";
		}
		debug_string += MOONG::StringTool::format(format, arg_ptr);;

		write_file << debug_string << std::endl;

		write_file.close();
	}
	else
	{
		OutputDebugStringA(std::string(MOONG::Record::get_delimiter() + std::string(" Failed to open the file.")).c_str());
	}
}

const std::string MOONG::Record::generate_next_available_record_file_path()
{
	std::string file_directory = MOONG::FileInformation::get_directory(MOONG::Record::get_record_file_path());
	std::string file_name_without_extension = MOONG::FileInformation::get_name_without_extension(MOONG::Record::get_record_file_path());
	std::string file_extension = MOONG::FileInformation::get_extension(MOONG::Record::get_record_file_path());

	std::string next_available_record_file_path = "";

	if (MOONG::Record::get_record_mode() == MOONG::RECORD::MODE::DAILY)
	{
		next_available_record_file_path = MOONG::StringTool::format("%s/%s_%s.%s",
			file_directory.c_str(),
			MOONG::Time::make_date_format(MOONG::Time::get_current_time(), "YEAR-MONTH-DAY(month_format:%02d)(day_format:%02d)").c_str(),
			file_name_without_extension.c_str(),
			file_extension.c_str()
		);
	}
	else
	{
		next_available_record_file_path = MOONG::StringTool::format("%s/%s.%s",
			file_directory.c_str(),
			file_name_without_extension.c_str(),
			file_extension.c_str()
		);
	}

	if (MOONG::Record::check_record_file_available(next_available_record_file_path) == true)
	{
		MOONG::Record::record_file_path_currently_use_ = next_available_record_file_path;

		return MOONG::Record::record_file_path_currently_use_;
	}

	for (size_t i = 1; i < 1000000; i++)	// 무한 반복 방지를 위해 100만번으로 반복 횟수 제한.
	{
		if (MOONG::Record::get_record_mode() == MOONG::RECORD::MODE::DAILY)
		{
			next_available_record_file_path = MOONG::StringTool::format("%s/%s_%s(%d).%s",
				file_directory.c_str(),
				MOONG::Time::make_date_format(MOONG::Time::get_current_time(), "YEAR-MONTH-DAY(month_format:%02d)(day_format:%02d)").c_str(),
				file_name_without_extension.c_str(),
				i,
				file_extension.c_str()
			);
		}
		else
		{
			next_available_record_file_path = MOONG::StringTool::format("%s/%s(%d).%s",
				file_directory.c_str(),
				file_name_without_extension.c_str(),
				i,
				file_extension.c_str()
			);
		}

		if (MOONG::Record::check_record_file_available(next_available_record_file_path) == true)
		{
			MOONG::Record::record_file_path_currently_use_ = next_available_record_file_path;

			return MOONG::Record::record_file_path_currently_use_;
		}
	}

	// 이 파일이 생성되었다는것은 뭔가 논리 에러가 있다는 뜻. 설마 파일 넘버링이 100만개 이상...? 
	MOONG::Record::record_file_path_currently_use_ = MOONG::StringTool::format("%s/%s.%s",
		file_directory.c_str(),
		"generate_next_available_record_file_path_logic_error",
		file_extension.c_str()
	);

	return MOONG::Record::record_file_path_currently_use_;
}

const bool MOONG::Record::check_record_file_available(const std::string& record_file_path)
{
	if (record_file_path.length() <= 0)
	{
		return false;
	}

	if (MOONG::Record::get_maximum_record_file_size() > 0)
	{
		if (false == MOONG::FileInformation::is_exist(record_file_path) || MOONG::FileInformation::get_size(record_file_path) < MOONG::Record::get_maximum_record_file_size())
		{
			return true;
		}
	}
	else
	{
		return true;
	}

	return false;
}
