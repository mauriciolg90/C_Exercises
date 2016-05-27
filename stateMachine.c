#include <stdio.h>
#include <ctype.h>  /* Provides isdigit() */
#include <stdlib.h> /* Provides atoi() */
#include <string.h> /* Provides strlen() */

/* Number of rows of the "transitionTable" matrix */
#define STATES_AMOUNT 5
/* Number of columns of the "transitionTable" matrix */
#define STIMULUS_AMOUNT 4

/* Enum that represents states */
enum State {
	Off,
	Stopped,
	Walking,
	Running,
	Error
};

/* Enum that represents stimulus */
enum Stimulus {
	TurnOn,
	TurnOff,
	SpeedUp,
	SpeedDown
};

/* Structure that contains the current state */
struct FSM {
	enum State currentState;
};

/* Arrays that store states and stimulus names as strings */
const char *stateNames[STATES_AMOUNT] = {"Off", "Stopped", "Walking", "Running", "Error"};
const char *stimulusNames[STIMULUS_AMOUNT] = {"TurnOn", "TurnOff", "SpeedUp", "SpeedDown"};

/* Matrix with the corresponding transitions */
const enum State transitionTable[STATES_AMOUNT][STIMULUS_AMOUNT] = {
	{Stopped, Off, Off, Off},
	{Stopped, Off, Walking, Error},
	{Walking, Off, Running, Stopped},
	{Running, Off, Error, Walking},
	{Error, Off, Error, Error}
};

/* Function prototype */
void stimulate(struct FSM* fsm, enum Stimulus stimulus);

int main(void)
{
	struct FSM fsm;
	char userInput[32];
	unsigned int i;
	int invalidInput;
	int finishProgram;
	int stimulusToSend;
	const int FINISH = 9;

	finishProgram = 0;
	fsm.currentState = Off;

	while(!finishProgram) {
		/* Verifies that user input only contains digits */
		do {
			invalidInput = 0;
			fgets(userInput, sizeof(userInput), stdin);
			/* The '-1' below is due to '\n' of the end */
			for(i = 0; i < strlen(userInput) - 1; ++i) {
				if(!isdigit(userInput[i])) {
					printf("The input is invalid!\n");
					invalidInput = 1;
					break;
				}
			}
		} while(invalidInput);

		/* Converts the user input into a integer */
		stimulusToSend = atoi(userInput);
		/* Verifies the output option */
		finishProgram = (stimulusToSend == FINISH);

		if(stimulusToSend < STIMULUS_AMOUNT) {
			stimulate(&fsm, stimulusToSend);
		}
		else if(finishProgram){
			printf("Program ended!\n");
		}
		else {
			printf("The stimulus does not exist!\n");
		}
	}

	return 0;
}

/** @brief Stimulates the machine and advances to the next state.
 *
 *  @param fsm Finite State Machine to stimulate.
 *  @param stimulus Stimulus to send to the machine.
 *  @return void Does not return any value.
 */
void stimulate(struct FSM *fsm, enum Stimulus stimulus)
{
	printf("[%s] ----- <%s>", stateNames[fsm->currentState], stimulusNames[stimulus]);
	fsm->currentState = transitionTable[fsm->currentState][stimulus];
	printf(" -----> [%s]\n", stateNames[fsm->currentState]);
}