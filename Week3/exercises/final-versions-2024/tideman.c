#include <cs50.h>
#include <stdio.h>
#include <string.h>

// [CS50] Max number of candidates
#define MAX 9

// [CS50] preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// [CS50] locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// [CS50] Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// [CS50] (Main) Functions prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
// Utils prototypes
int get_pair_strength(pair p);

int main(int argc, string argv[])
{
    // [CS50] Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // [CS50] Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // [CS50] Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // [CS50] Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // [CS50] ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // [CS50] Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

// [CS50] Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// [CS50] Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int current = ranks[i];

        // Loop all over the next ones after current rank
        for (int j = i + 1; j < candidate_count; j++)
        {
            int next = ranks[j];
            preferences[current][next]++;
        }

    }
    return;
}

// [CS50] Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1 ; j < candidate_count; j++)
        {
            // As we compare both directions (all combinations between 'i' and 'j')
            // in order to avoid duplication, we are only comparing it once
            // by starting considering 'j' as the index after i, and them the next,
            // and so on
            int iAgainstJ = preferences[i][j];
            int jAgainstI = preferences[j][i];

            if (iAgainstJ != jAgainstI)
            {
                pairs[pair_count].winner = iAgainstJ > jAgainstI ? i : j;
                pairs[pair_count].loser = iAgainstJ < jAgainstI ? i : j;

                pair_count++;
            }
        }
    }

    return;
}

// [CS50] Sort pairs in decreasing order by strength of victory
// TODO -> To create versions applying all sorts algorithms presented in class3
// This sort algorithm is failing on check 50. Need to debug more.
void sort_pairs(void)
{
    // bubble sort should not be a problem once MAX == 9.
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (get_pair_strength(pairs[j]) < get_pair_strength(pairs[j + 1]))
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// [CS50] Lock pairs into the candidate graph in order, without creating cycles
// (it won't work if you don't sort the pairs previously)
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int current_winner = pairs[i].winner;
        int current_loser = pairs[i].loser;

        if (current_winner == current_loser)
        {
            continue;
        }

        bool is_lockable = true;

        for (int j = 0; j < i; j++)
        {
            int previous_winner = pairs[j].winner;

            if (current_loser != previous_winner)
            {
                is_lockable = is_lockable && !locked[current_loser][previous_winner];
            }
        }

        if (is_lockable)
        {
            locked[current_winner][current_loser] = true;
        }
    }
}

// [CS50] Print the winner of the election
void print_winner(void)
{
    // tideman problem set clearly mentions we may assume 1 winner, so:
    int winner_index = -1;

    for (int i = 0; i < candidate_count; i++)
    {
        bool none_locked = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                none_locked = none_locked && !locked[j][i];
            }
        }

        if (none_locked)
        {
            // tideman problem set clearly mentions we may assume only 1 winner, so:
            winner_index = i;
        }
    }

    if (winner_index >= 0)
    {
        printf("%s\n", candidates[winner_index]);
    }
}

// Utils
int get_pair_strength(pair p)
{
    return preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
}
