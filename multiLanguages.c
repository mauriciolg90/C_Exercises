#include <stdio.h>

/* Enum that represents languages */
enum Languages {
	English,
	Spanish,
	LanguagesAmount
};

/* Enum that represents messages */
enum Messages {
	HelloWorld,
	OutOfMemory,
	FileNotFound,
	HolaMundo,
	SinMemoria,
	ArchivoNoEncontrado,
	MessagesAmount
};

/*
 * "languagesTable" is the matrix with the corresponding texts.
 * "LanguagesAmount" is the number of rows of the matrix.
 * "MessagesAmount / LanguagesAmount" is the number of columns.
 */
const char *languagesTable[LanguagesAmount][MessagesAmount / LanguagesAmount] = {
	{"HelloWorld", "OutOfMemory", "FileNotFound"},
	{"HolaMundo", "SinMemoria", "ArchivoNoEncontrado"}
};

/* Function prototype */
const char *getMessage(enum Languages language, enum Messages message);

int main(void)
{
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
const char *getMessage(enum Languages language, enum Messages message)
{
	return languagesTable[language][message];
}

/*										PREGUNTA
Asumiendo que el valor del enumerado es consecutivo, empezando en cero: ¿Se le ocurre 
alguna manera de saber cuantos mensajes y lenguajes hay en el enumerado?

const int messagesAmount = END - FIRST + 1; // 6
const int languagesAmount = END - FIRST + 1; // 2
*/