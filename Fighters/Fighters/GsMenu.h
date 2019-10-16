#pragma once

#include <DaramFrame.h>
#include <DaramImage.h>
#include <DaramSound.h>
#include "Define.h"
#include "ImageFont.h"

#include <DaramDelay.h>
using namespace util;

#include "Animation.h"

/////////////////////////////////////////////////
// Class  Name : GsMenu
// Description : ���� ���� �޴� ȭ��
// W o r k e r : ������, ���翬
//  Work Date  : 2009/01/13
/////////////////////////////////////////////////
class GsMenu : public DaramFrame
{
private:
	DaramImage bead;						// ��� ���� �̹���
	DaramImage menuSelectImage[4] ;			// ���� �޴� ���� �̹���(�۾�)
	DaramImage subMenuSelectImage[3] ;		// ���� �޴� ���� �̹���(�۾�)
	DaramImage optionImage[3] ;			// �ɼ� �̹��� ( ĥ���� 0 ���ڴ� 1���� 10�� 0 )
											// 11�� percent 12�� cursor 
	DaramImage createrImage[3];

	ImageFont numberFont;

	int menuAlpha ;							// �޴� ���� �̹��� ���İ�
	int prevMenuState, nextMenuState ;		// ����/���� �޴� ���� �̹���

	MenuState menuState ;					// ���� �޴� ����
	bool menuAlphaCheck ;					// ���� �޴� ���� �̹��� ���İ� ���� ���� üũ
	bool menuSelectCheck ;					// ���� �޴��� Ȱ��ȭ �ߴ��� üũ

	SubMenuState subMenuState ;				// ���� �޴� ����
	bool subMenuAlphaCheck ;				// ���� �޴� ���� �̹��� ���İ� ���� ���� üũ

	int createrCount ;						// Creater � ������ ����ϴ°� 0 ��ȹ 1���� 2�׷���
	bool createrDirectionCheck ;			// ��������� ���ϰ� �ִ°�? false - 0->2
	bool createrFadein ;					// fadein�����ΰ�
	DaramDelay createrDelay ;				// 

	int opState ;							// �ɼ� ����
	int opLinePosY ;						// �ɼ� ���� Y��ǥ 
	bool opSelectCheck ;					// �ɼ� ���� Ȱ��ȭ �ߴ��� üũ
	int opSelectState ;						// �ɼ� ���� ���λ��� ����
	int opMenu[5] ;							// �ɼ� �޴� �� 0-Hp , 1-Timer 2-Volume 3-Round 4-Key
	int opMenuSize[5] ;						// 
	int opPlusCoor[5] ;						// 
	int opComCoor[5] ;						//
	bool nowKeyChange1p ;					// ���� 1�� Ű�� �ٲٴ°�?? 1�Ǹ� T 2�Ǹ� F
	char save1PKey[7][2] ;					// 1�� Ű ���� ����
	char save2PKey[7][2] ;					// 2�� Ű ���� ����
	bool keyChangeCheck ;					// Ű�� �ٲٴ� ���·� ���°�??

	bool fadeIn;						// ���̵����� ����
	bool fadeOut;						// ���̵�ƿ��� ����
	unsigned char alpha;				// ���̵� ����

	DaramSound menuSelect;				// ȭ��ǥ�� �̿��Ͽ� � �޴��� ����� �� ���� ���
	DaramSound menuChoose;				// �����̽��ٸ� �̿��Ͽ� �޴��� ����� �� ���

	DaramSound menuTitle;				// Ÿ��Ʋ ȭ�� �������

public:
	GsMenu() : DaramFrame(GS_MENU) { }

	void Initial();
	void Update(double);
	void Draw();
	void Dispose();
	void ImageLoad();

};
