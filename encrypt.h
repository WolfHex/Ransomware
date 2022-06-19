#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "dirent.h"

extern VOID DirectoryCryptor(std::string DirPath);
extern VOID Encryption(VOID);
extern VOID HTMLFile(VOID);