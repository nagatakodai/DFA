#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 255

/* 状態の定義 */
typedef enum {
	Sp, Sq, Sr, Sd
} STATE;

/* グローバル変数 */
char Str[MAX_SIZE + 1]; /* 文字列格納用の配列 */

/* プロトタイプ宣言 */
void printConfiguration(STATE s, char* str);
void printInfer(void);
void getWord(void);
char nextChar(void);

int main(void) {
	STATE s = Sp; /* q0 = p */
	char ch;
	int count = 0; /* 処理した文字数のカウンタ */

	/* 記号列の読み込み */
	getWord();

	/* step 1 */
	printConfiguration(s, Str + count);

	/* 1文字ずつ読みオートマトンを動作させる */
	while ((ch = nextChar()) != '\0') {
		printf(" ");
		printInfer();
		printf(" ");
		switch (s) {
		case Sp:
			/* step 2 */
			if (ch == 'a')
				s = Sq;
			else
				s = Sd;
			break;

		case Sq:
			if (ch == 'b')
				s = Sr;
			else if (ch == 'a')
				s = Sq;
			else
				s = Sd;
			break;

		case Sr:
			if (ch == 'b')
				s = Sr;
			else if (ch != 'b')
				s = Sd;
			break;

		case Sd:
			s = Sd;
			break;

		}
		count++;
		printConfiguration(s, Str + count);
	}
	printf("\n");

	/* 受理判定 */
	if (s == Sr) { /* F = {r} */
		printf("accept\n");
	}
	else {
		printf("reject\n");
	}

	return 0;
}

void printConfiguration(STATE s, char* str) {
	printf("(");
	switch (s) {
	case Sp:
		printf("p");
		break;

		/* step 1 */
	case Sq:
		printf("q");
		break;

	case Sr:
		printf("r");
		break;

	case Sd:
		printf("d");
		break;

	}
	printf(", ");
	printf("%s", str);
	printf(")");
}

void printInfer(void) {
	printf("|-");
}

void getWord(void) {
	printf("w = ");
	scanf("%255s", Str);
}

char nextChar(void) {
	static char* pStr = Str;
	char c;

	if (*pStr != '\0') {
		c = *pStr;
		pStr++;
	}
	else {
		c = *pStr;
	}

	return c;
}

