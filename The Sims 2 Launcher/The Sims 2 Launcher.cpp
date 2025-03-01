// The Sims 2 Launcher.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "windowsx.h"
#include "combaseapi.h"
#include "shellapi.h"
#include "The Sims 2 Launcher.h"
#include <thread>
#include <vector>
#include <tuple>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define REGISTRY_KEY_PATH "Software\\Electronic Arts\\The Sims 2 Ultimate Collection 25"
#define REGISTRY_KEY_LANG_PATH REGISTRY_KEY_PATH "\\1.0"
#define REGISTRY_LANG_KEY "language"
#define DEFAULT_LANG_INDEX 6


std::vector<std::tuple<std::string, int, std::wstring>> languages = {
    {"Chinese (Simplified)", 17, L"zh_CN"},
    {"Chinese (Traditional)", 18, L"zh_TW"},
    {"Czech", 11, L"cs_CZ"},
    {"Danish", 9, L"da_DK"},
    {"Dutch", 8, L"nl_NL"},
    {"English (United Kingdom)", 13, L"en_GB"},
    {"English (United States)", 1, L"en_US"},
    {"Finnish", 7, L"fi_FI"},
    {"French", 2, L"fr_FR"},
    {"German", 3, L"de_DE"},
    {"Hungarian", 24, L"hu_HU"},
    {"Italian", 4, L"it_IT"},
    {"Japanese", 14, L"ja_JP"},
    {"Korean", 15, L"ko_KR"},
    {"Norwegian", 22, L"no_NO"},
    {"Polish", 20, L"pl_PL"},
    {"Portuguese (Brazil)", 10, L"pt_BR"},
    {"Portuguese (Portugal)", 23, L"pt_PT"},
    {"Russian", 16, L"ru_RU"},
    {"Spanish", 5, L"es_ES"},
    {"Swedish", 6, L"sv_SE"},
    {"Thai", 21, L"th_TH"},
};

void run(const wchar_t* verb, const wchar_t* path, const wchar_t* params, bool wait, bool hide);
void set_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName, const char* data);
void set_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName, int data);
std::string get_cwd_A();

void play_game(int index)
{
    if (index == -1)
    {
        index = DEFAULT_LANG_INDEX;
    }
    auto& data = languages[index];
    std::string cwd = get_cwd_A();
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_LANG_PATH, REGISTRY_LANG_KEY, std::get<1>(data));

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH, "DisplayName", "The Sims 2 Legacy");
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH, "EPsInstalled", "Sims2EP1.exe,Sims2EP2.exe,Sims2EP3.exe,Sims2SP1.exe,Sims2SP2.exe,Sims2EP4.exe,Sims2EP5.exe,Sims2SP4.exe,Sims2SP5.exe,Sims2EP6.exe,Sims2SP6.exe,,Sims2EP7.exe,Sims2SP7.exe,Sims2SP8.exe,Sims2EP8.exe,Sims2EP9.exe");

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2.exe", "Game Registry", "Software\\Electronic Arts\\The Sims 2 Ultimate Collection 25");
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2.exe", "Path", (cwd + "\\Base").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP1.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP1.exe", "Path", (cwd + "\\EP1").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP2.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP2.exe", "Path", (cwd + "\\EP2").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP3.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP3.exe", "Path", (cwd + "\\EP3").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP4.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP4.exe", "Path", (cwd + "\\EP4").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP5.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP5.exe", "Path", (cwd + "\\EP5").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP6.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP6.exe", "Path", (cwd + "\\EP6").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP7.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP7.exe", "Path", (cwd + "\\EP7").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP8.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP8.exe", "Path", (cwd + "\\EP8").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP9.exe", "Game Registry", "Software\\Electronic Arts\\The Sims 2 Ultimate Collection 25");
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP9.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2EP9.exe", "Path", (cwd + "\\EP9").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP1.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP1.exe", "Path", (cwd + "\\SP1").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP2.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP2.exe", "Path", (cwd + "\\SP2").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP4.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP4.exe", "Path", (cwd + "\\SP4").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP5.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP5.exe", "Path", (cwd + "\\SP5").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP6.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP6.exe", "Path", (cwd + "\\SP6").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP7.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP7.exe", "Path", (cwd + "\\SP7").c_str());

    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP8.exe", "Installed", 1);
    set_registry_value(HKEY_CURRENT_USER, REGISTRY_KEY_PATH "\\Sims2SP8.exe", "Path", (cwd + "\\SP8").c_str());

    run(nullptr, L"EP9\\TSBin\\Sims2EP9.exe", (L"-emuGameLang " + std::get<2>(data)).c_str(), false, false);
}

void install_redists(HWND play, HWND redists)
{
    EnableWindow(play, false);
    EnableWindow(redists, false);
    run(L"runas", L"__Installer\\directx\\redist\\dxsetup.exe", L"/silent", true, true);
    run(L"runas", L"__Installer\\vc\\vc2015\\redist\\vc_redist.x86.exe", L"/install /quiet /norestart", true, true);
    run(L"runas", L"__Installer\\vc\\vc2022\\redist\\vc_redist.x86.exe", L"/q /norestart", true, true);
    run(L"runas", L"__Installer\\customcomponent\\vp6\\vp6install.exe", nullptr, true, true);
    EnableWindow(play, true);
    EnableWindow(redists, true);
}

std::string get_cwd_A()
{
    std::vector<char> pathBuf;
    DWORD copied = 0;
    do {
        pathBuf.resize(pathBuf.size() + MAX_PATH);
        copied = GetModuleFileNameA(nullptr, &pathBuf[0], pathBuf.size());
    } while (copied >= pathBuf.size());
    pathBuf.resize(copied);
    std::string path(pathBuf.begin(), pathBuf.end());

    size_t pos = path.find_last_of("\\/");
    path.erase(pos);
    return path;
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

int get_registry_value(HKEY hkey, LPCSTR subKey, LPCSTR keyName)
{
    DWORD val;
    DWORD dataSize = sizeof(val);
    LSTATUS result = RegGetValueA(hkey, subKey, keyName, RRF_RT_DWORD, nullptr, &val, &dataSize);
    if (result != ERROR_SUCCESS)
    {
        return -1;
    }
    return val;
}

INT_PTR CALLBACK Launcher(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND combo, play, redists;
    static int old_lang;
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
