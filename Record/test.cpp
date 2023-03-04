#include <iostream>

#include "Old_Record.h"

int main()
{
	MOONG::Old_Record::set_delimiter("[NexessClient]");

	MOONG::Old_Record::debug("test");

	return 0;
}
