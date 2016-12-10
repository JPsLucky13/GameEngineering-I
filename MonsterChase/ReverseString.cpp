#pragma once

size_t StringLength(const char* word) {

	int length = 0;
	while (word[length] != '\0')
	{
		length++;

	}
	return length;

}




char * ReverseString(char* string) {



	const size_t length = StringLength(string);
	size_t count;


	if (length % 2 == 0) {
		count = length / 2;
	}
	else {
		count = (length / 2) - ((length / 2) % 1);
	}

		for (size_t i = 0; i <count; i++)
		{

			char temp = ' ';

			temp = string[i];
			string[i] = string[(length-1) - i];
			string[(length-1) - i] = temp;
		}
	return string;

}

