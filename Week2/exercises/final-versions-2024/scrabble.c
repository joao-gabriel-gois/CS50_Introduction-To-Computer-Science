#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int get_char_index_in_points_array(char c, int index);


int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 == score2)
    {
        printf("Tie!\n");
        return 0;
    }

    int winner =  score1 > score2 ? 1 : 2;
    
    printf("Player %i wins!\n", winner);
}



int compute_score(string word)
{
    int word_length = strlen(word);
    int result = 0;

    for (int i = 0; i < word_length; i++)
    {
        int char_index_in_points_array = get_char_index_in_points_array(word[i], i);
        int char_score = char_index_in_points_array != -1 ? POINTS[char_index_in_points_array] : 0;

        result += char_score;
    }

    return result;
}


int get_char_index_in_points_array(char c, int index)
{
    char c_lower = tolower(c);
    int char_index_in_points_array = c_lower - 'a';

    char no_score_condition = char_index_in_points_array < 0 || char_index_in_points_array > 25;

    return no_score_condition ? -1 : char_index_in_points_array;
}
