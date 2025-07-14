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
char stem_substrings[NUM_STEM_SUBSTRINGS][MAX_TOKEN_LEN] = {"ing", "ed", "s"};

int token_count = 0;

void print_documents(char documents[][MAX_LEN], int document_count)
{
    for (int i = 0; i < document_count; i++)
    {
        printf("Document %d: %s\n", i + 1, documents[i]);
    }
}

void print_tokens(char tokens[][MAX_TOKEN_LEN])
{
    for (int i = 0; i < token_count; i++)
    {
        printf("%d. %s\n", i + 1, tokens[i]);
    }
}

void normalize_case_all(char documents[][MAX_LEN], int document_count)
{
    for (int i = 0; i < document_count; i++)
    {
        for (int j = 0; documents[i][j]; j++)
        {
            documents[i][j] = tolower(documents[i][j]);
        }
    }
}

void tokenize_all(char documents[][MAX_LEN], int document_count, char tokens[][MAX_TOKEN_LEN])
{
    // Clear the tokens array
    for (int i = 0; i < MAX_TOKENS; i++)
        tokens[i][0] = '\0';

    // Tokenization delimiters: whitespaces, commas, periods, colons, semicolons, question marks, exclamation points.
    token_count = 0;
    char current_char;
    int current_token_len = 0;
    for (int i = 0; i < document_count; i++)
    {
        for (int j = 0; documents[i][j]; j++)
        {
            current_char = documents[i][j];
            if (isalnum(current_char))
            {
                tokens[token_count][current_token_len] = current_char;
                current_token_len++;
            }
            if (!isalnum(current_char) || j == strlen(documents[i]) - 1)
            {
                // Delimiter found or end of document
                if (current_token_len > 0)
                {
                    // This if statement ensures that the previous character was not a delimiter
                    tokens[token_count][current_token_len] = '\0'; // Null-terminate the current token
                    token_count++;
                    current_token_len = 0;

                    if (token_count == MAX_TOKENS)
                    {
                        return;
                    }
                }
            }
        }
    }
}

void remove_stop_words_all(char tokens[][MAX_TOKEN_LEN])
{
    int new_token_count = token_count;
    int gap_count = 0; // The number of consequent gaps (stop words) immediately before the current token.
    for (int i = 0; i < token_count; i++)
    {
        int is_stop_word = 0;
        for (int j = 0; j < NUM_STOP_WORDS; j++)
        {
            if (!strcmp(tokens[i], stop_words[j]))
            {
                is_stop_word = 1;
                tokens[i][0] = '\0';
                gap_count++;
                new_token_count--;
                break;
            }
        }
        if (!is_stop_word && gap_count > 0) {
            // Bringing the current token to the front of the gaps.
            strcpy(tokens[i - gap_count], tokens[i]);
            tokens[i][0] = '\0';
            // The gap count remains the same.
        }
    }
    token_count = new_token_count;
}

void stem_all_tokens(char tokens[][MAX_TOKEN_LEN])
{
    int stemmed_token_count = token_count;
    int gap_count = 0;
    for (int i = 0; i < token_count; i++)
    {
        int is_removed = 0;
        for (int j = 0; j < NUM_STEM_SUBSTRINGS; j++)
        {
            int token_len = strlen(tokens[i]);
            int substr_len = strlen(stem_substrings[j]);

            // Check whether the current token (i-th) ends with the current (j-th) substring.
            int ends_with_substr = 1;
            if (token_len < substr_len)
            {
                // The token is shorter than the substring, so it cannot end with it.
                ends_with_substr = 0;
                continue;
            }
            for (int k = 1; k <= substr_len; k++)
            {
                if (tokens[i][token_len - k] != stem_substrings[j][substr_len - k])
                {
                    ends_with_substr = 0;
                    break;
                }
            }

            if (ends_with_substr)
            {
                if (token_len == substr_len)
                {
                    // If a token is equal to a stem substring, then it is removed. For example, if "ing" is a token, it will be removed.
                    tokens[i][0] = '\0';
                    is_removed = 1;
                    gap_count++;
                    stemmed_token_count--;
                }
                else
                {
                    // Stemming
                    tokens[i][token_len - substr_len] = '\0';
                }
                break;
            }
        }
        if (gap_count > 0 && !is_removed)
        {
            // Bringing the current token to the front of the gaps.
            strcpy(tokens[i - gap_count], tokens[i]);
            tokens[i][0] = '\0';
        }
    }
    token_count = stemmed_token_count;
}

