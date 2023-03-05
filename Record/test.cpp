#include <iostream>

#include "Record.h"

int main()
{
	//MOONG::Record::set_log_file_path("C:/Users/moong/Desktop/Log/MoongRecord.log");
	MOONG::Record::set_record_file_path("./·Î±×/MoongRecord.log");
	MOONG::Record::set_delimiter("[delimiter_test]");
	//MOONG::Record::set_maximum_record_file_size(100);
	//MOONG::Record::set_record_mode("");

	MOONG::Record::debug("debug 000");
	MOONG::Record::info("info 000");

	MOONG::Record::set_record_level(MOONG::RECORD::LEVEL::INFO_);

	MOONG::Record::debug("debug 001");
	MOONG::Record::info("info 001");

	MOONG::Record::set_record_level(MOONG::RECORD::LEVEL::DEBUG_);

	MOONG::Record::debug("debug 002");
	MOONG::Record::info("info 002");

	//while (true)
	//{
	//	MOONG::Record::debug("test");

	//	Sleep(1000);
	//}

	return 0;
}
