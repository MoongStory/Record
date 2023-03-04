#include <iostream>

#include "Record.h"

int main()
{
	//MOONG::Record::set_log_file_path("C:/Users/moong/Desktop/Log/MoongRecord.log");
	MOONG::Record::set_log_file_path("./·Î±×/MoongRecord.log");
	MOONG::Record::set_delimiter("[NexessClient]");
	MOONG::Record::set_log_file_size(300);

	while (true)
	{
		MOONG::Record::debug("test");

		Sleep(1000);
	}

	return 0;
}
