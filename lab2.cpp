#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

using namespace std;

#define BUF_SIZE 256
TCHAR* lpName=new TCHAR[256];
TCHAR* szMsg=new TCHAR[256];

int _tmain()
{
    using namespace std;

    std::cout<<"Enter shared memory name:\n";
    std::cin>>szMsg;
    std::cout<<"\n";

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
    if (hFile == NULL)
    {
       _tprintf(TEXT("Could not create file mapping object (%d).\n"),
             GetLastError());
      return 1;
    }

   LPCTSTR pBuf = (LPTSTR) MapViewOfFile(hFile,
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

   while (hFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,lpName))
    {
        std::cout<<"\nPlease choose an action to do:\n\n"<<"1. Read message from shared memory;\n"<<"2. Write message to shared memory;\n"<<"3. Quit.\n\n";
        std::cin>>numofact;

        if (numofact==1)
        {
            std::cout<<"The message says:  "<<pBuf<<std::endl;
        }
        else {
            if (numofact==2)
                {
                    memset((void*)pBuf,0,BUF_SIZE);
                    std::cout<<"Enter message text:  ";
                    std::cin >> szMsg;
                    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
                }
            else {
                if (numofact==3){
                        exit(1);
                }
                else if ((numofact!=1)&&(numofact!=2)&&(numofact!=3))
                    { std::cout<<"Uncorrect number\n\n";
                    }}}
        }

    UnmapViewOfFile(pBuf);
    CloseHandle(hFile);

    return 0;
}
