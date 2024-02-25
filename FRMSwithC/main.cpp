#include "Head.h"
#include "Menu.h"

signed main() {
	Menu menu;
	menu.display(1);
	menu.read(1);
	menu.update();

	return 0;
}