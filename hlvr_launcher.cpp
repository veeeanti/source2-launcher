#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>

bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

int main () {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string currentPath(buffer);
    std::string exePath = currentPath.substr(0, currentPath.find_last_of("\\/")) + "\\hlvr.exe";
    if (pos != std::string::npos) {
        exepath = std::string(buffer).substr(0, pos);
    }

    else {
        exepath = ".\\game\\bin\\win64";
    }   std::string hlvrPath = exepath + "\\hlvr.exe";
    
    if (fileExists(hlvrPath)) {
        MessageBoxA(NULL, "Are you certain you're running this from the correct directory? It should be placed right next to the game folder inside the main Half-Life Alyx folder. Try again and if it still has trouble, look for the hlvr.exe file in the game\\bin\\win64 folder and run that directly.", "HLA Launcher Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    std::wstring commandLine = L".\\game\\bin\\win64\\hlvr.exe -vr -steam -noasserts -nopassiveasserts +map startup";
    BOOL result = CreateProcessW(
        NULL,
        &commandLine[0],
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!result) {
        MessageBoxA(NULL, "Failed to launch Half-Life: Alyx. Please ensure the game is installed correctly. This shouldn't happen.", "HLA Launcher Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
