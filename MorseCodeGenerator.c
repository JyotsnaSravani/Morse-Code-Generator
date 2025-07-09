#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char *morse[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",       // A-I
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",     // J-R
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",            // S-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....",       // 0-6
    "--...", "---..", "----."                                            // 7-9
};

void encode(const char *text) {
	int i;
    printf("Encoded Morse Code:\n");
    for (i = 0; text[i] != '\0'; i++) {
        char ch = toupper(text[i]);
        
        if (ch == ' ') {
            printf(" / ");
            continue;
        }
        
        // Find index in letters
        char *pos = strchr(letters, ch);
        if (pos) {
            int index = pos - letters;
            printf("%s ", morse[index]);
        }
    }
    printf("\n");
}

void decode(const char *code) {
    printf("Decoded Text:\n");
    int i,j;
    char temp[10];  
    int pos = 0;
    
    for (i = 0; ; i++) {
        char c = code[i];
        
        if (c != ' ' && c != '\0') {
            if (pos < (int)sizeof(temp) - 1)
                temp[pos++] = c;
        } else {
            if (pos > 0) {
                temp[pos] = '\0';
                if (strcmp(temp, "/") == 0) {
                    printf(" ");
                } else {
                    int found = 0;
                    for ( j = 0; j < (int)(sizeof(morse) / sizeof(morse[0])); j++) {
                        if (strcmp(temp, morse[j]) == 0) {
                            printf("%c", letters[j]);
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        printf("?");
                    }
                }
                pos = 0;
            }
            if (c == '\0')
                break;
        }
    }
    printf("\n");
}

int main() {
    int choice;
    char input[1024];
    
    while (1) {
        printf("\n1. Encode Text to Morse Code\n2. Decode Morse Code to Text\n3. Exit\nChoose: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Try again.\n");
            continue;
        }
        getchar(); 
        
        if (choice == 3) {
            printf("Exiting...\n");
            break;
        }
        
        printf("Enter input:\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  
        
        if (choice == 1) {
            encode(input);
        } else if (choice == 2) {
            decode(input);
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

