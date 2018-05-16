#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 29

struct DicTree {
	struct DicTree *letter[N];
};

int indexChar(char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		return (letter - 'A');
	}
	if (letter >= 'a' && letter <= 'z') {
		letter = letter - 32 - 'A';
		return letter;
	}
	if (letter == '-') {
		return 26;
	}
	if (letter == '\'') {
		return 27;
	}
}

char printChar(int n) {
	char letter;
	if (n < 26) {
		letter = n + 'A';
	}
	if (n == 26) {
		letter = '-';
	}
	if (n == 27) {
		letter = '\'';
	}
	return letter;
}

void addWord(char w[20], struct DicTree *top) {
	int i;
	struct DicTree *next;
	char l;
	for (i = 0; i < strlen(w); i++) {
		l = w[i];
		if (top->letter[indexChar(l)]){
			top = top->letter[indexChar(l)];
		}
		else{
			next = (struct DicTree *)malloc(sizeof(struct DicTree));
			top->letter[indexChar(l)] = next;
			int n;
			for (n = 0; n < N; n++) {
					next->letter[n] = NULL;
				}
			top = next;
			}
		}
	top->letter[N-1] = top;
}

void printWord(struct DicTree *top, char *word, char *pword){
	int i;
	for (i = 0; i < N-1;i++) {
		if (top->letter[i]) {
			*pword = printChar(i);
			if (top->letter[i] == top->letter[i]->letter[N - 1]) {
				*(pword) = '\0';
				printf("%s\n", word);
			}
			printWord(top->letter[i],word,pword+1);
		}
	}
}

void file_to_DicTree(char *path, char word[50], struct DicTree *top) {
	FILE *fPointer;
	fPointer = fopen(path, "r+");
	if (fPointer == NULL) {
		printf("Nie da sie odczytac pliku!");
	}
	else {
		while (!feof(fPointer)) {
			fgets(word, 50, fPointer);
			addWord(word, top);
		}
	}
	fclose(fPointer);
}

void delete_word(struct DicTree *top, char word[50]) {
	int i = 0;
	printf("%d", top);
	while (i < strlen(word)) {
		if (top->letter[indexChar(word[i])] != NULL) {
			top = top->letter[indexChar(word[i])];
			puts(" ");
			printf("%d", top);
			puts(" ");
			printf("%d", top->letter[N - 1]);
			i++;
		}
		else printf("Nie ma takiego wyrazu");
	}
	puts(" ");
	printf("%d", top);
	puts(" ");
	printf("%d", top->letter[N - 1]);

}

struct DicTree *search_word_delete(struct DicTree *top, char word[50]) {
	int i = 0;
	while (i < strlen(word)) {
		if (top->letter[indexChar(word[i])] != NULL) {
			top = top->letter[indexChar(word[i])];
			printf("%c\n", word[i]);
			i++;
		}
		else {
			printf("Podanego wyrazu nie ma w slowniku");
			return NULL;
		}
	}
	puts(" ");
	if (&top == &(top->letter[N - 1])) {
		printf("Wyraz istnieje\n");
		return top;
	}
}

int main()
{
	char path[100] = "words.txt", word[50], add[50];
	int i;
	int n;
	struct DicTree *top = (struct DicTree *)malloc(sizeof(struct DicTree));
	struct DicTree *tmp;
	for (n = 0; n < N; n++) {
		top->letter[n] = NULL;
	}
	file_to_DicTree(path, word, top);
	/*
	printf("Wybierz opcje: ");
	scanf("%d", &i);
	if (i==1) {
		printf("Podaj slowo: ");
		scanf("%s", add);
		addWord(add, top);
		printf("Slowo dodano pomyslnie\n");
	}
	else
	if (i==2) {

	}
	else
	if (i==3) {

	}
	else printf("Komenda nie rozpoznana");
	*/

	char word1[20] = "aaa";
	/*char word2[20] = "ASA";
	char word3[20] = "AS";
	char word4[20] = "ASHE";
	char word5[20] = "ASHEEA";
	addWord(word1, top);
	addWord(word2, top);
	addWord(word3, top);
	addWord(word4, top);
	addWord(word5, top);*/
	//printWord(top,word,word);

	search_word_delete(top, word1);
	/*delete_word(top, word2);
	delete_word(top, word3);
	delete_word(top, word4);
	delete_word(top, word5);*/
	return 0;
}


