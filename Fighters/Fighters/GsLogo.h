#pragma once

#include "Define.h"

#include <DaramImage.h>
#include <DaramFrame.h>
#include <DaramDelay.h>
#include <DaramSound.h>

#include "Animation.h"

/////////////////////////////////////////////////
// Class  Name : GsLogo
// Description : �ΰ� ȭ�� �� ������ �ε� ȭ��
// W o r k e r : ������, ���翬
//  Work Date  : 2009/01/07
/////////////////////////////////////////////////
class GsLogo : public DaramFrame
{
private:
	// ���̵��� ��� üũ
	bool fadeIn;
	// ���̵�ƿ� ��� üũ
	bool fadeOut;
	// ���İ�(BYTE �ڷ�)
	unsigned char alpha;
	// ������ �˻� Ŭ����
	util::DaramDelay delay;

	// �ΰ� �̹���
	DaramImage logo;
	// ��� �̹���
	DaramImage levelIcon;
	// ���¼� �̹���
	DaramImage forceIcon;
	// ������ �ΰ� �ִϸ��̼�
	Animation logoAni;

	// �ΰ� ����
	DaramSound logoSound;

public:
	GsLogo() : DaramFrame(GS_LOGO) { }

	void Initial();
	void Update(double);
	void Draw();
	void Dispose();

};
