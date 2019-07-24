#include "../../include/GV.h"

double rano(double sigma, double average){//average���ρAsigma�U��΂�x�����Ƃ��Đ��K���z����������Ԃ�
    static double r1, r2, s , r;
    static int valid = 0;
    double c;
    if(!valid)    {
        r1 = GetRand(RAND_MAX) / ((double)RAND_MAX+1);
        r2 = GetRand(RAND_MAX) / ((double)RAND_MAX+1);
        s = sqrt(-2.0 * log(1.0 - r2));
    }
    valid = !valid;
    c = 2.0 * PI * r1;
    r=valid? s * sin(c): s * cos(c);
    return r * sigma + average;
}

//�v�Z���͎d�l��12�Q��
int damdec(ch_t *c,int to,int actkind){//�_���[�W�v�Z�Bto =0(��������G��) 1(�G���猩����) 2(�������猩����) 3(�G����G�ւ̍U��)
	int lv,power,weapon,def,equip,strong;
	if(to==0){//�����́u�ʏ�U���v
		lv		=ch[0].lv;
		power	=ch[0].power	+ch[0].chsts.power;
		weapon	=ch[0].weapon	+ch[0].chsts.weapon;
		strong	=ch[0].strong	+ch[0].chsts.strong;
		def		=mon[0].def		+mon[0].chsts.def;
		equip	=mon[0].equip	+mon[0].chsts.equip;
		if(actkind/10000==2)
			power+=100*(actkind%10000)/100;
	}
	if(to==1){//�G�́u�ʏ�U���v
		lv		=mon[0].lv;
		power	=mon[0].power	+mon[0].chsts.power;
		weapon	=mon[0].weapon	+mon[0].chsts.weapon;
		strong	=mon[0].strong	+mon[0].chsts.strong;
		def		=ch[0].def		+ch[0].chsts.def;
		equip	=ch[0].equip	+ch[0].chsts.equip;
	}
	if(to==2){//�������猩���ւ̍U��
		lv		=ch[0].lv/2;
		power	=(ch[0].power	+ch[0].chsts.power)/2;
		weapon	=(ch[0].weapon	+ch[0].chsts.weapon)/2;
		strong	=(ch[0].strong	+ch[0].chsts.strong)/2;
		def		=(ch[0].def		+ch[0].chsts.def);
		equip	=(ch[0].equip	+ch[0].chsts.equip);
	}
	if(to==3){//�G����G�ւ̍U��
		lv		=mon[0].lv/2;
		power	=(mon[0].power	+mon[0].chsts.power)/2;
		weapon	=(mon[0].weapon	+mon[0].chsts.weapon)/2;
		strong	=(mon[0].strong	+mon[0].chsts.strong)/2;
		def		=(mon[0].def	+mon[0].chsts.def);
		equip	=(mon[0].equip	+mon[0].chsts.equip);
	}
	if(actkind<40000 && actkind!=20000){
		return (int)(lv*2+(power+weapon-(def+equip))*strong*rano(0.01,0.05)+strong*rano(0.2,1.0));
	}
	if(actkind==20000){//�L���A
		return (int)(c->magic*10.0*rano(0.2,1.0));
	}
	return -1;
}

void hp_sub(ch_t *c){//HP�̌������[�V�����B
	int spd;
	if(gameover_flag==1 || victory_flag==1)	return;

	if(c->hp==c->bttohp)	return;

	if(c->hp_max<300)	spd=1;
	else				spd=c->hp_max/300;

	if(c->bttohp<0)		c->bttohp=0;

	if(c->hp - spd >= c->bttohp)
		c->hp -= spd;
	if(c->hp - spd <= c->bttohp)
		c->hp=c->bttohp;

	return ;
}

int tp_calc(int dam,int hp){	//�_���[�W�Ƒ̗͍ő�l���TP������
	if(dam*100/hp<1)
		return 1;
	else
		return dam*100/hp;
}