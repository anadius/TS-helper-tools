// The Sims 1 Launcher.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "windowsx.h"
#include "combaseapi.h"
#include "shellapi.h"
#include "The Sims 1 Launcher.h"
#include <thread>
#include <vector>
#include <tuple>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define REGISTRY_KEY_PATH "Software\\Electronic Arts\\The Sims 25"
#define REGISTRY_KEY_LANG_PATH REGISTRY_KEY_PATH
#define REGISTRY_LANG_KEY "SIMS_LANGUAGE"
#define DEFAULT_LANG_INDEX 3


std::vector<std::tuple<std::string, std::string, int>> languages = {
    {"Danish", "Danish", 1},
    {"German", "German", 2},
    {"English (United Kingdom)", "UKEnglish", 2},
    {"English (United States)", "USEnglish", 1},
    {"Spanish", "Spanish", 1},
    {"Finnish", "Finnish", 1},
    {"French", "French", 2},
    {"Italian", "Italian", 2},
    {"Japanese", "Japanese", 5},
    {"Korean", "Korean", 8},
    {"Dutch", "Dutch", 2},
    {"Norwegian", "Norwegian", 1},
    {"Polish", "Polish", 4},
    {"Portuguese", "Portuguese", 3},
    {"Swedish", "Swedish", 2},
    {"Thai", "Thai", 7},
    {"Chinese (Simplified)", "SimplifiedChinese", 9},
    {"Chinese (Traditional)", "TraditionalChinese", 6},
};

void run(const wchar_t* verb, const wchar_t* path, const wchar_t* params, bool wait, bool hide);
void set_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName, const char* data);
void set_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName, int data);

void play_game(int index)
{
    if (index == -1)
    {
        index = DEFAULT_LANG_INDEX;
    }
    auto& data = languages[index];
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_LANG_PATH, REGISTRY_LANG_KEY, std::get<1>(data).c_str());
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_LANG_PATH, "SIMS_OTHERLANGUAGE", std::get<1>(data).c_str());
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_LANG_PATH, "SIMS_SKU", std::get<2>(data));

    run(nullptr, L"sims.exe", nullptr, false, false);
}

void install_redists(HWND play, HWND redists)
{
    EnableWindow(play, false);
    EnableWindow(redists, false);
    run(L"runas", L"__Installer\\vc\\vc2015\\redist\\vc_redist.x86.exe", L"/install /quiet /norestart", true, true);
    run(L"runas", L"__Installer\\vc\\vc2022\\redist\\vc_redist.x86.exe", L"/q /norestart", true, true);
    EnableWindow(play, true);
    EnableWindow(redists, true);
}

std::wstring get_cwd()
{
    std::vector<wchar_t> pathBufW;
    DWORD copied = 0;
    do {
        pathBufW.resize(pathBufW.size() + MAX_PATH);
        copied = GetModuleFileNameW(nullptr, &pathBufW[0], pathBufW.size());
    } while (copied >= pathBufW.size());
    pathBufW.resize(copied);
    std::wstring path(pathBufW.begin(), pathBufW.end());

    size_t pos = path.find_last_of(L"\\/");
    path.erase(pos);
    return path;
}

void run(const wchar_t* verb, const wchar_t* path, const wchar_t* params, bool wait, bool hide)
{
    static std::wstring currentDir;
    if (currentDir.empty())
    {
        currentDir = get_cwd();
    }
    std::wstring full_path = currentDir + path;

    SHELLEXECUTEINFO sei = { 0 };
    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.fMask = wait ? SEE_MASK_NOCLOSEPROCESS : 0;
    sei.hwnd = nullptr;
    sei.lpVerb = verb;
    sei.lpFile = path;
    sei.lpParameters = params;
    sei.lpDirectory = currentDir.c_str();
    sei.nShow = hide ? SW_HIDE : SW_SHOW;

    if (ShellExecuteEx(&sei) && sei.hProcess != 0) {
        if (wait)
        {
            WaitForSingleObject(sei.hProcess, INFINITE);
        }

        CloseHandle(sei.hProcess);
    }
}

void _set_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName, DWORD type, const BYTE* lpData, DWORD cbData)
{
    HKEY default_key;
    auto status = RegCreateKeyExA(hkey, subKey, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, nullptr, &default_key, nullptr);
    if (status == ERROR_SUCCESS)
    {
        RegSetValueExA(default_key, keyName, 0, type, lpData, cbData);
        RegCloseKey(default_key);
    }
}
void set_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName, const char* data)
{
    _set_registry_value(hkey, subKey, keyName, REG_SZ, (const BYTE*)data, strlen(data) + 1);
}
void set_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName, int data)
{
    _set_registry_value(hkey, subKey, keyName, REG_DWORD, (const BYTE*)&data, sizeof(data));
}

void centerWindow(HWND hwndDlg)
{
    HWND hwndOwner = GetDesktopWindow();
    RECT rc, rcDlg, rcOwner;

    GetWindowRect(hwndOwner, &rcOwner);
    GetWindowRect(hwndDlg, &rcDlg);
    CopyRect(&rc, &rcOwner);

    // Offset the owner and dialog box rectangles so that right and bottom 
    // values represent the width and height, and then offset the owner again 
    // to discard space taken up by the dialog box. 

    OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
    OffsetRect(&rc, -rc.left, -rc.top);
    OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

    // The new position is the sum of half the remaining space and the owner's 
    // original position. 

    SetWindowPos(hwndDlg,
        HWND_TOP,
        rcOwner.left + (rc.right / 2),
        rcOwner.top + (rc.bottom / 2),
        0, 0,          // Ignores size arguments. 
        SWP_NOSIZE);
}

std::string get_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName)
{
    DWORD length = 0;
    LSTATUS result = RegGetValueA(hkey, subKey, keyName, RRF_RT_REG_SZ, nullptr, nullptr, &length);
    if (result != ERROR_SUCCESS)
    {
        return "";
    }
    std::vector<char> buffer(length);
    result = RegGetValueA(hkey, subKey, keyName, RRF_RT_REG_SZ, nullptr, &buffer[0], &length);
    if (result != ERROR_SUCCESS)
    {
        return "";
    }
    return &buffer[0];
}

INT_PTR CALLBACK Launcher(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND combo, play, redists;
    static std::string old_lang;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SendMessage(hDlg, WM_SETICON, ICON_SMALL,
            (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON)));
        combo = GetDlgItem(hDlg, IDC_LANG);
        play = GetDlgItem(hDlg, IDC_PLAY);
        redists = GetDlgItem(hDlg, IDC_REDISTS);
        old_lang = get_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_LANG_PATH, REGISTRY_LANG_KEY);
        for (auto& it : languages)
        {
            int index = SendMessageA(combo, CB_ADDSTRING, 0L, (LPARAM)std::get<0>(it).c_str());
            if (std::get<1>(it) == old_lang)
            {
                SendMessageA(combo, CB_SETCURSEL, index, 0);
            }
        }
        if (SendMessageA(combo, CB_GETCURSEL, 0, 0) == -1)
        {
            SendMessageA(combo, CB_SETCURSEL, DEFAULT_LANG_INDEX, 0);
        }
        centerWindow(hDlg);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_PLAY)
        {
            play_game(SendMessageA(combo, CB_GETCURSEL, 0, 0));
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_REDISTS)
        {
            std::thread(install_redists, play, redists).detach();
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    std::ignore = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_LAUNCHER), NULL, Launcher);
    return 0;
}
