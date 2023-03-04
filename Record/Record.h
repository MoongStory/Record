#if _MSC_VER > 1000
	#pragma once
#endif

#ifndef _RECORD_H_
#define _RECORD_H_

#include <iostream>

namespace MOONG
{
	namespace RECORD
	{
		namespace LOG_LEVEL
		{
			static const int LEVEL_TRACE = 0;	// ��� ������ ���� ����Ѵ�.
			static const int LEVEL_DEBUG = 1;	// �Ϲ� ������ ���� ��Ÿ�� �� ����Ѵ�.
			static const int LEVEL_INFO = 2;	// �Ϲ� ������ ��Ÿ�� �� ����Ѵ�.
			static const int LEVEL_WARN = 3;	// ������ �ƴ����� ������ �ʿ䰡 ���� �� ����Ѵ�.
			static const int LEVEL_ERROR = 4;	// �Ϲ� ������ �Ͼ�� �� ����Ѵ�.
			static const int LEVEL_FATAL = 5;	// ���� ũ��Ƽ���� ������ �Ͼ�� �� ����Ѵ�.
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
		static unsigned int log_level_;
		static std::string log_file_path_;
		
		
		
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
		
		static unsigned int get_log_level();
		static void set_log_level(unsigned int log_level);

		static void set_log_file_path(const std::string& log_file_path);
	private:
		static void print_(const std::string& token, const std::string format, va_list arg_ptr);
	};
}

#endif _RECORD_H_