#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

using namespace std;

#define BUF_SIZE 256
TCHAR* lpName = new TCHAR[256];
TCHAR* szMsg = new TCHAR[256];

int _tmain()
{

    cout << "Enter shared memory name:\n";
    wcin >> szMsg;
    cout << "\n";

    HANDLE hFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        lpName);

    if ((hFile == NULL) && (GetLastError() == 2))
    {
        hFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            BUF_SIZE,
            lpName);
    }
    else
    {
        hFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, lpName);
    }
    if (hFile == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }

    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(hFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hFile);
        return 1;
    }

    int numofact;

   do
    {
        cout << "\nPlease choose an action to do:\n\n" << "1. Read message from shared memory;\n" << "2. Write message to shared memory;\n" << "3. Quit.\n\n";
        cin >> numofact;

        if (numofact == 1)
        {
            cout << "The message says:  ";
            wcout << pBuf << endl;
        }
        else {
            if (numofact == 2)
            {
                memset((void*)pBuf, 0, BUF_SIZE);
                cout << "Enter message text:  ";
                wcin >> szMsg;
                CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
            }
            else {
                if (numofact == 3) {
                    exit(1);
                }
                else if ((numofact != 1) && (numofact != 2) && (numofact != 3))
                {
                    cout << "Uncorrect number\n\n";
                }
            }
        }
   }
   while (true);
    UnmapViewOfFile(pBuf);
    CloseHandle(hFile);

    return 0;
}
