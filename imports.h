/**
* HideImports 1.1
*
* Copyright (C) 2015-2016 by Tobias Salzmann
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <Windows.h>
#include <stdio.h>

#define C(x) char((x) - 50)
#define UN(x) char((x) + 50)


#define S(x) #x

#define HIDE(x,y) HIDE##y(x),C(0)

#define HIDE1(x) C(S(x)[0])
#define HIDE2(x) HIDE1(x),C(S(x)[1])
#define HIDE3(x) HIDE2(x),C(S(x)[2])
#define HIDE4(x) HIDE3(x),C(S(x)[3])
#define HIDE5(x) HIDE4(x),C(S(x)[4])
#define HIDE6(x) HIDE5(x),C(S(x)[5])
#define HIDE7(x) HIDE6(x),C(S(x)[6])
#define HIDE8(x) HIDE7(x),C(S(x)[7])
#define HIDE9(x) HIDE8(x),C(S(x)[8])
#define HIDE10(x) HIDE9(x),C(S(x)[9])
#define HIDE11(x) HIDE10(x),C(S(x)[10])
#define HIDE12(x) HIDE11(x),C(S(x)[11])
#define HIDE13(x) HIDE12(x),C(S(x)[12])
#define HIDE14(x) HIDE13(x),C(S(x)[13])
#define HIDE15(x) HIDE14(x),C(S(x)[14])
#define HIDE16(x) HIDE15(x),C(S(x)[15])
#define HIDE17(x) HIDE16(x),C(S(x)[16])
#define HIDE18(x) HIDE17(x),C(S(x)[17])
#define HIDE19(x) HIDE18(x),C(S(x)[18])
#define HIDE20(x) HIDE19(x),C(S(x)[19])
#define HIDE21(x) HIDE20(x),C(S(x)[20])
#define HIDE22(x) HIDE21(x),C(S(x)[21])
#define HIDE23(x) HIDE22(x),C(S(x)[22])
#define HIDE24(x) HIDE23(x),C(S(x)[23])
#define HIDE25(x) HIDE24(x),C(S(x)[24])
#define HIDE26(x) HIDE25(x),C(S(x)[25])
#define HIDE27(x) HIDE26(x),C(S(x)[26])
#define HIDE28(x) HIDE27(x),C(S(x)[27])
#define HIDE29(x) HIDE28(x),C(S(x)[28])
#define HIDE30(x) HIDE29(x),C(S(x)[29])


#define UNHIDE(x) \
char buffer[128] = {0}; \
do { \
	for (int i = 0; ; ++i) { \
		buffer[i] = UN(x[i]); \
		if (buffer[i] == 0) { \
			break; \
		} \
	} \
} while (0)



static inline FARPROC GetProcAddressEncrypted(HMODULE hModule, const char* szName)
{
	UNHIDE(szName);
	return GetProcAddress(hModule, buffer);
}

static inline HMODULE GetModuleHandleEncrypted(const char* szName)
{
	UNHIDE(szName);
	return GetModuleHandleA(buffer);
}

const char szKernel32[] = { HIDE(kernel32, 8) };
const char szLoadLibraryA[] = { HIDE(LoadLibraryA, 12) };
typedef HMODULE(WINAPI* PLoadLibraryA)(LPCSTR);
PLoadLibraryA pfszLoadLibraryA;

static inline HMODULE LoadLibraryEncrypted(const char* szName) {
	UNHIDE(szName);
	if (pfszLoadLibraryA == NULL) {	
		pfszLoadLibraryA = (PLoadLibraryA)GetProcAddressEncrypted(GetModuleHandleEncrypted(szKernel32), szLoadLibraryA);
	}

	return pfszLoadLibraryA(buffer);
}



const char szUser32[] = { HIDE(user32, 6) };
const char szMessageBoxA[] = { HIDE(MessageBoxA, 11) };
typedef int(WINAPI* PMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
PMessageBoxA pfszMessageBoxA = (PMessageBoxA)GetProcAddressEncrypted(LoadLibraryEncrypted(szUser32), szMessageBoxA);
#define MessageBoxA pfszMessageBoxA

const char szGetEnvironmentVariableA[] = { HIDE(GetEnvironmentVariableA, 23) };
typedef DWORD(WINAPI* pGetEnvironmentVariable)(LPCSTR, LPSTR, DWORD);
pGetEnvironmentVariable pfszGetEnvironmentVariableA = (pGetEnvironmentVariable)GetProcAddressEncrypted(LoadLibraryEncrypted(szKernel32), szGetEnvironmentVariableA);
#define GetEnvironmentVariableA pfszGetEnvironmentVariableA


const char szFindFirstFileA[] = { HIDE(FindFirstFileA, 14) };
typedef HANDLE(WINAPI* pFindFirstFileA)(LPCSTR, LPWIN32_FIND_DATA);
pFindFirstFileA pfszFindFirstFileA = (pFindFirstFileA)GetProcAddressEncrypted(LoadLibraryEncrypted(szKernel32), szFindFirstFileA);
#define FindFirstFileA pfszFindFirstFileA


const char szFindClose[] = { HIDE(FindClose, 9) };
typedef BOOL(WINAPI* pFindClose)(HANDLE);
pFindClose pfszFindClose = (pFindClose)GetProcAddressEncrypted(LoadLibraryEncrypted(szKernel32), szFindClose);
#define FindClose pfszFindClose
