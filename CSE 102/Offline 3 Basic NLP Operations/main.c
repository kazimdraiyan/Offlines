#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_DOCS 50      // 50 paragraphs
#define MAX_LEN 5000     // Each paragraph max character count
#define MAX_TOKENS 500   // 500 words combining all documents
#define MAX_TOKEN_LEN 50 // Each word max length
#define NUM_STOP_WORDS 8
#define NUM_STEM_SUBSTRINGS 3

char stop_words[NUM_STOP_WORDS][MAX_TOKEN_LEN] = {"the", "is", "a", "an", "and", "in", "of", "to"};
char stem_substrings[NUM_STEM_SUBSTRINGS][MAX_TOKEN_LEN] = {"ing", "ed", "s"}; // TODO: Change MAX_TOKEN_LEN to something more suitable

// TODO: Change function names according to the problem statement
// TODO: Use strcpy() everywhere applicable, instead of manual copying.

// Helper functions
// TODO: Make print_documents more abstract to print any array of strings
void print_documents(char documents[][MAX_LEN], int document_count)
{
    for (int i = 0; i < document_count; i++)
    {
        printf("Document %d: %s\n", i + 1, documents[i]);
    }
}

void normalize_case_all(char documents[][MAX_LEN], int document_count)
{
    for (int i = 0; i < document_count; i++)
    {
        for (int j = 0; documents[i][j]; j++)
        { // documents[i][j] means it's not 0, which means it's not the null terminator.
            documents[i][j] = tolower(documents[i][j]);
        }
    }
}

void tokenize_all(char documents[][MAX_LEN], int document_count, char tokens[MAX_TOKENS][MAX_TOKEN_LEN], int *token_count)
{
    // Tokenization delimiters: whitespaces, commas, periods, colons, semicolons, question marks, exclamation points.
    char current_char;
    *token_count = 0;
    int current_token_len = 0;
    for (int i = 0; i < document_count; i++)
    {
        for (int j = 0; current_char = documents[i][j]; j++)
        {
            if (isalnum(current_char))
            {
                tokens[*token_count][current_token_len] = current_char;
                current_token_len++;
            }
            else
            {
                if (current_token_len > 0)
                {
                    (*token_count)++;
                    current_token_len = 0;
                }
            }
        }
    }
}

void remove_stop_words_all(char tokens[MAX_TOKENS][MAX_TOKEN_LEN], int token_count, char tokens_except_stop_words[MAX_TOKENS][MAX_TOKEN_LEN], int *tokens_except_stop_words_count)
{
    *tokens_except_stop_words_count = 0;
    for (int i = 0; i < token_count; i++)
    {
        int is_stop_word = 0;
        for (int j = 0; j < NUM_STOP_WORDS; j++)
        {
            if (!strcmp(tokens[i], stop_words[j]))
            {
                is_stop_word = 1;
            }
        }
        if (!is_stop_word)
        {
            int k;
            for (k = 0; tokens[i][k]; k++)
            {
                tokens_except_stop_words[*tokens_except_stop_words_count][k] = tokens[i][k];
            }
            tokens_except_stop_words[*tokens_except_stop_words_count][k] = '\0';
            (*tokens_except_stop_words_count)++;
        }
    }
}

void stem_all_tokens(char tokens_except_stop_words[MAX_TOKENS][MAX_TOKEN_LEN], int tokens_except_stop_words_count, char stemmed_tokens[MAX_TOKENS][MAX_TOKEN_LEN], int *stemmed_token_count) {
    *stemmed_token_count = 0;
    for (int i = 0; i < tokens_except_stop_words_count; i++) {
        int is_stemmed = 0;
        for (int j = 0; j < NUM_STEM_SUBSTRINGS; j++) {
            int token_len = strlen(tokens_except_stop_words[i]);
            int substring_len = strlen(stem_substrings[j]);
            int does_trailing_substring_match = 1;
            for (int k = 1; k <= substring_len; k++) {
                if (tokens_except_stop_words[i][token_len - k] != stem_substrings[j][substring_len - k]) {
                    does_trailing_substring_match = 0;
                    break;
                }
            }
            if (does_trailing_substring_match && token_len != substring_len) {
                strncpy(stemmed_tokens[*stemmed_token_count], tokens_except_stop_words[i], token_len - substring_len);
                (*stemmed_token_count)++;
                is_stemmed = 1;
                break;
            }
        }
        if (!is_stemmed) {
            strcpy(stemmed_tokens[*stemmed_token_count], tokens_except_stop_words[i]);
            (*stemmed_token_count)++;
        }
    }
}

double compute_tf(char word[], int doc_id) {
    
}

