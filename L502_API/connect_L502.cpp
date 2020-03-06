#include "Header.h"

bool connect_L502(t_l502_hnd* create, char* num_l502)
{
	uint32_t counter;
	char serials[5][32];
	L502_GetSerialList(serials, 2, NULL, &counter);

	if (is_number(num_l502))
	{
		//конвертируем строковый аргумент в int
		std::stringstream num_l502_convert(num_l502);
		int num_l502_int;
		num_l502_convert >> num_l502_int;

		if (num_l502_int >= 0)
		{
			int err = L502_Open(*create, serials[num_l502_int]);
			if (err != 0)
			{
				std::cout << "----Error connection!" << std::endl;
				return false;
			}
			else
			{
				std::cout << serials[num_l502_int] << " Connected!" << std::endl;
				return true;
			}
		}
		else
		{
			std::cout << "----Device does not exist!" << std::endl;
			return false;
		}
	}
	
	else
	{
		std::cout << "----Input  error!" << std::endl;
		return false;
	}
}
