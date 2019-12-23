#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "../inc/l502api.h"
#include "../inc/e502api.h"
#include "../inc/x502api.h"
#include <iostream>
#include <string>
#include <sstream>
#define	  stop __asm nop

 bool connect_L502(t_l502_hnd* create,char* num_l502);
 void set_const_digout(t_l502_hnd create,uint32_t state);
 void set_impulse_digout(t_l502_hnd create, char* imp_mode);
 bool is_number(const char* str);