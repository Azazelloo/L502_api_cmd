#include "Header.h"

int main(int argc, char* argv[])
	{
		setlocale(LC_ALL, "Russian");

		t_l502_hnd create=L502_Create();

		if (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0)
		{
			std::cout << "*.exe int number_device(номер платы) -const(постоянные уровни)/-impulse(импульсный режим) int state(если выбран режим -const) -single/-repeat(если выбран режим -impulse)" << std::endl;
			system("pause");
		}
		else
		{
			if (argc < 4)
				{
				std::cout << "Not enough arguments!" << std::endl;
				}
			else
			{
				if (connect_L502(&create, argv[1]))//проверяем установку соединения
				{
					if (strcmp(argv[2], "-const") == 0 || strcmp(argv[2], "-impulse") == 0)
					{
						if (strcmp(argv[2], "-const") == 0)
						{
							if (is_number(argv[3]))
							{
								std::stringstream state_const_convert(argv[3]);
								uint32_t state_const_int;
								state_const_convert >> state_const_int;
								if (state_const_int>=0 && state_const_int<=65535)
								{
									set_const_digout(create, state_const_int); //постоянные уровни на цифровых выходах
									L502_Free(create);
								}
								else
								{
									std::cout << "Error const state!" << std::endl;
									L502_Free(create);
								}
							}
							else
							{
								std::cout << "Error const state!" << std::endl;
								L502_Free(create);
							}
						}
						else
						{
							if (strcmp(argv[3], "-single") == 0 || strcmp(argv[3], "-repeat") == 0)
							{
								set_impulse_digout(create, argv[3]); //импульс
							}
							else 
							{
								std::cout << "Error impulse mode!" << std::endl;
								L502_Free(create);
							}
						}
						
					}
					else
					{
						std::cout << "Error device mode!" << std::endl;
						L502_Free(create);
					}
				}
			}
		}
	} 