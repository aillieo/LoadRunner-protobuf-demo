#include "lrs.h"


vuser_init()
{
	int ret = 0;

    lrs_startup(257);	

	ret = lr_load_dll("pb_dll.dll");


	if(ret != 0)
	{
		lr_error_message("fail load dll");
	}


    return 0;
}

