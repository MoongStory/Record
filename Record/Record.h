#if _MSC_VER > 1000
	#pragma once
#endif

#ifndef _RECORD_H_
#define _RECORD_H_

#include <wtypes.h>
#include <iostream>

// TODO: daily 기능 추가.

namespace MOONG
{
	namespace RECORD
	{
		namespace RECORD_LEVEL
		{
			static const int LEVEL_TRACE = 0;	// 경로 추적을 위해 사용한다.
			static const int LEVEL_DEBUG = 1;	// 일반 정보를 상세히 나타낼 때 사용한다.
			static const int LEVEL_INFO = 2;	// 일반 정보를 나타낼 때 사용한다.
			static const int LEVEL_WARN = 3;	// 에러는 아니지만 주의할 필요가 있을 때 사용한다.
			static const int LEVEL_ERROR = 4;	// 일반 에러가 일어났을 때 사용한다.
			static const int LEVEL_FATAL = 5;	// 가장 크리티컬한 에러가 일어났을 때 사용한다.
		}
	}
	
	class Record
	{
	public:
	protected:
	private:
		static const std::string TRACE_;
		static const std::string DEBUG_;
		static const std::string INFO_;
		static const std::string WARN_;
		static const std::string ERROR_;
		static const std::string FATAL_;
		
		static std::string delimiter_;
		static unsigned int record_level_;
		static std::string record_file_path_;
		static size_t record_file_count_;
		static LONGLONG record_file_size_;
		
		
		
	public:
		static void trace(const std::string format, ...);
		static void trace(const std::wstring format, ...);
		
		static void debug(const std::string format, ...);
		static void debug(const std::wstring format, ...);
		
		static void info(const std::string format, ...);
		static void info(const std::wstring format, ...);
		
		static void warn(const std::string format, ...);
		static void warn(const std::wstring format, ...);
		
		static void error(const std::string format, ...);
		static void error(const std::wstring format, ...);
		
		static void fatal(const std::string format, ...);
		static void fatal(const std::wstring format, ...);



		static void print(const std::string format, ...);
		static void print(const std::wstring format, ...);
		
		
		
		static const std::string get_delimiter();
		static void set_delimiter(const std::string& delimiter);
		static void set_delimiter(const std::wstring& wDelimiter);
		
		static unsigned int get_record_level();
		static void set_record_level(const unsigned int record_level);

		static const std::string get_record_file_path();
		static void set_record_file_path(const std::string& record_file_path);
		static void set_record_file_path(const std::wstring& record_file_path);

		static const LONGLONG get_record_file_size();
		static void set_record_file_size(const LONGLONG record_file_size);
	private:
		static void print_(const std::string& token, const std::string format, va_list arg_ptr);
	};
}

#endif _RECORD_H_