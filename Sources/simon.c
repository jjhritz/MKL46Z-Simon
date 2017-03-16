//************************************************************************************************************
// FILE: simon.c
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "simon.h"
#include "led.h"
#include "pushb.h"
#include "rand.h"
#include "global.h"
#include "tpm.h"

uint32_t sequence[50];
uint32_t turn_complete;
uint32_t wait = 1000; //delay between LED on/off (in ms)
uint32_t turn;
uint32_t led_logic = LED_LOGIC_NEG; //Logic configuration for LEDs

//Generates sequence of 50 random values from [0,3], 
//corresponding to the LEDs on the board
void sequence_gen()
{
	for(uint32_t i = 0; i < 50; i++)
	{
		sequence[i] = rand_between(0, 3); //generate random number from [0,3]
	}
}

//Starts a new game by turning off all LEDs, resetting all values, and
//generating a new sequence
void reset_game()
{
	led_all_off(led_logic, 4); 	//turn all LEDs off
	turn_complete = 1;			//Reset success flag
	turn = 1;					//Reset to turn 1
	rand_init();				//Get new random seed					
	sequence_gen();				//Generate new sequence
}

//If a player succeeds in a turn, flash all LEDs in unison twice
void succeed()
{
	turn_complete = 1;
	
	for(uint32_t i = 0; i < 2; i++)
	{
		//turn on all LEDs
		led_all_on(led_logic, 4);
		//wait
		tpm_busy_delay_ms(250);
		//turn all LEDs off
		led_all_off(led_logic, 4);
		//wait
		tpm_busy_delay_ms(250);
	}
}

//Flashes the number of lights from the sequence equal to the current turn number
void flash_phase(uint32_t turn)
{
	turn_backup = turn;
	i_backup = 0;
	for(uint32_t i = 0; i < turn; i++)
	{
		//turn on LED that corresponds to the value in the sequence
		led_on(led_logic, sequence[i]);
		//wait
		tpm_busy_delay_ms(wait);
		//turn LEDs off
		led_all_off(led_logic, 4);
		//wait
		tpm_busy_delay_ms(wait);
		
	}
}

//If a player fails a turn, set success flag to 0 and repeat sequence
void failure()
{
	flash_phase(turn);
	turn_complete = 0;
}

//Listens for player response and compares it to the sequence
void response_phase(uint32_t turn)
{
	uint32_t i = 0;
	uint32_t correct = 1;
	while(correct == 1 && i < turn)
	{
		//wait for user input
		while((PUSHB1_STATE != 0) && 
				(PUSHB2_STATE != 0) &&
				(PUSHB3_STATE != 0) &&
				(PUSHB4_STATE != 0))
		{/*do nothing*/}
		
		if(PUSHB1_STATE == 0)
		{
			led_on(led_logic, 0);
			//wait
			tpm_busy_delay_ms(wait);
			//turn LEDs off
			led_all_off(led_logic, 4);
			//wait
			tpm_busy_delay_ms(wait);			
			
			
			if(sequence[i] == 0)
			{
				correct = 1;
			}
			
			else
			{
				correct = 0;
			}
		}
		else if(PUSHB2_STATE == 0)
		{
			led_on(led_logic, 1);
			//wait
			tpm_busy_delay_ms(wait);
			//turn LEDs off
			led_all_off(led_logic, 4);
			//wait
			tpm_busy_delay_ms(wait);
			
			if(sequence[i] == 1)
			{
				correct = 1;
			}
			else
			{
				correct = 0;
			}			
		}
		else if(PUSHB3_STATE == 0)
		{
			led_on(led_logic, 2);
			//wait
			tpm_busy_delay_ms(wait);
			//turn LEDs off
			led_all_off(led_logic, 4);
			//wait
			tpm_busy_delay_ms(wait);
			
			if(sequence[i] == 2)
			{
				correct = 1;
			}
			
			else
			{
				correct = 0;
			}					
		}
		else if(PUSHB4_STATE == 0)
		{
			led_on(led_logic, 3);
			//wait
			tpm_busy_delay_ms(wait);
			//turn LEDs off
			led_all_off(led_logic, 4);
			//wait
			tpm_busy_delay_ms(wait);
			
			if(sequence[i] == 3)
			{
				correct = 1;
			}
			
			else
			{
				correct = 0;
			}					
		}
		
		i++;
	}
	
	if(correct == 1)
	{
		succeed();
	}
	else
	{
		failure();
	}
}


void simon_play()
{
	while(1)
	{
		//Turn off all LEDs
		reset_game();
		
		//Game starts at turn 1
		
		while(turn_complete == 1 && (turn - 1) < 50)
		{
			//Flash sequence
			flash_phase(turn);
			
			//wait for response
			response_phase(turn);
			
			//If correct, next turn	
			turn++;
			
			//Else, repeat sequence, reset
		}
	}
}
