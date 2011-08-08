/*
 * Clock.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: DVD
 */

#include "Clock.h"

List<ClockChangeListener> Clock::_hooks;

void Clock::TriggerAllEvents(ClockEventType type)
{
	Node<ClockChangeListener> * curr = _hooks.GetFirst();
	if(curr == NULL)
		return;
	do
	{
		if(curr->GetValue()->GetEventType() == type)
		{
			curr->GetValue()->GetEventFunction()();
		}
	}while((curr = _hooks.GetNext(curr)) != NULL);

}

void Clock::SetEventListener(ClockChangeListener listener)
{
	_hooks.AddFirst(&listener.GetNode());
}
