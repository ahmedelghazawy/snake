
#include"cc215.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
char ch='!';

#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define UP_ARROW 72
#define DOWN_ARROW 80

struct location
{
	int x;
	int y;
	location()
	{
		x=getScreenWidth();
		y=getScreenHeight();
	}
};

struct body
{
	char b;
	int x,y;
	body* next;
	body* prev;
};
body* InsertBody(body* head)
{
	body* tmp;
	tmp=(body*) malloc(sizeof(body));
	tmp->b='0';
	body *it=head;
	while( it->next != NULL)
		it=it->next;
	it->next=tmp;
	tmp->prev=it;
	tmp->next=NULL;
	tmp->x=head->x;
	tmp->y=head->y;

	return head;
}

void drawBounds()
{
	
	location max;
	int i, j;
	for (i=0; i<=max.x; i++) //top margin
	{
		goto_xy(i, 0);
		printf("%c", 220);
	}
	for(i=0; i<max.x; i++) //bottom margin
	{
		goto_xy(i, max.y);
		printf("%c", 223);
	}
	for(j=1; j<max.y; j++) //leftmost margin
	{
		goto_xy(0, j);
		printf("%c", 221);
	}
	for(j=1; j<max.y; j++) //rightmost margin
	{
		goto_xy(max.x-1, j);
		printf("%c", 222);
	}
	
}
body *Movement( body *head)
{
	body *it=head;
	while(it->next!=NULL)
		it=it->next;
	goto_xy(it->x, it->y);
	printf(" ");
	
		while(it->prev!=NULL)
		{
			it->x=it->prev->x;
			it->y=it->prev->y;
			it=it->prev;
		}
		return head;
}
void Print( body* head, body *food)
{
	body *it=head;
	
		while(it != NULL)
		{
			goto_xy(it->x,it->y);
			printf("%c",it->b);
			it=it->next;
		}
			goto_xy(food->x, food->y);
			printf("%c", food->b);
}
bool SelfHit( body* head )
{
	if( head == NULL || head->next == NULL )
		return false;
	body* it = head;
	while( it!= NULL)
	{
		if(it->next == NULL)
			return false;
		it = it->next;
		if((it->y==head->y && it->x==head->x))
			return true;
	}
	return false;
}


void main()
{
	int x=40;
	int st=0;
	int factor=0,insertion=0,count=0;
	bool can=false;
	body* head, *food;
	head=(body*) malloc(sizeof(body));
	head->b='8';
	head->x=getScreenWidth()/2;
	head->y=getScreenHeight()/2;
	head->next=head->prev=NULL;

	food=(body*) malloc(sizeof (body*));
	food->b='#';
	food->next=food->prev=NULL;
	food->x=getRandomNumber(getScreenWidth());
	food->y=getRandomNumber(getScreenHeight());

	getch();
	body* it=head;
	for(int i=1; i<=5; i++)
	{
		head=InsertBody(head);
		it->next->y=head->y;
		it->next->x=head->x-i;
		it=it->next;
	}
	it=head;
	drawBounds();
	while(it != NULL)
	{
		goto_xy(it->x, it->y);
		printf("%c",it->b);
		it=it->next;
	}
	while(ch !='e')
	{
		char a=ch;
		if(kbhit())
			ch=getch();
			if(ch=='w' || ch==UP_ARROW)
			{	
				head=Movement(head);
				head->y--;
				Print(head,food);
			}
			else if(ch=='s' || ch==DOWN_ARROW)
			{
				head=Movement(head);
				head->y++;
				Print(head,food);	
			}
			else if(ch=='a' || ch==LEFT_ARROW)
			{
				head=Movement(head);
				head->x--;
				Print(head,food);
			}
			else if( ch=='d' || ch==RIGHT_ARROW)
			{
				head=Movement(head);
				head->x++;
				Print(head,food);
			}
			else if (ch=='e')
				break;
			else if (ch=='p')
				while(!kbhit())
					continue;
			else
				ch=a;
			
			if(food->x==head->x && food->y==head->y)
			{
				factor++;
				if(count<10)
					count++;
				else
					count+=(factor/5);
				st++;
				insertion=factor/10 +1;
				for(int i=1; i<=insertion;i++)
				{
 				head=InsertBody(head);
				it=head;
				while(it->next!=NULL)
					it=it->next;
				it->x=it->prev->x-(it->prev->prev->x-it->prev->x);
				it->y=it->prev->y-(it->prev->prev->y-it->prev->y);
				}
				food->x=getRandomNumber(getScreenWidth()-1);
				food->y=getRandomNumber(getScreenHeight()-1);
			}	
			if(st==2)
			{
				x--;
				st=0;
			}
			if(count>=100)
				break;
		if (head->x==getScreenWidth() || head->y==getScreenHeight() || head->x==0 || head->y==0)
			{
				getch();
				clearScreen();
				goto_xy( getScreenWidth()/2, getScreenHeight()/2);
				printf("WallHit\n");
				goto_xy( getScreenWidth()/2, getScreenHeight()/2+1);
				printf("Gameover Sucker\n");
				goto_xy(getScreenWidth()/2, getScreenHeight()/2+2);
				printf("Your Score = %d", count);
				getch();
				break;
			}
		can=SelfHit(head);
			if(can==true)
			{
				getch();
				clearScreen();
				goto_xy( getScreenWidth()/2, getScreenHeight()/2);
				printf("Selfhit\n");
				goto_xy( getScreenWidth()/2, getScreenHeight()/2+1);
				printf("Gameover Sucker\n");
				goto_xy(getScreenWidth()/2, getScreenHeight()/2+2);
				printf("Your Score = %d", count);
				getch();
				break;
			}
			Sleep(x);
		}
	if(count>=100)
	{
				clearScreen();
				goto_xy(getScreenWidth()/2, getScreenHeight()/2);
				printf("Your score = %d", count);
				goto_xy(getScreenWidth()/2, getScreenHeight()/2+2);
				printf("YOU WIN");
	}
	getch();
}
