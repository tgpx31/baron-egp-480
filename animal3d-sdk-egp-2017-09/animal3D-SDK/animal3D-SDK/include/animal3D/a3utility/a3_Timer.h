/*
	Copyright 2011-2017 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_Timer.h
	Multi-platform high-precision timer interface.

	**DO NOT MODIFY THIS FILE**
*/

#ifndef __ANIMAL3D_TIMER_H
#define __ANIMAL3D_TIMER_H


#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
	typedef struct a3_Timer	a3_Timer;
#endif	// __cplusplus

	
//-----------------------------------------------------------------------------

	// A3: Timer structure.
	//	member started: timer started/running flag
	//	member ticks: number of times timer has ticked
	//	member totalTime: total accumulation of time counter (updated on tick)
	//	member previousTick: last tick measurement (updated on tick)
	//	member currentTick: duration of the current tick (constantly updated)
	//	member ticksPerSecond: expected number of ticks per second
	//	member secondsPerTick: inverse ticks per second; expected time per tick
	struct a3_Timer
	{
		unsigned int started;
		unsigned int ticks;
		double totalTime;
		double previousTick;
		double currentTick;
		double ticksPerSecond;
		double secondsPerTick;

		// internal time values
		union {
			struct {
				long q[2];
				long long qs;
			};
			long long qu;
		} tf[1], t0[1], t1[1];
	};
	

//-----------------------------------------------------------------------------

	// A3: Begin counting time for the specified timer; if already running, 
	//		resets the current tick's start time.
	//	param timer: non-null pointer to timer object
	//	return: 1 if started timing
	//	return: -1 if invalid param
	int a3timerStart(a3_Timer *timer);

	// A3: Stop counting time for the specified timer; measures current tick.
	//	param timer: non-null pointer to timer object
	//	return: 1 if stopped timing
	//	return: -1 if invalid param
	int a3timerStop(a3_Timer *timer);

	// A3: Pause timer; does not measure current tick.
	//	param timer: non-null pointer to timer object
	//	return: 1 if paused
	//	return: -1 if invalid param
	int a3timerPause(a3_Timer *timer);

	// A3: Resume timer; does not measure current tick.
	//	param timer: non-null pointer to timer object
	//	return:	1 if resumed
	//	return: -1 if invalid param
	int a3timerResume(a3_Timer *timer);

	// A3: Reset timer object; also stops timing.
	//	param timer: non-null pointer to timer object
	//	return: 1 if timer reset
	//	return: -1 if invalid param
	int a3timerReset(a3_Timer *timer);

	// A3: Reset, and set tick rate of timer; also stops timing.
	//	param timer: non-null pointer to timer object
	//	param ticksPerSecond: tick rate of timer
	//		if > 0, timer ticks based on time interval
	//		if <= 0, timer ticks every update while running
	//	return: 1 if timer set
	//	return: -1 if invalid param
	int a3timerSet(a3_Timer *timer, double ticksPerSecond);

	// A3: Take time measurement.
	//	param timer: non-null pointer to timer object
	//	return: 1 if timer ticked (time since last tick exceeds 
	//		tick rate)
	//	return: 0 if timer did not tick
	//	return: -1 if invalid param
	int a3timerUpdate(a3_Timer *timer);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// __ANIMAL3D_TIMER_H