
#include "../../include/GV.h"

void boad_string_calc(){//���ڂ̐�����\�����邽�߂ɕ�������i�[����֐�
	if(ch[0].btcnt==240 && ch[0].menu_sel<10000){
		switch(ch[0].menu_sel){
			case 1:
				strcpy(board_string,"�U�����s���܂��B");
				break;
			case 2:
				strcpy(board_string,"���@�U�����s���܂��B");
				break;
			case 3:
				strcpy(board_string,"�A�r���e�B���g�p���܂��B");
				break;
			case 4:
				strcpy(board_string,"�A�C�e�����g�p���܂��B");
				break;
			case 5:
				strcpy(board_string,"�퓬���瓦���܂��B");
				break;
			case 100:
				strcpy(board_string,"�ʏ�U�����s���܂��B");
				break;
			case 101:
				strcpy(board_string,"TP���g�p���ē���U�����s���܂��B");
				break;
			case 200:
				strcpy(board_string,"MP9����ĉ񕜖��@���s���܂��B");
				break;
			case 201:
				strcpy(board_string,"MP8����ĕ��̖��@�U�����s���܂��B");
				break;
			case 202:
				strcpy(board_string,"MP16����ĉ΂̖��@�U�����s���܂��B");
				break;
			case 203:
				strcpy(board_string,"MP24����ĕX�̖��@�U�����s���܂��B");
				break;
			case 204:
				strcpy(board_string,"MP36����ė��̖��@�U�����s���܂��B");
				break;
			case 300:
				strcpy(board_string,"�������đ���������Ɉ����t���܂��B(30�b��Ďg�p��)");
				break;
			case 301:
				strcpy(board_string,"2���ԍU���͂������Ėh��͂��グ�܂��B(2����Ďg�p��)");
				break;
			case 302:
				strcpy(board_string,"2���ԍU���͂��グ�Ėh��͂������܂��B(2����Ďg�p��)");
				break;
			case 303:
				strcpy(board_string,"�����̗̑͂�����ēG��2�{�̃_���[�W��^���܂��B(30�b��Ďg�p��)");
				break;
			case 304:
				strcpy(board_string,"MP��2�{����ĉr�����Ԃ�1/4�ɂ��܂��B(30�b��Ďg�p��)");
				break;
			case 400:
				strcpy(board_string,"HP�������񕜂��܂��B");
				break;
			case 401:
				strcpy(board_string,"HP�������񕜂��܂��B");
				break;
			case 402:
				strcpy(board_string,"�U���͂��������܂��B");
				break;
			case 403:
				strcpy(board_string,"�h��͂��������܂��B");
				break;
			case 404:
				strcpy(board_string,"MP�������񕜂��܂��B");
				break;
			case 500:
				strcpy(board_string,"�퓬���瓦���܂��B");
				break;
			case 501:
				strcpy(board_string,"�}�l�[�𗎂Ƃ��č��m���Ő퓬���瓦���܂��B");
				break;
			default:
				strcpy(board_string,"");
				break;
		}
	}
	else
		strcpy(board_string,"");
	return ;
}