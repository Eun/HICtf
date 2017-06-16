#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include "imports.h"


void main() 
{

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char vbuffer[1024];
	{
		const char str[] = { HIDE(SystemDrive, 11) };
		UNHIDE(str);
		if (GetEnvironmentVariableA(buffer, vbuffer, sizeof(vbuffer)) == NULL)
		{
			puts("Something went wrong...\n");
			return;
		}
	}

	{
		const char str[] = { HIDE(\\*, 3) };
		UNHIDE(str);
		strcat(vbuffer, buffer);
		hFind = FindFirstFileA(vbuffer, &FindFileData);
	}
	
	if (hFind == INVALID_HANDLE_VALUE)
	{
		puts("Something went wrong...\n");
		return;
	}
	
	FindClose(hFind);

	{
		const char str[] = { HIDE(PROCESSOR_ARCHITECTURE, 22) };
		UNHIDE(str);
		if (GetEnvironmentVariableA(buffer, vbuffer, sizeof(vbuffer)) == NULL)
		{
			puts("Something went wrong...\n");
			return;
		}
	}

	char fbuffer[1024] = {0};
	{
		const char str[] = { HIDE(%d-%d-%s, 8) };
		UNHIDE(str);
		sprintf(fbuffer, buffer, FindFileData.ftCreationTime.dwHighDateTime, FindFileData.ftCreationTime.dwLowDateTime, vbuffer);
	}
	

	goto pw;

	while (strlen(vbuffer) != strlen(fbuffer) || strcmp(fbuffer, vbuffer) != 0)
	{
		puts("invalid password, ");
	pw:
		memset(vbuffer, 0, sizeof(vbuffer));
		puts("enter password:\n");
		scanf("%s", vbuffer);
	}


	MessageBoxA(NULL, "You found the flag, good work!", "Congratz.", 0);
	return;
}