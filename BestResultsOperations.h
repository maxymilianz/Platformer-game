#pragma once

char checkPosition(char level) {
	char i;
	for (i = 0; i < 5; i++) {
		if (level >= scores[i])
			break;
	}

	return i;
}

void enterName(char ch) {
	char i;
	for (i = 0; names[getName][i] != 0 && i < 16; i++);

	if (i < 16) {
		if (ch <= 25)
			names[getName][i] = ch + 'A';
		else
			names[getName][i] = ch + 22;
	}
}

char length() {
	char i;
	for (i = 0; names[getName][i] != 0; i++);
	return i;
}

void delete1Char() {
	char i;
	for (i = 0; names[getName][i] != 0; i++);
	names[getName][i - 1] = 0;
}

void moveResults() {
	for (char i = 4; i > getName; i--) {
		for (char j = 0; names[i][j] != 0 && j < 16; j++)
			names[i][j] = 0;
		for (char j = 0; names[i - 1][j] != 0 && j < 16; j++)
			names[i][j] = names[i - 1][j];

		scores[i] = scores[i - 1];
	}

	for (char i = 0; names[getName][i] != 0; i++)
		names[getName][i] = 0;
}

char length(char i) {
	char j;
	for (j = 0; names[i][j] != 0; j++);
	return j;
}

char nrOfScores() {
	char i;
	for (i = 0; i < 5 && scores[i] != 0; i++);
	return i;
}
