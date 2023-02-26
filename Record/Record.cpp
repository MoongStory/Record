#include "Record.h"

#include "../../StringTool/StringTool/StringTool.h"

#include <io.h>

NexessClient::Log::Log(std::string log_file/* = ""*/) :
	TOKEN_DEBUG_LEVEL("DEBUG"),
	TOKEN_TRACE_LEVEL("TRACE"),
	TOKEN_INFO_LEVEL("INFO"),
	TOKEN_WARN_LEVEL("WARN"),
	TOKEN_FATAL_LEVEL("FATAL")
{
	log_level_ = LL_DEBUG;
	producer_ = "";
	buf_size_ = 2048;
	limit_file_size_ = ULONG_MAX;
	InitializeCriticalSection(&critical_section_log_);

	if (false == log_file.empty())
	{
		set_log_file(log_file);
	}
}

NexessClient::Log::~Log(void)
{
	DeleteCriticalSection(&critical_section_log_);
}





std::string NexessClient::Log::get_time()
{
	SYSTEMTIME system_time = { 0 };
	GetLocalTime(&system_time);

	current_time_string_ = MOONG::StringTool::format("%04d%02d%02d%02d%02d%02d", system_time.wYear, system_time.wMonth, system_time.wDay, system_time.wHour, system_time.wMinute, system_time.wSecond);

	return MOONG::StringTool::format("%04d-%02d-%02d %02d:%02d:%02d.%04ld", system_time.wYear, system_time.wMonth, system_time.wDay, system_time.wHour, system_time.wMinute, system_time.wSecond, system_time.wMilliseconds);
}

void NexessClient::Log::set_log_file(std::string log_file)
{
	log_file_ = log_file;
}

std::string NexessClient::Log::error_lookup(DWORD error_code)
{
	std::string error_message;

	switch (error_code)
	{
	case 0x800706BE:
		error_message = "원격 프로시저를 호출하지 못했습니다. ";
		break;
	case 0x800708AD:
		error_message = "사용자 이름을 찾을 수 없습니다.";
		break;
	case 0x800704c3:
		error_message = "제공한 자격 증명이 기존의 자격 증명 집합과 충돌합니다.";
		break;
	case 0x80070562:
		error_message = "already exist.";
		break;
	case 0x8007056B:
		error_message = "구성원이 없기 때문에 로컬 그룹에 구성원을 추가 또는 삭제하지 못했습니다.";
		break;
	case 0x800708B0:
		error_message = "계정이 이미 있습니다.";
		break;
	case 0x8007089A:
		error_message = "지정한 사용자 이름이 적합하지 않습니다.";
		break;
	case 0x80005000:
		error_message = "E_ADS_BAD_PATHNAME";
		break;
	case 0x80005001:
		error_message = "E_ADS_INVALID_DOMAIN_OBJECT";
		break;
	case 0x80005002:
		error_message = "E_ADS_INVALID_USER_OBJECT";
		break;
	case 0x80005003L:
		error_message = "E_ADS_INVALID_COMPUTER_OBJECT";
		break;
	case 0x80005004L:
		error_message = "E_ADS_UNKNOWN_OBJECT";
		break;
	case 0x80004002:
		error_message = "Interface not supported.";
		break;
	}

	debug("%s", error_message.c_str());

	return error_message;
}

std::string NexessClient::Log::get_log_file()
{
	return log_file_;
}

NexessClient::Log::LOG_LEVEL NexessClient::Log::set_log_level(LOG_LEVEL level)
{
	log_level_ = level;

	return log_level_;
}

NexessClient::Log::LOG_LEVEL NexessClient::Log::set_log_level(std::string log_level)
{
	MOONG::StringTool::toupper(log_level);

	if (log_level == this->TOKEN_DEBUG_LEVEL)
	{
		OutputDebugStringA(this->TOKEN_DEBUG_LEVEL.c_str());
		log_level_ = LOG_LEVEL(0);
	}
	else if (log_level == "TRACE")
	{
		OutputDebugStringA("TRACE");
		log_level_ = LOG_LEVEL(1);
	}
	else if (log_level == "INFO")
	{
		OutputDebugStringA("INFO");
		log_level_ = LOG_LEVEL(2);
	}
	else if (log_level == "WARN")
	{
		OutputDebugStringA("WARN");
		log_level_ = LOG_LEVEL(3);
	}
	else if (log_level == "FATAL")
	{
		OutputDebugStringA("FATAL");
		log_level_ = LOG_LEVEL(4);
	}
	else
	{
		OutputDebugStringA("INFO");
		log_level_ = LOG_LEVEL(LOG_LEVEL::LL_INFO);
	}


	return log_level_;
}

