#pragma once
#include"Processor.h"
#include"Scheduler.h"
#include"Process.h"
#include"defs.h"
#include"ProcessLinkedlist.h"
class FCFSprocessor:public Processor
{
private:
	ProcessLinkedlist rdylist;
	ProcessLinkedlist temp;
public:
FCFSprocessor(Scheduler* sh):Processor(sh)
{
	setType(FCFS);
}

void addprocess(Process* p)
{
	if(p!=nullptr)
	{
	rdylist.insertlast(p);
	rdylist.totalreqtime += (p->getCpuTime()) - (p->getexcuted());
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

 bool removebyid(int id, Process*& p)
 {
	 bool a = rdylist.removeid(id, p);
	 if (a)
	 {
		 readynum--;
		 return true;
	 }
	 return false;
 }

 void ScheduleAlgo()
{
	 //
	if(Running!=nullptr)
	{
		if (psh->migrate(Running, FCFS))
		{
			Running = nullptr;
		}
		else 
		{
			Running->incrementexcuted();
			if (Running->getexcuted() == Running->getCpuTime())
			{
				psh->Completed(Running);

			}
			else if (Running->needio(neededio) != -1)
			{
				psh->IOHandling(Running, neededio);

			}
		}
	}

	Process*p;
	if(Running==nullptr)
	{
		if(!rdylist.isEmpty())
		{
			rdylist.peek(p);
			if( p != nullptr)
			{
				p = dequeueprocess();

				if (!psh->migrate(p, FCFS))
					Running = p;
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
	rdylist.removefirst(p);
	rdylist.totalreqtime -= p->getCpuTime() - p->getexcuted();
	readynum--;
	return p;
 
 }

 /*bool FindProcessByPID(int id)
 {
	 if (Running->getID() == id)
		 return Running;
	 while(rdylist.isEmpty()!=false)
	 {

	 }
 }*/

 void storeForked(Process* p)
 {
	 Process* q;

	 this->dequeueprocess();
	 temp.insertlast(p);
	 this->peek(q);
	 if (q && q->getForked())
		 storeForked(q);
 }

 void restoreForked()
 {
	 Process* p = this->dequeueprocess();
	 while (p)
	 {
		 temp.insertlast(p);
		 p = this->dequeueprocess();
	 }

	 while (!temp.isEmpty())
	 {
		 temp.removefirst(p);
		 this->addprocess(p);
	 }
 }


};