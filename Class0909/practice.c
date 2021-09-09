#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct trump
{
    char order;
    char shape[3];
    char number;
};
struct card
{
    char order;
    char number;
};

void make_card(struct trump m_card[]);
void display_card(struct trump m_card[]);

void make_card(struct trump m_card[])
{
    int i, j;
    char shape[4][3] = {"¢¼", "¡ß", "¢¾", "¢À"};
    for (i = 0; i < 4; i++)
    {
        for (j = i * 13; j < i * 13 + 13; j++)
        {
            m_card[j].order = i;
            strcpy(m_card[j].shape, shape[i]);
            m_card[j].number = j % 13 + 1;
            switch (m_card[j].number)
            {
            case 1:
                m_card[j].number = 'A';
                break;
            case 11:
                m_card[j].number = 'J';
                break;
            case 12:
                m_card[j].number = 'Q';
                break;
            case 13:
                m_card[j].number = 'K';
                break;
            }
        }
    }
}

void display_card(struct trump m_card[])
{
    int i, count = 0;
    int check = 0;
    int j, lotto[6];
    srand(time(NULL));
    for (i = 0; i <= 5; i++)
    {
        check = 0;
        lotto[i] = rand() % 45 + 1;
        for (j = 0; j < i; j++)
        {
            if (lotto[i] == lotto[j])
            {
                i--;
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            printf("%s", m_card[lotto[i]].shape);
            if (10 < m_card[lotto[i]].number)
                printf("  %-2c ", m_card[lotto[i]].number);
            else
                printf("  %-2d ", m_card[lotto[i]].number);
            count++;
        }
    }
}

int main(void)
{
    struct trump card[52];
    make_card(card);
    display_card(card);
    return 0;
}
