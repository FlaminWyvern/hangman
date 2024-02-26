#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

const char *pics[] = {
    "  +---+\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|   |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " /    |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " / \\  |\n"
    "      |\n"
    "========="
    };

char* animalsWords[] = {"ant", "baboon", "badger", "bat", "bear", "beaver", "camel", "cat", "clam", "cobra", "cougar", "coyote", "crow", "deer", "dog", "donkey", "duck", "eagle", "ferret", "fox", "frog", "goat", "goose", "hawk", "lion", "lizard", "llama", "mole", "monkey", "moose", "mouse", "mule", "newt", "otter", "owl", "panda", "parrot", "pigeon", "python", "rabbit", "ra", "rat", "raven", "rhino", "salmon", "seal", "shark", "sheep", "skunk", "sloth", "snake", "spider", "stork", "swan", "tiger", "toad", "trout", "turkey", "turtle", "weasel", "whale", "wolf", "wombat", "zebra"};
const int animalsLength = 64;
int *indices;
char alphabet[26];

void printHangman(int index);
char *createHiddenWord(char *word);
char *findWord(int index);
int getRandomIndex();
int scanWord(char c, char *word);
void clearInputBuffer();
int scanDashes(char *word);
int *createIndices();
int scanRepeatingLetters(char c);

int main(int argc, char* argv[]){
    int wordIndex = getRandomIndex();
    char *word = findWord(wordIndex);
    char *hiddenWord = createHiddenWord(word);
    int gameIndex = 0;
    int k = 0;
    int correct = 0;
    puts("WELCOME TO HANGMAN!");
    while(gameIndex < 6){
        int *indices = createIndices();
        printf("\nEnter letter: ");
        char letter;
        scanf(" %c", &letter);
        clearInputBuffer();
        if(scanRepeatingLetters(letter)){
            puts("Letter already guessed");
            puts(hiddenWord);
            printHangman(gameIndex);
            sleep(2);
            system("clear");
            continue;
        }
        int hiddenWordIndex = scanWord(letter, word);
        if(hiddenWordIndex != -1){
            for(int i=0; i  < hiddenWordIndex; i++){
                hiddenWord[indices[i]] = word[indices[i]];
            }
            alphabet[k] = letter;
            k++;
            puts(hiddenWord);
            if(scanDashes(hiddenWord)){
                correct = 1;
                break;
            }
            
        }
        else{
            puts("Letter not in word");
            alphabet[k] = letter;
            k++;
            gameIndex++;
            puts(hiddenWord);
        }
        printHangman(gameIndex);
        free(indices);
        sleep(2);
        system("clear");
    }
    free(hiddenWord);
    if(correct){
        puts("Great Job!");
    }
    else{
        printf("\nThe word was %s\n", word);
    }
    puts("Thanks for playing!");
}

void printHangman(int index){
    printf("%s", pics[index]);
}

char *findWord(int index){
    return animalsWords[index];
}

int getRandomIndex(){
    srand(time(NULL));
    int index = rand() % animalsLength;
    return index;
}

char *createHiddenWord(char *word){
    char *hiddenWord = malloc(strlen(word)+1);
    for(int i=0; i < strlen(word); i++){
        hiddenWord[i] = '_';
    }
    hiddenWord[strlen(word)] = '\0';
    return hiddenWord;
}

int scanWord(char c, char *word){
    // createIndices();
    int j=0;
    int charFound = 0;
    for(int i=0; i < strlen(word); i++){
        if(word[i] == c){
            charFound++;
            indices[j] = i;
            j++;
        }
    }
    if(charFound > 0){
        return charFound;
    }
    return -1;
}

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int scanDashes(char *word){
    for(int i=0; i < strlen(word); i++){
        if(word[i] == '_'){
            return 0;
        }
    }
    return 1;
}

int *createIndices(){
    indices = malloc(64);
    return indices;
}

int scanRepeatingLetters(char c){
    for(int i=0; i < 26; i++){
        if(alphabet[i] == c){
            return 1;
        }
    }
    return 0;
}