void NexessClient::Log::set_producer(std::string producer)
{
	//m_producer = producer;
	producer_ = "";
}

std::string NexessClient::Log::get_producer()
{
	return producer_;
}



UINT NexessClient::Log::get_buf_size()
{
	return buf_size_;
}

int NexessClient::Log::set_buf_size(UINT buf_size)
{
	buf_size_ = buf_size;
	return 0;
}

int NexessClient::Log::read_properties(std::string config_file)
{
	// TODO: SET API 제공.
	char buf[MAX_PATH] = { 0 };
	DWORD bufsize = MAX_PATH;

	memset(buf, 0, bufsize);
	GetPrivateProfileStringA("logger", "loglevel", "DEBUG", buf, bufsize, config_file.c_str());
	set_log_level(buf);

	memset(buf, 0, bufsize);
	GetPrivateProfileStringA("logger", "logfile", "", buf, bufsize, config_file.c_str());
	set_log_file(buf);

	return 0;
}

NexessClient::Log::LOG_LEVEL NexessClient::Log::get_log_level()
{
	return log_level_;
}

//	logfile의 현재크기를 리턴한다.
unsigned long NexessClient::Log::get_file_size()
{
	FILE* fp = NULL;
	fopen_s(&fp, log_file_.c_str(), "r");

	if (fp == NULL) return 0;

	long file_size = _filelength(_fileno(fp));

	fclose(fp);

	return file_size;
}

//	copy 현재로그파일 --> 로그파일_현재날짜.
//	현재로그파일 사이즈==0
void NexessClient::Log::backup_log_file()
{


	// Request ownership of the critical section.
	EnterCriticalSection(&critical_section_log_);

	// Access the shared resource.
	std::string backup_file;
	std::string dummy = get_time();

	backup_file = log_file_ + "_" + current_time_string_ + ".log";

	std::string old_logfile = this->log_file_;
	std::string tmp_logfile = this->log_file_ + ".tmp";

	log_file_ = tmp_logfile;

	CopyFileA(old_logfile.c_str(), backup_file.c_str(), FALSE);
	DeleteFileA(old_logfile.c_str());

	log_file_ = old_logfile;
	CopyFileA(log_file_.c_str(), tmp_logfile.c_str(), FALSE);

	// Release ownership of the critical section.
	LeaveCriticalSection(&critical_section_log_);
}

unsigned long NexessClient::Log::get_limit_file_size()
{
	return limit_file_size_;
}

int NexessClient::Log::set_limit_file_size(unsigned long limit_file_size)
{
	limit_file_size_ = limit_file_size;
	return 0;
}

//	logfile name이 .log로 끝나지 않으면 default logname이 logfile name이 된다.
//	--> 수정 길이가 3이 안되면
void NexessClient::Log::check_log_file_name()
{
	if (log_file_.length() < 3)
	{
		// Request ownership of the critical section.
		EnterCriticalSection(&critical_section_log_);

		log_file_ = "LoggerV4_default.log"; //DEFAULT_LOGFILE;

		// Release ownership of the critical section.
		LeaveCriticalSection(&critical_section_log_);
		return;
	}
}

void NexessClient::Log::debug(const std::string format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	this->write_log(LOG_LEVEL::LL_DEBUG, format, arg_ptr);
	va_end(arg_ptr);
}

void NexessClient::Log::trace(const std::string format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	this->write_log(LOG_LEVEL::LL_TRACE, format, arg_ptr);
	va_end(arg_ptr);
}

void NexessClient::Log::info(const std::string format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	this->write_log(LOG_LEVEL::LL_INFO, format, arg_ptr);
	va_end(arg_ptr);
}

void NexessClient::Log::warn(const std::string format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	this->write_log(LOG_LEVEL::LL_WARN, format, arg_ptr);
	va_end(arg_ptr);
}

void NexessClient::Log::fatal(const std::string format, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, format);
	this->write_log(LOG_LEVEL::LL_FATAL, format, arg_ptr);
	va_end(arg_ptr);
}

