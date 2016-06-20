//============================================================================
// Name        : worker.cpp
// Author      : DaveMonsalve
// Version     :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>
#include <string.h>

#define MAX_THREADS 10

void invertMouseThread();
void blockMouseMoveThread();
void closeThreads();
DWORD WINAPI blockMouseMove(LPVOID lpParameter);
DWORD WINAPI invertMouse(LPVOID lpParameter);
void getcoords(int &x, int &y);
HANDLE hThreadArray[MAX_THREADS];
DWORD dwThreadIdArray[MAX_THREADS];
int threadIndex;
void processArguments(int argc, char ** argv);
char ask[512];
bool bExit;
//https://msdn.microsoft.com/en-us/library/windows/desktop/ms682516(v=vs.85).aspx

int main(int argc, char ** argv) {
	bExit = false;
	threadIndex = 0;
	processArguments(argc, argv);
	do{
		std::cout<<"ask for: ";
		std::cin.getline(ask,512);
		bExit = (strcmp(ask,"q")==0);
	}while(!bExit);

	WaitForMultipleObjects(threadIndex, hThreadArray, TRUE, INFINITE);
	// Close all thread handles and free memory allocations.
	closeThreads();
	std::cout<<"end"<<std::endl;

	return 0;
}

void processArguments(int argc, char ** argv){
	if(argc > 1){
		if(strcmp(argv[1],"invert") == 0){
			invertMouseThread();
		}else if(strcmp(argv[1],"block") == 0){
			blockMouseMoveThread();
		}
	}
	//only for debug
	/*int i;
	for (i = 0; i < argc; i++) {
		std::cout << "Argument [" << i << "] = '" << argv[i] << "'" << std::endl;
	}*/
}

void closeThreads() {
	for (int i = 0; i < threadIndex; i++) {
		CloseHandle(hThreadArray[i]);
	}
}

void invertMouseThread() {
	hThreadArray[threadIndex] = CreateThread(0,   // default security attributes
			0,                      // use default stack size
			invertMouse,       // thread function name
			0, //pDataArray[threadIndex],          // argument to thread function
			0,                      // use default creation flags
			&dwThreadIdArray[threadIndex]);   // returns the thread identifier
	threadIndex++;
}

void blockMouseMoveThread() {
	hThreadArray[threadIndex] = CreateThread(0,   // default security attributes
			0,                      // use default stack size
			blockMouseMove,       // thread function name
			0, //pDataArray[threadIndex],          // argument to thread function
			0,                      // use default creation flags
			&dwThreadIdArray[threadIndex]);   // returns the thread identifier
	threadIndex++;
}

DWORD WINAPI blockMouseMove(LPVOID lpParameter) {
	while (!bExit) {
		Sleep(100);
		SetCursorPos(400, 400);
	}
}

void getcoords(int &x, int &y) {
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	x = cursorPos.x;
	y = cursorPos.y;
}

DWORD WINAPI invertMouse(LPVOID lpParameter) {
	int x, y;
	int x2, y2;
	int dx, dy;

	int minx = 0;
	int miny = 0;

	SetCursorPos(9999, 9999);
	int mx, my; //max x and max y on the particular screen
	getcoords(mx, my);

	while (!bExit) {
		getcoords(x, y);
		Sleep(1);
		getcoords(x2, y2);

		//If the cursor is out of bounds
		if (x == minx) {
			x = x + 2;
		}
		if (x2 == minx) {
			x2 = x2 + 2;
		}
		if (y2 == miny) {
			y2 = y2 + 2;
		}
		if (y == miny) {
			y = y + 2;
		}
		if (x == mx) {
			x = x - 2;
		}
		if (x2 == mx) {
			x2 = x2 - 2;
		}
		if (y2 == my) {
			y2 = y2 - 2;
		}
		if (y == my) {
			y = y - 2;
		}

		SetCursorPos(x2, y2);

		dx = x2 - x;
		dy = y2 - y;

		SetCursorPos(x - dx, y - dy);
	}
	return 0;
	//https://www.daniweb.com/programming/software-development/threads/111952/how-do-you-invert-the-mouse-control-
}
