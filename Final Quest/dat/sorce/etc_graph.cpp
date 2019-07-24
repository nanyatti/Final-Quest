#include "../../include/GV.h"

void fps_graph(){//FPS•`‰æ
	if(fps_average!=0)//0Š„‚è‹Ö~‚É‚æ‚èAFPS•½‹Ï‚ª0‚¶‚á‚È‚©‚Á‚½‚ç•`‰æ
		DrawFormatString(0,0,GetColor(255,255,255),"FPS %.1f",1000.0/(double)fps_average);
	return;
}