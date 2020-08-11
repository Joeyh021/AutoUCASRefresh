#include <stdio.h>
#include <string.h>
#include <windows.h>

// constants
#define KEY 0x74     // keycode to press
#define DELAY 10000  // delay between keypresses in ms

// take partially built struct and keydown then keyup the key passed
void keypress(INPUT* inp, int keycode) {
    INPUT* inparr = inp;                        // declare the array of 2  structs to be passed to SendInput
    inparr[0].ki.wVk = keycode;                 // set the keycode as passed
    memcpy(inparr + 1, inparr, sizeof(INPUT));  // duplicate the struct into both items of the array
    inparr[0].ki.dwFlags = 0;
    inparr[1].ki.dwFlags = KEYEVENTF_KEYUP;  // set the keydown and then keyup in first and second structs, respectively
    SendInput(2, inparr, sizeof(INPUT));     // let the system have it :)
}

int main(void) {
    INPUT inp;                  // declare an INPUT structure from the win API
    inp.type = INPUT_KEYBOARD;  // declare what type the input is

    inp.ki.wScan = inp.ki.time = inp.ki.dwExtraInfo = 0;  // set a bunch of system flags in the struct to zero
    while(1) {
        Sleep(DELAY);  // time between keypresses in ms

        keypress(&inp, KEY);
        printf("pressing key 0x%x\n", KEY);
    }
    return 0;
}
