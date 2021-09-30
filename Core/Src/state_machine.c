/*
 * state_machine.c
 *
 *  Created on: 24 Aug 2021
 *      Author: nigil
 *
 */
#include "statemachine.h"
#include "main.h"


void set_state(StateMachine *me,event_typedef event)
{
	switch(me->event)
		{
			case PA0:
				if(me->state==DEFAULT)
				{
					//ignore event
				}
				else if (me->state==ON)
				{
					//ignore event
				}
				else
				{
					me->previous_state=me->state;
					me->state=ON;
				}
				break;
			case PC13:
				if(me->state==OFF)
				{
					//ignore event
				}
				else if (me->state   ==ON)
				{
					me->previous_state=me->state;
					me->state=OFF;
				}
				else
				{
					//ignore event
				}
				break;
			case START:
			{
				//waiting for button press
				me->previous_state=me->state;
				me->state=DEFAULT;
			}
			break;
		}

}

state_typedef  get_state(StateMachine *ptr_inst) 	//return a state enum not an int
{
	return ptr_inst->state;
}


void initstatemachine(StateMachine *ptr_inst)
{

	ptr_inst->ptr_get_state = get_state;
	ptr_inst->ptr_set_state = set_state;
	ptr_inst->state=2;
	ptr_inst->event=2;
	return;
}

void event_handler(StateMachine *me, Event_Queue *buffer){

	me->event=Pop_Event_From_Buffer(buffer);  //set last event into active object
	set_state(me,me->event);				 //Switch states accordingly
	return;

}
void init_buffer(Event_Queue *me,int size_of_buffer){
	me->size_of_buffer= size_of_buffer;
	me->event_buffer = (event_typedef*)calloc(me->size_of_buffer , sizeof(event_typedef));
	me->current_buffer_length=0;
	me->read_index=0;
	me->write_index=0;
	me->event_buffer[me->write_index]=START;

	me->ptr_Pop_Event_From_Buffer=Pop_Event_From_Buffer;
	me->ptr_Add_Event_To_Buffer=Add_Event_To_Buffer;
	return;

}

void Add_Event_To_Buffer(Event_Queue *me, event_typedef event)
{
	if(me->current_buffer_length == me->size_of_buffer){

		//Do nothing

	}
	else{
		me->event_buffer[me->write_index]= event; //Adding state invoke to buffer
		me->current_buffer_length++;
		me->write_index++;

	}
	return ;
}


//event_typedef last_event=START;
event_typedef Pop_Event_From_Buffer(Event_Queue *me)
{

	if( me->current_buffer_length ==0){
		//return last_event; //No event to process
	}
	else{

		event_typedef e;
		e= me->event_buffer[me->read_index];
		//last_event=e;
		me->current_buffer_length--;
		me->read_index++;
		if(me->read_index==me->size_of_buffer)
		{
			me->read_index=0;
		}
	return e ; //Return the event
	}
}


