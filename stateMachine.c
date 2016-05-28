#include <stdio.h>
#include <ctype.h>  /* Provides isdigit() */
#include <stdlib.h> /* Provides atoi() */
#include <string.h> /* Provides strlen() */

/* Number of rows of the "TRANSITION_TABLE" matrix */
#define STATES_AMOUNT 5
/* Number of columns of the "TRANSITION_TABLE" matrix */
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

/* Callback function */
typedef void (*FSMActionFunc)();

/* Structure that represents the FSM */
struct FSM {
	enum State nextState;
	enum State currentState;
	FSMActionFunc actionFunction;
};

/* Function handles */
void handleTurnOn();
void handleTurnOff();
void handleSpeedUp();
void handleSpeedDown();

/* Matrix that contains the transitions */
struct FSM TRANSITION_TABLE[STATES_AMOUNT][STIMULUS_AMOUNT];
/* Array that store state names as strings */
const char *STATE_NAMES[STATES_AMOUNT] = {"Off", "Stopped", "Walking", "Running", "Error"};

const int FINISH = 9;
void initializeFSM(struct FSM *);
void stimulateFSM(struct FSM *, enum Stimulus);

int main(void)
{
	struct FSM fsm;
	unsigned int i;
	int invalidInput;
	int finishProgram;
	int stimulusToSend;
	char userInput[32];

	/* Initialize FSM */
	initializeFSM(&fsm);
	finishProgram = 0;

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
			stimulateFSM(&fsm, stimulusToSend);
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

void initializeFSM(struct FSM *fsm)
{
	/* Set the intial state */
	fsm->currentState = Off;
	/* Memset to 'TRANSITION_TABLE' to zero */
	memset(TRANSITION_TABLE, 0, sizeof(struct FSM));
	/* State_'Off' */
	TRANSITION_TABLE[Off][TurnOn].actionFunction    = handleTurnOn;
	TRANSITION_TABLE[Off][TurnOn].nextState         = Stopped;
	TRANSITION_TABLE[Off][TurnOff].actionFunction   = handleTurnOff;
	TRANSITION_TABLE[Off][TurnOff].nextState        = Off;
	TRANSITION_TABLE[Off][SpeedUp].actionFunction   = handleSpeedUp;
	TRANSITION_TABLE[Off][SpeedUp].nextState        = Off;
	TRANSITION_TABLE[Off][SpeedDown].actionFunction = handleSpeedDown;
	TRANSITION_TABLE[Off][SpeedDown].nextState      = Off;
	/* State 'Stopped' */
	TRANSITION_TABLE[Stopped][TurnOn].actionFunction    = handleTurnOn;
	TRANSITION_TABLE[Stopped][TurnOn].nextState         = Stopped;
	TRANSITION_TABLE[Stopped][TurnOff].actionFunction   = handleTurnOff;
	TRANSITION_TABLE[Stopped][TurnOff].nextState        = Off;
	TRANSITION_TABLE[Stopped][SpeedUp].actionFunction   = handleSpeedUp;
	TRANSITION_TABLE[Stopped][SpeedUp].nextState        = Walking;
	TRANSITION_TABLE[Stopped][SpeedDown].actionFunction = handleSpeedDown;
	TRANSITION_TABLE[Stopped][SpeedDown].nextState      = Error;
	/* State 'Walking' */
	TRANSITION_TABLE[Walking][TurnOn].actionFunction    = handleTurnOn;
	TRANSITION_TABLE[Walking][TurnOn].nextState         = Walking;
	TRANSITION_TABLE[Walking][TurnOff].actionFunction   = handleTurnOff;
	TRANSITION_TABLE[Walking][TurnOff].nextState        = Off;
	TRANSITION_TABLE[Walking][SpeedUp].actionFunction   = handleSpeedUp;
	TRANSITION_TABLE[Walking][SpeedUp].nextState        = Running;
	TRANSITION_TABLE[Walking][SpeedDown].actionFunction = handleSpeedDown;
	TRANSITION_TABLE[Walking][SpeedDown].nextState      = Stopped;
	/* State 'Running' */
	TRANSITION_TABLE[Running][TurnOn].actionFunction    = handleTurnOn;
	TRANSITION_TABLE[Running][TurnOn].nextState         = Running;
	TRANSITION_TABLE[Running][TurnOff].actionFunction   = handleTurnOff;
	TRANSITION_TABLE[Running][TurnOff].nextState        = Off;
	TRANSITION_TABLE[Running][SpeedUp].actionFunction   = handleSpeedUp;
	TRANSITION_TABLE[Running][SpeedUp].nextState        = Error;
	TRANSITION_TABLE[Running][SpeedDown].actionFunction = handleSpeedDown;
	TRANSITION_TABLE[Running][SpeedDown].nextState      = Walking;
	/* State 'Error' */
	TRANSITION_TABLE[Error][TurnOn].actionFunction    = handleTurnOn;
	TRANSITION_TABLE[Error][TurnOn].nextState         = Error;
	TRANSITION_TABLE[Error][TurnOff].actionFunction   = handleTurnOff;
	TRANSITION_TABLE[Error][TurnOff].nextState        = Off;
	TRANSITION_TABLE[Error][SpeedUp].actionFunction   = handleSpeedUp;
	TRANSITION_TABLE[Error][SpeedUp].nextState        = Error;
	TRANSITION_TABLE[Error][SpeedDown].actionFunction = handleSpeedDown;
	TRANSITION_TABLE[Error][SpeedDown].nextState      = Error;
}

void handleTurnOn()
{
	printf(" ----- <TurnOn> -----> ");
}

void handleTurnOff()
{
	printf(" ----- <TurnOff> -----> ");
}

void handleSpeedUp()
{
	printf(" ----- <SpeedUp> -----> ");
}

void handleSpeedDown()
{
	printf(" ----- <SpeedDown> -----> ");
}

/** @brief Stimulates the machine and advances to the next state.
 *
 *  @param fsm Finite State Machine to stimulate.
 *  @param stimulus Stimulus to send to the machine.
 *  @return void Does not return any value.
 */
void stimulateFSM(struct FSM *fsm, enum Stimulus stimulus)
{
	/* Prints the current state */
	printf("[%s]", STATE_NAMES[fsm->currentState]);
	/* Call the respective action function */
	TRANSITION_TABLE[fsm->currentState][stimulus].actionFunction();
	/* Advances to the next state */
	fsm->currentState = TRANSITION_TABLE[fsm->currentState][stimulus].nextState;
	/* Prints the new state */
	printf("[%s]\n", STATE_NAMES[fsm->currentState]);
}