#define _CRT_SECURE_NO_WARNINGS //scanf보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void heap_sort(int *, int);
void heap(int *, int, int);
int *get_number();

int main(void)
{
    int num[45], sel[6];
    int times, range, index, move;
    int money = 1000, batting = 0, cnt = 0;
    srand((unsigned)time(NULL));
    int *getnum;

    int a = 1;
    while (a == 1)
    {
        getnum = get_number(); // 로또 숫자 고르기

        cnt = 0;     // 맞은개수 초기화
        batting = 0; //베팅 금액 초기화
        printf("로또 당첨 번호 \n\n");
        printf("현재 잔액 : %d\n", money); // 현재 잔액 표시
        printf("===============\n");
        for (int i = 0; i <= 5; i++)
        {
            printf("%d. : %d \n", i + 1, getnum[i]); // 고른 로또 숫자 출력
        }
        printf("===============\n");

        //베팅 시작
        while (1)
        {
            printf("베팅금액 : ");
            scanf("%d", &batting);
            if (batting > money) //잔액보다 베팅하는 금액이 큰지 확인
            {
                printf("\n잔액이 부족합니다 다시 입력해주세요\n");
            }
            else //아닐경우 while문 종료
            {
                break;
            }
        }
        //베팅 끝

        money = money - batting; // 현재 잔액에서 베팅금액을 감소
        printf("\n");
        printf("베팅금액 : %d\n\n", batting);
        printf("현재 잔액 : %d\n", money);

        for (index = 0; index <= 44; index++)
            num[index] = index + 1;

        for (times = 0; times <= 5; times++)
        {
            range = 45 - times;
            index = rand() % range;
            sel[times] = num[index];

            if (index == 44 - times)
                continue;
            else
            {
                for (move = index; move <= 44 - times; move++)
                    num[move] = num[move + 1];
            }
        }

        // 결과출력 시작

        for (index = 0; index <= 5; index++) //당첨번호 출력
            printf("\n%d번째 당첨번호 : %2d ", index + 1, sel[index]);

        heap_sort(sel, 5);    //당첨번호 정렬
        heap_sort(getnum, 5); // 고른숫자 정렬

        printf("\n\n[당첨 번호 정렬]\n");
        for (index = 0; index <= 5; index++)
            printf("%d ", sel[index]);
        printf("\n");

        for (int i = 0; i <= 5; i++)
            printf("%d ", getnum[i]);
        printf("\n");

        for (int i = 0; i <= 5; i++)
        {
            for (int j = 0; j <= 5; j++)
            {
                if (sel[i] == getnum[j]) // 당첨번호랑 일치할경우 출력 , cnt+1
                {
                    cnt++;
                    printf("%d  당첨 ", getnum[j]);
                }
            }
        }
        printf("\n");
        money += cnt * batting;                     // 당첨금액은 batting금액 x 맞은개수
        printf("당첨 금액 : %d \n", cnt * batting); // 당첨금액 출력
        printf("\n");
        printf("다시할려면 아무키나 눌러주세요...");
        getch();       // 입력 기다림
        system("cls"); // 화면 지우기
    }
    return 0;
}

int *get_number()
{
    static int arr[6];
    int b = 0, flag;
    int i = 0;

    while (i != 6)
    {
        for (int j = 0; j < i; j++)
        {
            printf("%d : %d \n", j + 1, arr[j]);
        }
        printf("%d 번 : ", i + 1);
        while (1) //중복된 숫자가 있으면 다시 입력을 받기위해서 while문을 사용함
        {
            flag = 0; //중복된 숫자가 1인지 확인하기위한 flag
            scanf("%d", &b);
            for (int j = 0; j < i; j++) // 중복확인 시작
            {
                if (arr[j] == b) //중복된 숫자일경우 flag를 1로 만들어서 다시 입력받게함
                {
                    printf("중복된 숫자입니다. 다시 입력해주세요..\n");
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) // flag가 바뀌지 않았을경우에는
                           // arr[i]번째에 b를 넣어서 다음 입력을 받을수 있게함
            {
                arr[i] = b;
                break;
            }
        }
        i++;
        system("cls");
    }

    return arr;
}

//heap sort program
void heap_sort(int *b, int n)
{
    int k, t;
    for (k = n / 2; k >= 0; k--)
        heap(b, n, k);
    while (n > 0)
    {
        t = b[0];
        b[0] = b[n];
        b[n] = t;
        heap(b, --n, 0);
    }
}

void heap(int *b, int n, int k)
{
    int j, v;
    v = b[k];
    while (k <= n / 2)
    {
        j = k + k;
        if (j < n && b[j] < b[j + 1])
            j++;
        if (v >= b[j])
            break;
        b[k] = b[j];
        k = j;
    }
    b[k] = v;
}