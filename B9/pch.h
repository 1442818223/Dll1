#pragma once

#include<Windows.h>
#include<iostream>
extern"C" __declspec(dllexport) BOOL InstallHook();
extern"C" __declspec(dllexport) BOOL unInstallHook();


