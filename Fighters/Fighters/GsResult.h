#pragma once

#include "Define.h"
#include <DaramImage.h>
#include <DaramFrame.h>

/////////////////////////////////////////////////
// Class  Name : GsResult
// Description : ���� ��� ȭ��
// W o r k e r : 
//  Work Date  : 
/////////////////////////////////////////////////
class GsResult : public DaramFrame
{
public:

	bool Check1pWin ;
	DaramImage End[2] ;
	GsResult() : DaramFrame(GS_RESULT) { }

	void Initial();
	void Update(double);
	void Draw();
	void Dispose();

};
