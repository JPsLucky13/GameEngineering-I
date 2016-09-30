#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#else
#include <stdlib.h>
#endif // _DEBUG

//The number of words the user will introduce
int words;

//Stores the complete length of the sentence
int completeLength;

//Array of pointers to keep all of the words
char * allWords[100];

//Ask the user for the amount of words they would like to write in the 
//sentence
void QueryUser()
{
	printf("How many words would you like to write?");
	scanf_s("%d", &words);
}

//Get the length of the current word
int getLength(const char * word) {
	int length = 0;
	while (word[length] != '\0')
	{
		length++;
	}

	return length;
}

//Place the words the user writes into an array pointer
void FillOutWords()
{
	for (int i = 0; i < words; i++)
	{
		char currentWord[100];
		printf("word%d: ", i);
		scanf_s("%s", currentWord, 100);
		int length = getLength(currentWord);
		allWords[i] = (char*)malloc(sizeof(char) * (length + 1));

		for (int j = 0; j < length; j++)
		{
			allWords[i][j] = currentWord[j];
		}
		allWords[i][length] = '\0';
		completeLength += length;
		completeLength += words;
	}

}



//Makes the sentence of the array of words
char * MakeSentence(char * strings[])
{
	char  * sentence = (char*)malloc(sizeof(char) * (completeLength + 1));
	int sentenceIndex = 0;
	for (int i = 0; i < words; i++)
	{
		for (int j = 0; j < getLength(strings[i]); j++)
		{
			sentence[sentenceIndex] = strings[i][j];
			sentenceIndex++;

			if (j == getLength(strings[i]) - 1 && i != (words - 1)) {
				sentence[sentenceIndex] = ' ';
				sentenceIndex++;

			}

			if (i == (words - 1) && j == getLength(strings[i]) - 1)
			{
				sentence[sentenceIndex] = '.';
				sentenceIndex++;
			}
		}
	}
	sentence[sentenceIndex] = '\0';

	return sentence;

}



void main(int i_argc, char ** i_argl)
{

	//Ask the user for the words
	QueryUser();

	//Ask the user to introduce the words
	FillOutWords();


	/*
	const char * strings[] = {
	"This",
	"is",
	"a",
	"test",
	NULL
	};
	*/


	char * pSentence = MakeSentence(allWords);

	printf("The Sentence is: %s", pSentence);
	scanf_s("%s", 10);

	//Free the memory occupied by the sentence
	free(pSentence);
	for (int i = 0; i < words; i++)
	{
		free(allWords[i]);
		allWords[i] = NULL;
	}

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}