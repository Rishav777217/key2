#ifndef TIMER_H
#define TIMER_H

#include<thread>
#include<chrono>

class Timer
{
   std::thread THREAD;
   bool alive = false;
   long callNum = -1L, repCount = -1L;
   std::chrono::milliseconds interval = std::chrono::milliseconds(0);
   std::function<void(void)> funct = nullptr;

   void sleepAndRun()
   {
       std::this_thread::sleep_for(interval);
       if(alive)
            Function()();
   }
   void threadFunct()
   {
       if(callNum==Infinite)
            while(alive)
                sleepAndRun();
       else
            while(repCount--)
                sleepAndRun();
   }

   public:
       static const long Infinite = -1L;

       Timer() {}
       Timer(const std::function<void(void)> &f) : funct(f){}
       Timer(const std::function<void(void)> &f,const unsigned long &i,const long repeat = Timer::Infinite):funct(f),interval(std::chrono::milliseconds(i)),callNum(repeat) {}
       void start(bool Async=true)
       {
           if(IsAlive())
                return;
           alive=true;
           repCount=callNum;
           if(Async)
                THREAD=std::thread(threadFunct,this);
            else
                this->threadFunct();
       }
       void stop()
       {
           alive = false;
           THREAD.join();
       }
       const bool IsAlive() {return alive;}
       void RepeatCount(const long r)
       {
           if(alive)
                return;
           callNum=r;
       }
       void setFunct(const std::function<void(void)> &f)
       {
           funct=f;
       }
       const long getLeftCount() {return repCount;}
       const long RepeatCount() {return callNum;}
       void SetInterval(const unsigned long &i)
       {
           if(alive)
                return;
           interval=std::chrono::milliseconds(i);
       }
       const unsigned long Interval() {return interval.count();}
       const std::function<void(void)> &Function() const
       {
           return funct;
       }
};

#endif // TIMER_H
