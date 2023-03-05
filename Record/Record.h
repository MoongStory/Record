#if _MSC_VER > 1000
	#pragma once
#endif

#ifndef _RECORD_H_
#define _RECORD_H_

#include <wtypes.h>
#include <iostream>

namespace MOONG
{
	namespace RECORD
	{
		namespace LEVEL
		{
			static const int TRACE_ = 0;	// 경로 추적을 위해 사용한다.
			static const int DEBUG_ = 1;	// 일반 정보를 상세히 나타낼 때 사용한다.
			static const int INFO_ = 2;	// 일반 정보를 나타낼 때 사용한다.
			static const int WARN_ = 3;	// 에러는 아니지만 주의할 필요가 있을 때 사용한다.
			static const int ERROR_ = 4;	// 일반 에러가 일어났을 때 사용한다.
			static const int FATAL_ = 5;	// 가장 크리티컬한 에러가 일어났을 때 사용한다.
		}

		namespace MODE
		{
			static const std::string DAILY = "daily";
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
		static std::string record_mode_;
		static LONGLONG maximum_record_file_size_;
		static std::string record_file_path_;
		static std::string record_file_path_currently_use_;
		
		
		
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

		static const LONGLONG get_maximum_record_file_size();
		static void set_maximum_record_file_size(const LONGLONG maximum_record_file_size);

		static const std::string get_record_mode();
		static void set_record_mode(const std::string& record_mode);
		static void set_record_mode(const std::wstring& record_mode);

		static const std::string get_record_file_path_currently_use();
	private:
		static void print_(const std::string& token, const std::string format, va_list arg_ptr);

		// 새로 생성한 파일 전체 경로를 record_file_path_currently_use_ 변수에 초기화하고 동일한 값을 리턴한다.
		static const std::string generate_next_available_record_file_path();

		static const bool check_record_file_available(const std::string& record_file_path);
	};
}

#endif _RECORD_H_