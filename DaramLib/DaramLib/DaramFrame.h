#pragma once

#include "DaramLibrary.h"

class DECLSPEC DaramFrame
{
private:
	int stateValue;

public:
	DaramFrame();
	DaramFrame(int statevalue);

	virtual void Initial() {  };
	virtual void Update(double ElapsedTime) {  };
	virtual void Draw() {  };
	virtual void Dispose() {  };

	bool operator==(DaramFrame frames);
	bool operator!=(DaramFrame frames);
	bool operator==(int statevalue);
	bool operator!=(int statevalue);
};
