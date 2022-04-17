/*
		Developed by Lexa
		Offset: 0xB7CE50
		Instagram: https://www.instagram.com/onurlexa/
		Git Hub: https://github.com/lyrexdrexy
		Discord: https://discord.gg/7trg7ehkXY
*/

#include <iostream>
#include <windows.h>

using namespace std;

void error(string errMsg);
long int readFromMem(DWORD address, LPCSTR windowName);
void writeToMem(DWORD address, LPCSTR windowName, long int newValue);

int main()
{
	system("color 0a");
	system("title San Andreas Money Hack by Lexa");

	DWORD address = 0xB7CE50;
	LPCSTR windowName = "GTA: San Andreas";

	try
	{
		long int currentMoney = readFromMem(address, windowName);
		long int newAmount = 0;

		cout << "San Andreas Money Hack by Lexa" << endl;
		cout << endl << "Current Money = " << currentMoney << endl;

	moneyError:
		cout << "Enter New Money Amount: ",
			cin >> newAmount;

		if (newAmount > 999999999 || newAmount < 0)
		{
			cout << endl << "MONEY AMOUNT CAN ONLY BE FROM 0 TO 999,999,999 Try Again..." << endl;
			goto moneyError;
		}

		else
		{
			writeToMem(address, windowName, newAmount);
			cout << "Success" << endl << endl;
		}

		system("pause");
	}

	catch (string erreMsg)
	{
		cout << erreMsg << endl;;
	}

	return 0;
}

void error(string errMsg)
{
	throw errMsg;
}

long int readFromMem(DWORD address, LPCSTR windowName)
{
	long int value;
	HWND windowHandle = FindWindow(0, windowName);

	if (!windowHandle)
	{
		error("error, can't find window [LAUNCH GAME!]");
	}

	else
	{
		DWORD processId;
		GetWindowThreadProcessId(windowHandle, &processId);
		HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

		if (!processHandle)
		{
			error("error, can't find process [RUN THIS EXE AS ADMIN]");
		}

		else
		{
			int status = ReadProcessMemory(processHandle, (LPVOID)address, &value, sizeof(value), 0); //LPVOID = void *
			CloseHandle(processHandle);

			if (status > 0)
			{
				return value;
			}

			else
			{
				error("error, failed to read value [RUN THIS EXE AS ADMIN]");
			}
		}
	}
}

void writeToMem(DWORD address, LPCSTR windowName, long int newValue)
{
	HWND windowHandle = FindWindow(0, windowName);

	if (!windowHandle)
	{
		error("error, can't find window [RUN THIS EXE AS ADMIN]");
	}

	else
	{
		DWORD processId;
		GetWindowThreadProcessId(windowHandle, &processId);
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

		if (!processHandle)
		{
			error("error, can't find process [RUN THIS EXE AS ADMIN]");
		}

		else
		{
			int status = WriteProcessMemory(processHandle, (LPVOID)address, &newValue, (DWORD)sizeof(newValue), NULL);
			CloseHandle(processHandle);

			if (status < 0)
			{
				error("error, failed to write value [RUN THIS EXE ADMIN]");
			}
		}
	}
}