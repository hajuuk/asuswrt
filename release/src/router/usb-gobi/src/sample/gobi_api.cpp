#include "StdAfx.h"
#include "GobiConnectionMgmtAPI.h"

//---------------------------------------------------------------------------
// Definitions
//---------------------------------------------------------------------------
#define MAX_BUF_SIZE	100


int main(int argc, char **argv){
	ULONG ret;
	CHAR dev[MAX_BUF_SIZE];

	if(argc < 3){
		printf("Usage: gobi_api GOBI_DEVICE command\n");
		exit(0);
	}

	ret = QCWWANConnect((CHAR *)argv[1], (CHAR *)"");
	if(ret != 0){
		printf("QCWWANConnect fail ret = %ld\n", ret);
		exit(ret);
	}

	if(!strcmp(argv[2], "rate")){
		ULONG pCurrentChannelTXRate, pCurrentChannelRXRate, pMaxChannelTXRate, pMaxChannelRXRate;

		ret = GetConnectionRate(&pCurrentChannelTXRate, &pCurrentChannelRXRate, &pMaxChannelTXRate, &pMaxChannelRXRate);
		if(ret == 0)
			printf("    Max Tx %lu, Rx %lu.\n", pMaxChannelTXRate, pMaxChannelRXRate);
		else
			printf("GetConnectionRate fail ret = %ld\n", ret);
	}
	else if(!strcmp(argv[2], "byte")){
		ULONGLONG pTXTotalBytes, pRXTotalBytes;

		ret = GetByteTotals(&pTXTotalBytes, &pRXTotalBytes);
		if(ret == 0)
			printf("Total Bytes: Tx %llu, Rx %llu.\n", pTXTotalBytes, pRXTotalBytes);
		else
			printf("GetByteTotals fail ret = %ld\n", ret);
	}
	else if(!strcmp(argv[2], "hw")){
		CHAR str[MAX_BUF_SIZE];

		ret = GetHardwareRevision(MAX_BUF_SIZE, (CHAR *)str);
		if(ret == 0)
			printf("Hardware Revision: %s.\n", str);
		else
			printf("GetHardwareRevision fail ret = %ld\n", ret);
	}
	else if(!strcmp(argv[2], "icc")){
		CHAR str[MAX_BUF_SIZE];

		ret = UIMGetICCID(MAX_BUF_SIZE, (CHAR *)str);
		if(ret == 0)
			printf("ICCID: %s.\n", str);
		else
			printf("UIMGetICCID fail ret = %ld\n", ret);
	}
	else
		printf("Invalid command %s.\n", argv[2]);

	ret = QCWWANDisconnect();
	if(ret != 0)
		printf("QCWWANDisconnect fail ret = %ld\n", ret);

	return 0;
}
