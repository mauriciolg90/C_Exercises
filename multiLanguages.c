#include <stdio.h>

/* Number of rows of the "languagesTable" matrix */
#define LANGUAGES_AMOUNT 2
/* Number of columns of the "languagesTable" matrix */
#define MESSAGES_AMOUNT 3

/* Enum that represents languages */
enum Languages {
	English,
	Spanish
};

/* Enum that represents messages */
enum Messages {
	HelloWorld,
	OutOfMemory,
	FileNotFound,
	HolaMundo,
	SinMemoria,
	ArchivoNoEncontrado
};

/* Matrix with the corresponding texts */
const char *languagesTable[LANGUAGES_AMOUNT][MESSAGES_AMOUNT] = {
	{"HelloWorld", "OutOfMemory", "FileNotFound"},
	{"HolaMundo", "SinMemoria", "ArchivoNoEncontrado"}
};

/* Function prototype */
const char *getMessage(enum Languages language, enum Messages message);

int main(void) {
	const char *translatedMessage;

	translatedMessage = getMessage(Spanish, OutOfMemory);
	printf("The translated message is: %s\n", translatedMessage);
	return 0;
}

/** @brief Translates the message to the specified language.
 *
 *  @param language Output language.
 *  @param message Message to translate.
 *  @return char Translated message.
 */
const char *getMessage(enum Languages language, enum Messages message) {
	return languagesTable[language][message];
}

/*										PREGUNTA
Asumiendo que el valor del enumerado es consecutivo, empezando en cero: ¿Se le ocurre 
alguna manera de saber cuantos mensajes y lenguajes hay en el enumerado?

const int messagesAmount = END - FIRST + 1; // 6
const int languagesAmount = END - FIRST + 1; // 2
*/