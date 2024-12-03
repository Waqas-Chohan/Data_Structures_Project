#include <windows.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include "Helper.h"

using namespace std;

void Helper::load()
{
    system("cls");
    system("Color 3F");
    cout << "\n\n\n\n\n\n\n\n\n\t\t\t\tWELCOME TO MINI INSTAGRAM";
    // Set ASCII to print special character. // Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int barl = 177, bar2 = 219;
    cout << "\n\n\t\t\t\t";
    for (int i = 0; i < 25; i++)
        cout << (char)barl;
    cout << "\r";
    cout << "\t\t\t\t";
    for (int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(100);
    }
    cout << "\n\t\t\t\tChecking for updates";
    cout << ".";
    Sleep(800);
    cout << ".";
    Sleep(800);
    cout << ".";
    Sleep(800);
    cout << "\n\t\t\t\tPress Enter or any key to continue:\n";
    cin.clear();
    _getch();
    system("cls");
}

void Helper::FullScreen()
{
    // Simulate pressing the F11 key
    INPUT input{};
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    // Press F11
    input.ki.wVk = VK_F11;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));

    // Release F11
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void Helper::DisplayInBox(const string& message, int spacing, char border)
{
    // Find the length of the message and the box
    int messageLength = message.length();
    int boxWidth = messageLength + (spacing * 2) + 2;

    // Print the top border
    for (int i = 0; i < boxWidth; ++i) {
        cout << border;
    }
    cout << endl;

    // Print the message with padding
    cout << "|";
    for (int i = 0; i < spacing; i++)
    {
        cout << " ";
    }
    cout << message;
    for (int i = 0; i < spacing; i++)
    {
        cout << " ";
    }
    cout << "|" << endl;

    // Print the bottom border
    for (int i = 0; i < boxWidth; ++i) {
        cout << border;
    }
    cout << endl;
}

int Helper::read_input(int start, int end)
{
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good() && (input >= start && input <= end))
        {
            //everything went well, we'll get out of the loop and return the value
            valid = true;
        }
        else
        {
            //something went wrong, we reset the buffer's state to good
            cin.clear();
            //and empty it
            cin.ignore(99999999, '\n');
            cout << "Invalid input; please re-enter: ";
        }
    } while (!valid);

    return (input);
}

void Helper::zoomConsoleScreen(int percent) {
    if (percent < 50 || percent > 200) {
        std::cerr << "Zoom percentage should be between 50% and 200%." << std::endl;
        return;
    }

    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get console handle." << std::endl;
        return;
    }

    // Retrieve the current font info
    CONSOLE_FONT_INFOEX fontInfo = { 0 };
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
        std::cerr << "Failed to retrieve current console font information." << std::endl;
        return;
    }

    // Adjust the font size based on the zoom percentage
    fontInfo.dwFontSize.X = static_cast<SHORT>(fontInfo.dwFontSize.X * percent / 100);
    fontInfo.dwFontSize.Y = static_cast<SHORT>(fontInfo.dwFontSize.Y * percent / 100);

    // Set the new font size
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
        std::cerr << "Failed to set console font size." << std::endl;
        return;
    }

    // Lock console resizing
    HWND hwndConsole = GetConsoleWindow();
    if (hwndConsole == NULL) {
        std::cerr << "Failed to get console window handle." << std::endl;
        return;
    }

    // Disable resizing by setting a fixed console size
    RECT rect;
    GetWindowRect(hwndConsole, &rect); // Get the current console window dimensions
    MoveWindow(hwndConsole, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);

    // Disable maximize button and resizing options
    LONG style = GetWindowLong(hwndConsole, GWL_STYLE);
    style &= ~WS_SIZEBOX;  // Disable resizing
    style &= ~WS_MAXIMIZEBOX;  // Disable maximize button
    SetWindowLong(hwndConsole, GWL_STYLE, style);

    // Disable Quick Edit mode and mouse-based zooming
    DWORD consoleMode;
    GetConsoleMode(hConsole, &consoleMode);
    consoleMode &= ~ENABLE_QUICK_EDIT_MODE; // Disable Quick Edit mode
    consoleMode &= ~ENABLE_MOUSE_INPUT;    // Disable mouse input to block Ctrl + Scroll
    SetConsoleMode(hConsole, consoleMode);
}


void Helper::printMiniInstagram() {
    vector<string> art = {
        "==============================================================================================================================",
        "      __  ___   ____   _   __   ____         ____   _   __   _____    ______   ___       ______   ____     ___       __  ___ ",
        "     /  |/  /  /  _/  / | / /  /  _/        /  _/  / | / /  / ___/   /_  __/  /   |     / ____/  / __ \\   /   |     /  |/  / ",
        "    / /|_/ /   / /   /  |/ /   / /          / /   /  |/ /   \\__ \\     / /    / /| |    / / __   / /_/ /  / /| |    / /|_/ /  ",
        "   / /  / /  _/ /   / /|  /  _/ /         _/ /   / /|  /   ___/ /    / /    / ___ |   / /_/ /  / _, _/  / ___ |   / /  / /   ",
        "  /_/  /_/  /___/  /_/ |_/  /___/        /___/  /_/ |_/   /____/    /_/    /_/  |_|   \\____/  /_/ |_|  /_/  |_|  /_/  /_/    ",
        "                                                                                                                          ",
        "==============================================================================================================================",
    };

    for (const auto& line : art) {
        cout << line << endl;
    }
}