#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>

bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

// Convert UTF-8 std::string → std::wstring safely
std::wstring toWide(const std::string& input) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL, 0);
    std::wstring output(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, &output[0], size_needed);
    return output;
}

int main() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    std::string currentPath(buffer);
    size_t pos = currentPath.find_last_of("\\/");
    std::string exeDir = (pos != std::string::npos) ? currentPath.substr(0, pos) : ".";

    std::string hlvrPath = exeDir + "\\game\\bin\\win64\\HLA-NoVR-Launcher_veeanti.1.exe";

    if (!fileExists(hlvrPath)) {
        MessageBoxA(NULL,
            "Failed to find hlvr.exe in game\\bin\\win64.",
            "HLANoVR Launcher Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Command line
    std::string commandLineStr = "\"" + hlvrPath + "\"";

    std::wstring cmdW = toWide(commandLineStr);  // safe conversion

    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    BOOL result = CreateProcessW(
        NULL,
        &cmdW[0],             // writable buffer required by WinAPI
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
        MessageBoxA(NULL,
            "Failed to launch Half-Life: Alyx.\nCreateProcessW() failed.",
            "HLANoVR Launcher Error",
            MB_OK | MB_ICONERROR);
        return 1;
    }

    // Clean up handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
