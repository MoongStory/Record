#include <iostream>

#include "Record.h"

int main()
{
	//MOONG::Record::set_log_file_path("C:/Users/moong/Desktop/MoongRecord.log");
	MOONG::Record::set_delimiter("[NexessClient]");

	MOONG::Record::debug("test");

	return 0;
}