int NexessClient::Log::write_log(const LOG_LEVEL log_level, const std::string format, va_list arg_ptr)
{
	std::string log_level_token;

	if (NexessClient::Log::LOG_LEVEL::LL_DEBUG == log_level)
	{
		log_level_token = this->TOKEN_DEBUG_LEVEL;
	}
	else if (NexessClient::Log::LOG_LEVEL::LL_TRACE == log_level)
	{
		log_level_token = this->TOKEN_TRACE_LEVEL;
	}
	else if (NexessClient::Log::LOG_LEVEL::LL_INFO == log_level)
	{
		log_level_token = this->TOKEN_INFO_LEVEL;
	}
	else if (NexessClient::Log::LOG_LEVEL::LL_WARN == log_level)
	{
		log_level_token = this->TOKEN_WARN_LEVEL;
	}
	else if (NexessClient::Log::LOG_LEVEL::LL_FATAL == log_level)
	{
		log_level_token = this->TOKEN_FATAL_LEVEL;
	}

	try
	{
		check_log_file_name();

		std::string current_thread_id = MOONG::StringTool::format("%04x", GetCurrentThreadId());

		std::string log_data;

		if (log_level < log_level_)
		{
			return 1;
		}

		// file size가 크면 backup
		if (get_file_size() > limit_file_size_)
		{
			backup_log_file();
		}

		//	bufsize가 모자라는 경우, 1024씩 증가 시킨다. 
		//	최대 버퍼사이즈는 1024*1024*10=10MB
		const unsigned long max_buf_size = 1024 * 1024 * 10;
		const unsigned int buf_block_size = 1024;

		char* buf = new char[buf_size_];

		bool loop = true;

		int written_byte = 0;
		do {
			memset(buf, 0, buf_size_);

			written_byte = _vsnprintf_s(buf, buf_size_, buf_size_ / sizeof(char), format.c_str(), arg_ptr);

			if (written_byte < 0)
			{
				//	bufsize를 더크게
				buf_size_ = buf_size_ + buf_block_size;
				if (buf_size_ > max_buf_size)
				{
					loop = false;
				}
				else
				{
					if (NULL != buf)
					{
						memset(buf, 0, buf_size_);
						delete[] buf;
						buf = NULL;
					}

					buf = new char[buf_size_];

					loop = true;
				}
			}
			else
			{
				log_data = buf;

				if (NULL != buf)
				{
					memset(buf, 0, buf_size_);
					delete[] buf;
					buf = NULL;
				}

				loop = false;
			}
		} while (loop);

		if (NULL != buf)
		{
			memset(buf, 0, buf_size_);
			delete[] buf;
			buf = NULL;
		}

		if (written_byte < 0)
		{
			log_data = "로그를 남길 데이터량이 (1024*1024*10)Byte보다 큽니다.";
		}
		else
		{
			if (NexessClient::Log::LOG_LEVEL::LL_TRACE == log_level)
			{
				if (log_data[0] == '#')
				{
					log_data = "[" + get_time() + "][" + producer_ + "][TID:" + current_thread_id + "]" + "[" + log_level_token + "] " + log_data.substr(1, log_data.length() - 1);
				}
				else
				{
					log_data = "[" + get_time() + "][" + producer_ + "][TID:" + current_thread_id + "]" + "[" + log_level_token + "] ### " + log_data;
				}
			}
			else
			{
				log_data = "[" + get_time() + "][" + producer_ + "][TID:" + current_thread_id + "]" + "[" + log_level_token + "] " + log_data;
			}
		}

		FILE* fp = NULL;
		fp = _fsopen(log_file_.c_str(), "a", _SH_DENYNO);
		if (NULL != fp)
		{
			fflush(fp);
			fprintf(fp, "%s\n", log_data.c_str());
			fclose(fp);
		}
	}
	catch (...)
	{
		std::string exception_logfile = log_file_ + ".exception.log";

		FILE* ferr = NULL;
		ferr = _fsopen(exception_logfile.c_str(), "a", _SH_DENYNO);
		if (ferr == NULL)
		{
			return 2;
		}

		std::string current_thread_id = MOONG::StringTool::format("%04x", GetCurrentThreadId());

		std::string logdata = "using logger. some error occured. debug";
		logdata = "[" + get_time() + "][" + producer_ + "][TID:" + current_thread_id + "]" + "[" + log_level_token + "] " + logdata;
		fprintf(ferr, "%s\n", logdata.c_str());

		fclose(ferr);
	}

	return 0;
}