void clear_input_buffer(char *last_inputted_str_by_fgets)
{
    if (last_inputted_str_by_fgets == NULL || last_inputted_str_by_fgets[strlen(last_inputted_str_by_fgets) - 1] != '\n') {
        // If the pointer is null, then it is assumed that the input was taken by scanf, so there's at least a \n in the input buffer. In this case, the RHS of the || operator does not get evaluated.
        // If the pointer is not null, then it is assumed that the input was taken by fgets. In this case, if the last character (in front of \0) is not \n, then there's at least a \n in the input buffer.
        char temp;
        do {
            temp = getchar();
        } while (temp != '\n');
    }
}

void trim_string(char *str)
{
    // TODO: Leading trim

    // Trailing trim
    for (int len = strlen(str); len > 0 && isspace(str[len - 1]); len--)
    {
        str[len - 1] = '\0';
    }
}

void print_help(void)
{
    printf("set         - Prompt for the number of documents and their text.\n");
    printf("normalize   - Convert all documents to lowercase and display them.\n");
    printf("tokenize    - Tokenize all documents into words and display the tokens.\n");
    printf("remove_stop - Remove stop words from tokens and display the filtered tokens.\n");
    printf("stem        - Apply simple stemming (remove suffixes like \"ing\", \"ed\", \"s\") and display results.\n");
    printf("tf          - Compute and display Term Frequency for a specified word across documents.\n");
    printf("idf         - Compute and display Inverse Document Frequency for a specified word.\n");
    printf("tfidf       - Compute and display TF-IDF scores for a specified word across documents.\n");
    printf("stat        - Display TF, IDF, and TF-IDF for all tokens across all documents in a matrix format.\n");
    printf("help        - Print the list of all available commands.\n");
    printf("exit        - Exit the program.\n");
}

int main()
{
    char documents[MAX_DOCS][MAX_LEN];
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    char tokens_except_stop_words[MAX_TOKENS][MAX_TOKEN_LEN];
    char stemmed_tokens[MAX_TOKENS][MAX_TOKEN_LEN];

    char command[50]; // TODO: Manage command length in a better way
    int document_count;
    int token_count;
    int tokens_except_stop_words_count;
    int stemmed_token_count;

    // Initializing all documents with empty strings
    for (int i = 0; i < MAX_DOCS; i++)
        documents[i][0] = '\0';

    printf("Welcome to the Document Processing System!\n");
    print_help();

    while (1)
    {
        printf("Enter command: ");
        fgets(command, 50, stdin);
        clear_input_buffer(command);
        trim_string(command);

        if (!strcmp(command, "set"))
        {
            printf("Enter number of documents (1-50): ");
            scanf("%d", &document_count);
            clear_input_buffer(NULL);

            if (document_count < 1 || document_count > 50)
            {
                printf("Invalid number of documents. Must be from 1 to 50.\n");
                continue;
            }

            for (int i = 0; i < document_count; i++)
            {
                printf("Enter document %d: ", i + 1);
                fgets(documents[i], MAX_LEN, stdin);
                clear_input_buffer(documents[i]);
                trim_string(documents[i]);
            }
            printf("Documents set successfully.\n");
        }
        else if (!strcmp(command, "normalize"))
        {
            normalize_case_all(documents, document_count);
            printf("Normalized Documents:\n");
            print_documents(documents, document_count);
            printf("Documents normalized.\n");
        }
        else if (!strcmp(command, "tokenize"))
        {
            tokenize_all(documents, document_count, tokens, &token_count);
            printf("Tokens:\n");
            for (int i = 0; i < token_count; i++)
            {
                printf("%d. %s\n", i + 1, tokens[i]);
            }
            printf("Tokenization complete. Total tokens: %d\n", token_count);
        }
        else if (!strcmp(command, "remove_stop"))
        {
            remove_stop_words_all(tokens, token_count, tokens_except_stop_words, &tokens_except_stop_words_count);
            printf("Tokens after stop-word removal:\n");
            for (int i = 0; i < tokens_except_stop_words_count; i++)
            {
                printf("%d. %s\n", i + 1, tokens_except_stop_words[i]);
            }
            printf("Stop-word removal complete. Tokens remaining: %d\n", tokens_except_stop_words_count);
        }
        else if (!strcmp(command, "stem"))
        {
            stem_all_tokens(tokens_except_stop_words, tokens_except_stop_words_count, stemmed_tokens, &stemmed_token_count);
            printf("Stemmed Tokens:\n");
            for (int i = 0; i < stemmed_token_count; i++)
            {
                printf("%d. %s\n", i + 1, stemmed_tokens[i]);
            }
            printf("Stemming complete. Total stemmed tokens: %d\n", stemmed_token_count);
        }
        else
        {
            printf("Unknown command. Type 'help' for list of commands.\n");
        }
    }
}