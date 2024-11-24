#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define WORD_COUNT 10
#define MAX_WORD_LENGTH 20

void displayWordState(char *word, char *guesses);
int isValidGuess(char guess, char *guesses);

int main(void) {
    char *wordList[WORD_COUNT] = {"computer", "programming", "developer", "software", "hardware",
                                  "keyboard", "algorithm", "internet", "database", "password"};

    // listeden rastgele kelime seçme
    srand((unsigned int)time(NULL));
    char *selectedWord = wordList[rand() % WORD_COUNT];

    char guesses[MAX_WORD_LENGTH] = {0}; // tahminleri saklama
    int remainingTries = MAX_TRIES;
    int wordGuessed = 0;

    printf("Adam Asmacaya Hoşgeldin!\n\n");

    while (remainingTries > 0) {
        printf("Word: ");
        displayWordState(selectedWord, guesses);
        printf("\nTahmin hakkın: %d\n", remainingTries);
        printf("Bulunan harfler: %s\n", guesses[0] ? guesses : "Henüz hiçbir harf yok");

        // oyuncudan tahmin (input) alma
        char guess;
        printf("\nTek bir harf dene: ");
        if (scanf(" %c", &guess) != 1) {
            printf("Lütfen geçerli bir harf gir.\n\n");
            while (getchar() != '\n');
            continue;
        }

        // küçük harf yapma
        guess = tolower(guess);

        // tahmin değerlendirme
        if (!isValidGuess(guess, guesses)) {
            printf("Lütfen önceden girilmemiş ve alfabetik bir harf gir.\n\n");
            continue;
        }

        // tahminleri toparlama
        int len = (int)strlen(guesses);
        guesses[len] = guess;
        guesses[len + 1] = '\0';

        // harf tahmini yanlışsa..
        if (strchr(selectedWord, guess) == NULL) {
            remainingTries--;
            printf("Yanlış harf :(\n\n");
        }

        // tahmin kontrolü
        int allGuessed = 1;
        for (int i = 0; i < strlen(selectedWord); i++) {
            if (!strchr(guesses, selectedWord[i])) {
                allGuessed = 0;
                break;
            }
        }

        if (allGuessed) {
            wordGuessed = 1;
            break;
        }
    }

    // oyunun sonucu
    if (wordGuessed) {
        printf("\nTebrikler, kazandınız! Kelime: %s\n", selectedWord);
    } else {
        printf("\nÜzgünüm, yanlış cevap. Doğru kelime: %s\n", selectedWord);
    }

    return 0;
}

// kelimenin son durumu
void displayWordState(char *word, char *guesses) {
    for (int i = 0; i < strlen(word); i++) {
        if (strchr(guesses, word[i])) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// tahmin kontrolü
int isValidGuess(char guess, char *guesses) {
    if (!isalpha(guess)) {
        return 0; // alfabetik olmalı
    }
    if (strchr(guesses, guess)) {
        return 0; // onceden tahmin edilmemiş olmalı
    }
    return 1;
}

