#include "Header.h"

void set_const_digout(t_l502_hnd create, uint32_t state)
{
	std::cout << "---Constant level setting---" << std::endl;
	L502_AsyncOutDig(create, state, NULL);
	std::cout << "----Const outputs mode OFF!" << std::endl;
}