//  Program Description/Support  ///////////////////////////////////////////////
/**
@file Timer.cpp
@author Ashlee Ladouceur
@version 1.0
@brief This file contains the Timer class function implementations. The timer
can be started, stopped, and return the elapsed time.
@date Sunday, December 3rd, 2017
*/

/**
@mainpage
This class will calculate elapsed time using the time of day (real time).

The start function stores the current time of day. The stop function
also stores the current time of day but can only be called after the timer has
been started. If the timer has been started and stopped, the getElapsedTime
function can be called to calculate the difference between the times and return
the result in seconds.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/

//  Header Files  //////////////////////////////////////////////////////////////
#include "Timer.h"
using namespace std;

//  Function Implementation  ///////////////////////////////////////////////////

/**
 * This function will initialize timerWasStarted and timerWasStopped to false.
 *
 */
Timer::Timer()
{
   timerWasStarted= false;
   timerWasStopped= false;
}

/**
 * This function will store the current time of day in beginTime.
 *
 * This function will use the gettimeofday function to store the current time
 * of day in beginTime. If gettimeofday returned a number other than 0, an error
 * is thrown.
 *
 * @return This function will return the number of adjacent pumpkins,
 * recursively resulting the size of a patch.
 * @exception If gettimeofday returns number other than 0, throw error.
 *
 * @post Time of day will be stored and timerWasStarted will be set to true.
 *
 */
void Timer::start() throw (runtime_error)
{
   int errorCheck= gettimeofday(&beginTime, NULL);
   if(errorCheck == 0) timerWasStarted= true;
   else throw runtime_error("start() failed to get time of day");
}

/**
 * This function will store the current time of day in endTime.
 *
 * This function will use the gettimeofday function to store the current time
 * of day in endTime. If the timer hasnt been started, an error
 * is thrown.
 *
 * @exception If the timer was not started, throw error.
 *
 * @pre Timer will have been started
 * @post Time of day will be stored and timerWasStopped will be set to true.
 *
 */
void Timer::stop() throw (logic_error)
{
   if(timerWasStarted)
   {
      int errorCheck= gettimeofday(&endTime, NULL);
      timerWasStopped= true;
   }
   else
   {
      throw logic_error("stop() while timer not started");
   }
}

/**
 * This function will calculate the difference between beginTime and endTime
 * and return the result in seconds.
 *
 * This function will calculate the beginTime and endTime in seconds, then find
 * the difference between them and return it. If the timer was not started and
 * stopped, an error is thrown.
 *
 * @return This function will return the elapsed time.
 * @exception If the timer was not started and stopped, throw error.
 *
 * @pre Timer will have been started and stopped.
 *
 */
double Timer::getElapsedTime() const throw (logic_error)
{
   double startTime= 0, stopTime= 0, elapsedTime= 0;

   if(timerWasStarted && timerWasStopped)
   {
      startTime= beginTime.tv_sec + beginTime.tv_usec / 1000000.0;
      stopTime= endTime.tv_sec + endTime.tv_usec / 1000000.0;
      elapsedTime= stopTime - startTime;
   }

   else
   {
      throw logic_error("getElapsedTime() while timer not started and stopped");
   }

   return elapsedTime;
}
