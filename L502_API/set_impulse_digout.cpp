#include "Header.h"

void set_impulse_digout(t_l502_hnd create, char* imp_mode)
{
	L502_StreamsEnable(create, L502_STREAM_DOUT);

	int impulse_length = GetPrivateProfileInt("impulse_length", "length", -1, "../inc/set_impulse.ini");
	if (impulse_length > 0)
	{
		uint32_t* impulse_array = new uint32_t[impulse_length]{};//выделяем память под массив импульса
		char str_i[8];
		int state,period,delay;
		for (int i = 1; i <= 16; i++)
		{
			_itoa(i, str_i, 10);
			state = GetPrivateProfileInt(str_i, "state", -1, "../inc/set_impulse.ini");
			if (state==1)
			{
				period= GetPrivateProfileInt(str_i, "period", -1, "../inc/set_impulse.ini");
				delay= GetPrivateProfileInt(str_i, "delay", -1, "../inc/set_impulse.ini");
				for (int j=delay;j<period+delay;j++)
				{
					impulse_array[j] = impulse_array[j] + pow(2,i-1);
				}
			}
		}

		if (strcmp(imp_mode,"-repeat")==0)
		{
			//повторяющийся импульс
			std::cout << "...Impulse repeating..." << std::endl;
			L502_OutCycleLoadStart(create, impulse_length);
			L502_Send(create, impulse_array, impulse_length, 10);
			L502_OutCycleSetup(create, L502_OUT_CYCLE_FLAGS_FORCE);
			L502_StreamsStart(create);

			int flag= GetPrivateProfileInt("impulse_flag", "imp_state", -1, "../inc/set_impulse.ini");
			while (flag)
			{
				flag = GetPrivateProfileInt("impulse_flag", "imp_state", -1, "../inc/set_impulse.ini");
			}
		}
		else if (strcmp(imp_mode, "-single") == 0)
		{
			std::cout << "...Impulse single..." << std::endl;
			L502_PreloadStart(create);
			L502_PrepareData(create,NULL,NULL, impulse_array, impulse_length, L502_DAC_FLAGS_VOLT,NULL);
			L502_Send(create, impulse_array, impulse_length,10);
			L502_StreamsStart(create);
		}
		//останавливаем импульс по нажатию клавиши
		//system("pause");
		//L502_StreamsStop(create);
		//std::cout << "----Impulse stopped!"<<std::endl;
		delete[] impulse_array;
	}
	else
	{
		std::cout << "----Change impulse length!" << std::endl;
	}
}