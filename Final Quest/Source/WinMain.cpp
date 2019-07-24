#include <Windows.h>
#include "SystemMain.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance, LPSTR command_line, int show_method) {

	SystemMain system;
	if (system.Initialize()) {
		system.Main();
	}
	system.Finalize();
}