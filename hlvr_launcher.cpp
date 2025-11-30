#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>

bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

int main() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string currentPath(buffer);
    size_t pos = currentPath.find_last_of("\\/");
    std::string exeDir = (pos != std::string::npos) ? currentPath.substr(0, pos) : ".";

    std::string hlvrPath;

    // Check if hlvr.exe is in the same directory as the launcher
    hlvrPath = exeDir + "\\hlvr.exe";
    if (fileExists(hlvrPath)) {
        // Launcher is placed in game\bin\win64
    } else {
        // Check in game\bin\win64 relative to launcher directory
        hlvrPath = exeDir + "\\game\\bin\\win64\\hlvr.exe";
        if (!fileExists(hlvrPath)) {
            MessageBoxA(NULL, "Failed to find hlvr.exe. Ensure the launcher is placed in the Half-Life Alyx root folder or in the game\\bin\\win64 folder.", "HLA Launcher Error", MB_OK | MB_ICONERROR);
            return 1;
        }
    }

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    std::string commandLineStr = "\"" + hlvrPath + "\" -vr -steam -noasserts -nopassiveasserts +map startup";
    std::wstring commandLine(commandLineStr.begin(), commandLineStr.end());
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
        MessageBoxA(NULL, "Failed to launch Half-Life: Alyx. Unfortunately, I don't have the slightest clue why. Sorry.", "HLA Launcher Error", MB_OK | MB_ICONERROR);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
