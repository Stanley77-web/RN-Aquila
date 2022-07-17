#include <iostream>
#include <string>   
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#define target_process "target-program.exe"
#define border std::cout << " =========================================" << std::endl;

void print_ps_name(DWORD pid) {
    TCHAR pname[MAX_PATH] = TEXT("<unknown>");
    HANDLE phandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (phandle != NULL) {
        HMODULE pmod;
        DWORD temp;
        if (EnumProcessModules(phandle, &pmod, sizeof(pmod), &temp))
            GetModuleBaseName(phandle, pmod, pname, sizeof(pname) / sizeof(TCHAR));
    }
    CloseHandle(phandle);
    _tprintf(TEXT("%s (PID %u)\n"), pname, pid);
    
}

void print_ps() {
    DWORD ps_list[1024], ps_memctr, ps_ctr;
    if (!EnumProcesses(ps_list, sizeof(ps_list), &ps_memctr))
        return;
    ps_ctr = ps_memctr / sizeof(DWORD);
    for (int i = 0; i < ps_ctr; i++)
        if (ps_list[i] != 0) {
            std::cout << i+1 << ". ";
            print_ps_name(ps_list[i]);
        }   
}

void find_pidps(DWORD *pid) {
    DWORD ps_list[1024], ps_memctr, ps_ctr;
    if (!EnumProcesses(ps_list, sizeof(ps_list), &ps_memctr))
        return;
    ps_ctr = ps_memctr / sizeof(DWORD);
    for (int i = 0; i < ps_ctr; i++)
        if (ps_list[i] != 0) {
            TCHAR pname_tmp[MAX_PATH] = TEXT("<unknown>");
            HANDLE phandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ps_list[i]);
            wchar_t *pname; 
            if (phandle != NULL) {
                HMODULE pmod;
                DWORD temp;
                if (EnumProcessModules(phandle, &pmod, sizeof(pmod), &temp))
                    GetModuleBaseName(phandle, pmod, pname_tmp, sizeof(pname_tmp) / sizeof(TCHAR));
            }
            if (!strcmp((char *) pname_tmp, target_process)) {
                *pid = ps_list[i];
                return;
            }
            CloseHandle(phandle);
        }
}

int main() {
    DWORD pid;
    LONGLONG address;
    SIZE_T size, access_size;
    HANDLE ptarget;

    char buffer[1024];
    int bufint;
    unsigned int bufuint;

    int choice;
    
    find_pidps(&pid);


    ptarget = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (ptarget == NULL) {
        _tprintf(TEXT("OpenProcess failed: %d\n"), GetLastError());
        return 1;
    } 

    access_size = 11;
    std::cout << "Enter address: ";
    std::cin >> std::hex >> address;
    _tprintf(TEXT("\nOpen Process PID (%u) at memory address 0x%x success\n"), pid, address);

    while (true) {
        memset(buffer, 0, 1024);

        std::cout << std::endl << "                Main Menu " << std::endl;
        border
        std::cout << "| 1. Show Processes                       |" << std::endl;
        std::cout << "| 2. Read Memory                          |" << std::endl;
        std::cout << "| 3. Write Memory                         |" << std::endl;
        std::cout << "| 4. Set Bytes (only for string)          |" << std::endl;
        std::cout << "| 5. Exit                                 |" << std::endl;
        border
        std::cout << ">> ";
        std::cin >> choice;

        if (choice == 5) break;
        else if (choice == 1) {
            std::cout << "Processes " << std::endl;
            print_ps();
        } else if (choice == 2) {
            int suc = 
                ReadProcessMemory(ptarget, (LPCVOID) address, &bufint, sizeof(bufint), &size) &&
                ReadProcessMemory(ptarget, (LPCVOID) address, &bufuint, sizeof(bufuint), &size) &&
                ReadProcessMemory(ptarget, (LPCVOID) address, (LPVOID) buffer, access_size, &size);
            if (!suc) {
                _tprintf(TEXT("ReadProcessMemory failed: %d\n"), GetLastError());
            } else {
                std::cout << "Read Memory success" << std::endl;
                std::cout << "Memory at 0x" << std::hex << address << " from target process";
                _tprintf(TEXT(" (PID %u) "),  pid);
                std::cout << ": " << std::endl; 
                _tprintf(TEXT("%s (string)\n"), buffer);
                _tprintf(TEXT("0x%x (hexadecimal)\n"), bufint);
                _tprintf(TEXT("%d (decimal)\n"), bufint);
                _tprintf(TEXT("%u (unsigned decimal)\n"), bufint);
            }
        } else if (choice == 3) {
            int type;
            int succ = 0;
            
            std::cout << "Enter type message:  " << std::endl;
            std::cout << "1. String" << std::endl;
            std::cout << "2. Hexadecimal" << std::endl;
            std::cout << "3. Decimal" << std::endl;
            std::cout << "4. Unsigned Decimal" << std::endl << ">> ";
            std::cin >> type;
            
            std::cout << "Enter message ";
            if (type == 1) {
                std::string message_in;
                char message[1024];
                
                std::cout << "(string): ";
                std::cin.ignore (100, '\n');
                std::getline(std::cin, message_in);

                strcpy(message, message_in.c_str());
                succ = WriteProcessMemory(ptarget, (LPVOID) address, (LPCVOID) message, access_size, NULL);
            } else if (type == 2) {
                std::cout << "(hexadecimal): ";
                std::cin >> std::hex >> bufint;

                succ = WriteProcessMemory(ptarget, (LPVOID) address, &bufint, sizeof(bufint), NULL);
            } else if (type == 3) {
                std::cout << "(decimal): ";
                std::cin >> std::dec >> bufint;

                succ = WriteProcessMemory(ptarget, (LPVOID) address, &bufint, sizeof(bufint), NULL);
            } else if (type == 4) {
                std::cout << "(unsigned decimal): ";
                std::cin >> bufuint;

                succ = WriteProcessMemory(ptarget, (LPVOID) address, &bufuint, sizeof(bufuint), NULL);
            }

            if (!succ) {
                _tprintf(TEXT("WriteProcessMemory failed: %d\n"), GetLastError());
            } else {
                std::cout << "Write Memory success" << std::endl;
            }
        } else if (choice == 4) {
            std::cout << "Current access size: " << std::dec << access_size << " byte(s)" << std::endl;

            std::cout << "Enter new access size: ";
            std::cin >> std::dec >> access_size;
        } 
    }     
    
    CloseHandle(ptarget);
    return 0;
}

