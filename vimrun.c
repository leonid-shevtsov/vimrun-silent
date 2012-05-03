#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
#include <wchar.h>

LPWSTR splitCommandLine(LPWSTR string) 
{
	LPWSTR	p = string;
    int inquote = 0;

    while (*p)
    {
		if (*p == '"') 
		{
			inquote = !inquote;
		}
		else if (!inquote && *p == ' ')
		{
			break;
		}
		++p;
    }

	*p = 0;
	return ++p;
}

int CALLBACK WinMain(
  __in  HINSTANCE hInstance,
  __in  HINSTANCE hPrevInstance,
  __in  LPSTR lpCmdLine,
  __in  int nCmdShow
)
{
    LPWSTR	command_line;
    int		retval;
    int		silent = 0;
	int inquote = 0;
	LPWSTR command, arguments, arguments_with_pause;
	SHELLEXECUTEINFOW sei;

	command_line = GetCommandLineW();
	command = splitCommandLine(command_line);

    /*
     * "-s" argument: don't wait for a key hit.
     */
    if (command[0] == '-' && command[1] == 's' && command[2] == ' ')
    {
	silent = 1;
	command += 3;
	while (*command == ' ')
	    ++command;
    }

	arguments = splitCommandLine(command);

	if (!silent) {
		arguments_with_pause = (LPWSTR)malloc(wcslen(arguments) + sizeof(wchar_t)*10);
		*arguments_with_pause = 0;
		wcscat(arguments_with_pause, arguments);
		wcscat(arguments_with_pause, L" && pause");
		arguments = arguments_with_pause;
	}

    /*
     * Do it!
     */
	ZeroMemory(&sei, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.nShow = silent ? SW_HIDE : SW_SHOW;
	sei.lpVerb = L"open";
	sei.lpFile = command;
	sei.lpParameters = arguments;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShellExecuteEx(&sei);
	
	// if the process has started, 
	if (sei.hProcess) {
		while (1) {
			GetExitCodeProcess(sei.hProcess, &retval);
			if (retval != STILL_ACTIVE) {
				return retval;
			}
			Sleep(100); // don't eat up too much cpu
		}
	} else {
		return -1;
	}
}
