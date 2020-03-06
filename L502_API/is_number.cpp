#include "Header.h"

bool is_number(const char* str)
{
	char* end;
	long i=strtol(str,&end,10);
	if (errno == ERANGE) 
		{
			std::cout << "Range error!"<<std::endl;
			errno = 0;
			return false;
		}
	else if (strlen(end)==0)
		{
			return true;
		}
	else
	{
		std::cout << "Conversion error!" << std::endl;
		return false;
	}
}