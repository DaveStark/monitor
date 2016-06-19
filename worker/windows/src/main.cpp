//============================================================================
// Name        : worker.cpp
// Author      : DaveMonsalve
// Version     :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>

void invertMouse();
void getcoords(int &x, int &y);
void blockMouseMove();
int main(int argc, char ** argv) {
	int i;
	for (i = 0; i < argc; i++) {
		std::cout << "Argument [" << i << "] = '" << argv[i] << "'"
				<< std::endl;
	}
	blockMouseMove();
	std::cout << "Hi !" << std::endl;
	return 0;
}

void blockMouseMove(){
	while(1){
		Sleep(100);
		SetCursorPos(400,400);
	}
}

void getcoords(int &x, int &y) {
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	x = cursorPos.x;
	y = cursorPos.y;
}

void invertMouse() {
	int x,y;
	int x2,y2;
	int dx,dy;


	int minx = 0;
	int miny = 0;


	SetCursorPos(9999,9999);
	int mx,my; //max x and max y on the particular screen
	getcoords(mx,my);


	while(true) {
		getcoords(x,y);
		Sleep(1);
		getcoords(x2,y2);


		//If the cursor is out of bounds
		if(x  == minx) {
			x = x+2;
		}
		if(x2 == minx) {
			x2 = x2+2;
		}
		if(y2 == miny) {
			y2 = y2+2;
		}
		if(y == miny) {
			y = y+2;
		}
		if( x  == mx) {
			x = x-2;
		}
		if(x2 == mx) {
			x2 = x2-2;
		}
		if(y2 == my) {
			y2 = y2-2;
		}
		if(y == my) {
			y = y-2;
		}

		SetCursorPos(x2,y2);

		dx = x2 - x;
		dy = y2 - y;

		SetCursorPos(x-dx,y-dy);
   }

/*	POINT prevPos, curPos;
int mouseSpeed = 10;
	GetCursorPos(&curPos);

	while (1) {
		Sleep(10);
		GetCursorPos(&prevPos);
		if (prevPos.x < curPos.x) {
			SetCursorPos(prevPos.x + mouseSpeed, prevPos.y);
			curPos.x = prevPos.x+mouseSpeed;
		}else if (prevPos.x > curPos.x) {
			SetCursorPos(prevPos.x - mouseSpeed, prevPos.y);
			curPos.x = prevPos.x-mouseSpeed;
		}


		if (prevPos.y < curPos.y) {
			SetCursorPos(prevPos.x, prevPos.y + mouseSpeed);
			curPos.y = prevPos.y+mouseSpeed;
		} else if (prevPos.y > curPos.y) {
			SetCursorPos(prevPos.x, prevPos.y - mouseSpeed);
			curPos.y = prevPos.y-mouseSpeed;
		}
	}*/
}
