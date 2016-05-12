#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
	int option;
	struct FSM *fsm;

	fsm = malloc(sizeof(struct FSM));
	fsm->currentState = Off;

	do {
		scanf("%d", &option);
		switch(option) {
			case 0: 
			case 1:
			case 2:
			case 3:
				stimulate(fsm, option);
				break;
			default:
				printf("The stimulus does not exist!\n");
				break;
		}
	} while(option != 9);

	return 0;
}

/** @brief Stimulates the machine and advances to the next state.
 *
 *  @param fsm Finite State Machine to stimulate.
 *  @param stimulus Stimulus to send to the machine.
 *  @return void Does not return any value.
 */
void stimulate(struct FSM *fsm, enum Stimulus stimulus) {
	printf("[%s] ----- <%s>", stateNames[fsm->currentState], stimulusNames[stimulus]);
	fsm->currentState = transitionTable[fsm->currentState][stimulus];
	printf(" -----> [%s]\n", stateNames[fsm->currentState]);
}