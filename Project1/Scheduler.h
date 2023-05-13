// test
// another
// gg
#pragma once
#include"Process.h"
#include"UserInterface.h"
#include"ProcessQueues.h"
class Processor;


class Scheduler{
private:
	int timestep;
	
	int Processorsnum;

	Processor** pros;
	//
	int processnum;
	int BLKcount;
	int TRMcount;
	UserInterface Window;
	int fcfscount, sjfcount, rrcount, timeslice, rtf, maxW, stl;
	double forkprob;
	
	
	ProcessQueue NEWlist;
	ProcessQueue BLKlist;
	ProcessQueue TRMlist;
	LinkedQueue<Pairs> Sigkilllist;


public:
	int gettime()
	{
	
	return timestep;
	}

	int getblk()
	{
	
	return BLKcount;
	
	}
	int gettrm()
	{
	
	return TRMcount;
	
	}
	
	int getslice()
	{
	
	return timeslice;
	}

	int getSTL()
	{
		return stl;
	}

	int getprocessnum()
	{
	
	return processnum;
	}
	void counterup()
	{
	
	timestep++;
	}

	int checkAvailability(ProcessorType type);
	void Assign();
	void Assign(Process*);
	bool migrate(Process*, ProcessorType T);
	void workSteal();
	void shedule();
	void printpros();
	void addtoBLK(Process*);
	void addtoTRM(Process*);
	bool removeBLK(Process*&);
	void Load();
	Scheduler();
	//Start of Forking Functions:
	bool TestingProbability(double Probability);
	bool CanForkChild(Process* Process);
	void forkChild(Process* Process);
	Processor* findShortestRdyList();

	void IOHandling(Process*);
	void CheckBlock();
};

