#pragma once
#include"Processor.h"
#include"Scheduler.h"
#include"Process.h"
#include"defs.h"
#include"SJFQueue.h"
class SJFprocessor:public Processor
{
private:
	SJQueue rdylist;
public:
SJFprocessor(Scheduler* sh):Processor(sh)
{
	setType(SJF);
}

void addprocess(Process* p)
{
	if(p!=nullptr)
	{
	rdylist.enqueue(p);

	rdylist.totalreqtime+=p->getCpuTime()-p->getexcuted();

	readynum++;
	}
}

void peek(Process* p)
{
	rdylist.peek(p);
}

void printRdyList()
{
	rdylist.print();
}


 void ScheduleAlgo()
{
	
	
	if(Running!=nullptr)
	{
		Running->incrementexcuted();
		if(Running->getexcuted()==Running->getCpuTime())
		{
			Running->setTermination(psh->gettime());
			psh->addtoTRM(Running);
			Running=nullptr;
		}
		else if(Running->needio()!=-1)
		{
			psh->IOHandling(Running);
			Running = nullptr;
		}
	}




	Process*p;
	if(Running==nullptr)
	{
		if(!rdylist.isEmpty())
		{
			rdylist.peek(p);
			if(p!=nullptr)
			{
	p=dequeueprocess();
	Running=p;
	
	
			}
		}
	
	}

	




};

 int  gettotalreq()
 {
 
 return rdylist.totalreqtime;
 
 }

Process* dequeueprocess()
{
	Process*p;
	rdylist.dequeue(p);
	rdylist.totalreqtime-=p->getCpuTime()-p->getexcuted();
	readynum--;
	return p;
}


};