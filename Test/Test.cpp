// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "my_base64.h"
int _tmain(int argc, _TCHAR* argv[])
{
	char* ch1 = base64_encode2("ÄãºÃ£¬ÊÀ½ç");
	char* ch2 = base64_decode(ch1);
	return 0;
}

