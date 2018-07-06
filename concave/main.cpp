#include "5_mok.h"

ground *back_ground;
int main() {

	back_ground = (ground*)malloc(sizeof(ground));
	Initialization(back_ground);
	Drawing_board();
	Moving_cursor();

	Game_finish();
}
