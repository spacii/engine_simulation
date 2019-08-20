#pragma once

class Engine {
public:
	virtual void StartEngine() = 0;
	virtual void StopEngine() = 0;
	virtual ~Engine() = 0 {};
	virtual bool isWorking() = 0;
	virtual void setWorking(bool working) = 0;
	virtual int getT_Engine() = 0;
	virtual int getT_Overheat() = 0;
	virtual int getTimeInWork() = 0;
	
protected:
	bool working = false;
};