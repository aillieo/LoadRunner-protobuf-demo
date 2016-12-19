#include "lrs.h"


Action()
{

	char* sendStr;
	char* rece;
	int receLen = 0;
	char* name;


	lrs_create_socket("socket0", "TCP", "LocalHost=0", "RemoteHost=192.168.1.200:2000", LrsLastArg);

	
	rece = (char*)malloc(1024 * sizeof(char));
	sendStr = (char*)malloc(1024 * sizeof(char));
	name = (char*)malloc(128 * sizeof(char));

	receLen = getSerializedName(rece, "TestingName");

	
	dataToHex(rece, sendStr, receLen );


	lrs_set_send_buffer("socket0", sendStr , strlen(sendStr) );
	lrs_send("socket0", "buf0", LrsLastArg);
	

	custom_lrs_receive("socket0", "buf1", LrsLastArg);

	
	lrs_get_last_received_buffer("socket0", &rece, &receLen);

	getParsedName(name, rece, receLen);


	lr_output_message("name from sever is %s ",name);


	free(rece);
	free(sendStr);
	free(name);


	lrs_close_socket("socket0");


    return 0;
}





int dataToHex(char* src, char* des, int length )
{
	int i = 0 ;
	for(i = 0; i < length ; i++ )
	{
		char hex[5];
		sprintf(hex,"\\x%02X",(unsigned char)src[i]);
		memcpy(des + i*4 , hex,4);
	}
	memcpy(des + length * 4 , "\0",4);

	return 0;


}



int custom_lrs_receive(char *sock_desc, char *buf_desc,void *dummy)
{
	int rc;
	
	int buf_len = 4;
	
	char szBytesLength[30], *buf = NULL, *pszError, *pszLastChar;

	rc = lrs_receive_ex(sock_desc, buf_desc, "NumberOfBytesToRecv=4", LrsLastArg);	

	if (rc != 0)     
	{

		return -1;
	}

	lrs_get_last_received_buffer(sock_desc, &buf, &buf_len);

	if (buf == NULL || buf_len != 4)
	{
		lr_error_message("receive of %s failed", buf_desc);

		return -1;
	}


	sprintf (szBytesLength, "NumberOfBytesToRecv=%d", fiFromHexBinToInt(buf));

	lr_debug_message(LR_MSG_CLASS_FULL_TRACE, "!!!! Bytes length = %s", szBytesLength);

	
	rc = lrs_receive_ex(sock_desc, buf_desc, szBytesLength, LrsLastArg);



	if (rc != 0) 
		return -1;




	return 0;
}


int fiFromHexBinToInt (char *szBuffer)
{

    int i, j, iIntValue = 0, iExp = 1;

    for( i = 3; i >= 0; i--)
    {
        iExp = 1;

        for (j = 6; j > i*2; j--)
            iExp *= 16;

        iIntValue += (szBuffer[i] & 0x0000000f) * iExp + ((szBuffer[i] & 0x000000f0) >> 4) * iExp * 16;

    }

    return iIntValue;

}