double compute_tf(char word[], int doc_id)
{
}

// Returns 1 if any meaningful user input is in the buffer. Considers non-whitespace characters as meaningful.
int clear_input_buffer(char *last_inputted_str_by_fgets)
{
    int meaningful_char_count_in_buffer = 0;
    if (last_inputted_str_by_fgets == NULL || last_inputted_str_by_fgets[strlen(last_inputted_str_by_fgets) - 1] != '\n')
    {
        // If the pointer is null, then it is assumed that the input was taken by scanf, so there's at least a \n in the input buffer. In this case, the RHS of the || operator does not get evaluated.
        // If the pointer is not null, then it is assumed that the input was taken by fgets. In this case, if the last character (in front of \0) is not \n, then there's at least a \n in the input buffer.
        char temp;
        do
        {
            temp = getchar();
            if (!isspace(temp))
            {
                meaningful_char_count_in_buffer++;
            }
        } while (temp != '\n');
    }
    return meaningful_char_count_in_buffer > 0;
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
    printf("preprocess  - Apply normalization, tokenization, stop-words removal, and stemming orderly.\n");
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

    char command[50]; // TODO: Manage command length in a better way
    int document_count;

    int is_preprocessed = 0;

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
                if (clear_input_buffer(documents[i]))
                {
                    // Meaningful user input is in the buffer, so the inputted document exceeds MAX_LEN - 1
                    printf("Document too long.\n");
                    documents[i][0] = '\0'; // Reset the current document
                    i--;
                    continue;
                }
                trim_string(documents[i]);
                if (documents[i][0] == '\0')
                {
                    printf("Document cannot be empty.\n");
                    i--;
                    continue;
                }
            }
            printf("Documents set successfully. Please, enter 'preprocess' command now. It will not take other commands.\n");
        }
        else if (!strcmp(command, "preprocess"))
        {
            // Normalization
            normalize_case_all(&documents[0], document_count);
            printf("Normalized Documents:\n");
            print_documents(documents, document_count);
            printf("Documents normalized.\n");

            // Tokenization
            tokenize_all(documents, document_count, tokens);
            printf("Tokens:\n");
            print_tokens(tokens);
            printf("Tokenization complete. Total tokens: %d\n", token_count);

            // Stop-words removal
            remove_stop_words_all(tokens);
            printf("Tokens after stop-word removal:\n");
            print_tokens(tokens);
            printf("Stop-word removal complete. Tokens remaining: %d\n", token_count);

            // Stemming
            stem_all_tokens(tokens);
            printf("Stemmed Tokens:\n");
            print_tokens(tokens);
            printf("Stemming complete. Total stemmed tokens: %d\n", token_count);
        }
        else if (!strcmp(command, "tf"))
        {
            if (!is_preprocessed)
            {
                printf("Please, enter 'preprocess' command now. It will not take other commands.\n");
                continue;
            }
        }
        else if (!strcmp(command, "idf"))
        {
            if (!is_preprocessed)
            {
                printf("Please, enter 'preprocess' command now. It will not take other commands.\n");
                continue;
            }
        }
        else if (!strcmp(command, "tfidf"))
        {
            if (!is_preprocessed)
            {
                printf("Please, enter 'preprocess' command now. It will not take other commands.\n");
                continue;
            }
        }
        else if (!strcmp(command, "stat"))
        {
            if (!is_preprocessed)
            {
                printf("Please, enter 'preprocess' command now. It will not take other commands.\n");
                continue;
            }
        }
        else if (!strcmp(command, "help"))
        {
            print_help();
        }
        else if (!strcmp(command, "exit"))
        {
            break;
        }
        else
        {
            printf("Unknown command. Type 'help' for list of commands.\n");
        }
    }
}