#pragma once 
#include<iostream>
#include"defs.h"
#include "Pairs.h"
#include "LinkedQueue.h"
using namespace std;








class Process{
private:
int PID;
int ArrivalTime;
int CpuTime;
int totalexcuted;
int IOneeded;
int IOcount;

LinkedQueue<Pairs> IOprocess;
//very important! Node* IOlist;
//Node*child; bool isparent;

bool forked;
bool forkedBefore;
int TerminationTime;
int FirstResponse;
int TRT;
int WT; 

/**/
ProcessState State;

friend ostream& operator<<(ostream&, Process*);

public:
	Process(){};
	Process(int ID,int arrival,int runtime,int IOnum=0)
	{
		PID=ID;
		ArrivalTime=arrival;
		CpuTime=runtime;
		IOcount=IOnum;
		totalexcuted = 0;
		forked = false;
		FirstResponse = -1;
		TerminationTime = -1;
		TRT = -1;
		WT = -1;
		forkedBefore = false;
	}
	int getID()
	{
		return PID;
	}

	int getArrivalTime()
	{
		return ArrivalTime;
	}


	int getCpuTime()
	{
		return CpuTime;
	}


	int getIOcount()
	{
		return IOcount;
	}

	int getIOneeded()
	{
		return IOneeded;
	}

	bool getForked()
	{
		return forked;
	}

	int getTermination()
	{
		return TerminationTime;
	}
	ProcessState getProcessState()
	{
		return State;
	}

	bool setAsForked()
	{
		forked = true;
	}

	void setIOneeded(int x)
	{
		IOneeded = x;
	}

	void setTermination(int t)
	{
		TerminationTime = t;
		TRT = t - ArrivalTime;
		WT = TRT - CpuTime;
	}

	void setFirstResponse(int t)
	{
		FirstResponse = t;
	}

	void incrementexcuted()
	{
		totalexcuted++;
	}

	int getexcuted()
	{
		return totalexcuted;
	}

	void setPair(int f, int s)
	{
		IOprocess.enqueue(Pairs(f, s));
	}

	int getRemainingTime()
	{
		return CpuTime - totalexcuted;
	}

	int needio()
	{
		if (!IOprocess.isEmpty())
		{
			Pairs p;
			IOprocess.peek(p);

			if (totalexcuted == p.getfirst())
			{
				IOprocess.dequeue(p);
				return p.getsecond();
			}
		}

		return -1;
	}
	bool getForkedBefore()
	{
		return forkedBefore;
	}

	void setForkedBefore()
	{
		forkedBefore = true;
	}

	
	~Process(void)
	{
	}


};

 