#include <stdio.h>

#define bool int
#define true 1
#define false 0

char seats[15][30] = {};
double prices[15] = {0};
int sold = 0;
int avail = 15*30;
double ticketSale = 0;

void menu();
void display();
void clear();
void getPrices();
void getTotal();
void buyTix();
void seatsByRow();
int validateInt(char msg[], int min, int max);

int main() 
{
  menu();
  return 0;
}

void menu()
{
  clear(); //fills array with values for empty seats to start
  char choice = '0';
  bool ready = false;
  while(choice!='6')
  {
    printf("\n\nTheater seating menu:\n1 - Enter row prices\n2 - View Available Seats\n3 - Buy ticket(s)\n4 - View total ticket sales\n5 - Clear theater seats\n6 - Exit\n-->");
    choice = getchar();
    scanf("%*c");
    switch(choice)
    {
      case '1':
        getPrices();
        ready = true;
        break;
      case '2':
        display();
        printf("\n\n%d seats have been sold. \nThere are %d seats left available.", sold, avail);
        seatsByRow();
        break;
      case '3':
        if(ready == false)
          printf("Cannot buy tickets yet! Enter row prices first.\n");
        else
          buyTix();
        break;
      case '4':
        getTotal();
        break;
      case '5':
        clear();
        printf("All seats are now empty.\n");
        break;
      case '6':
        printf("\nExiting program...");
        break;
      default:
        printf("Invalid choice.\n");
        break;
    }
  }
}

void clear() //used to empty all seats in theater
{
  for(int r=0;r<15;r++)
  {
    for(int c=0;c<30;c++)
    {
      seats[r][c] = '-';
    }
  }
}

void getTotal()
{
  printf("Total ticket sales: $%.2f", ticketSale);
}

void display()
{
  printf("Seats:\nColumn:\t123456789012345678901234567890\n");
  for(int r=0;r<15;r++)
  {
    printf("\nRow %d:\t", r+1);
    for(int c=0;c<30;c++)
    {
      printf("%c",seats[r][c]);
    }
  }
}

void getPrices()
{
  double p;
  bool valid=false;
  printf("\n\nEnter ticket prices per row:\n");
  for(int i=0;i<15;i++)
  {
    p = 0;
    while(valid==false)
    {
      printf("Price for Row %d: $", i+1);
      if(1 == scanf("%lf", &p) && p>0)
        valid = true;
      else
        printf("Invalid input.\n");
    }
    prices[i] = p;
    valid = false;
  }
  printf("\nAll row ticket prices entered!");
  scanf("%*c");
}

void buyTix()
{
  display();
  double cart = 0;
  int tix = 0;
  bool taken = true;
  tix = validateInt("\nEnter number of tickets to purchase: ", 0, avail);
  for(int i = 0;i<tix;i++)
  {
    int row = 0;
    int col = 0;
    while(taken==true)
    {
      row = validateInt("\nEnter desired row: ", 0, 30) - 1;
      col = validateInt("\nEnter desired column: ", 0, 30) - 1;
      if(seats[row][col]=='-')
        taken = false;
      else
        printf("Seat taken.\n");
    }
    seats[row][col] = '*';
    sold++;
    avail--;
    cart+=prices[row];
    taken = true;
  }
  printf("\nYour total is: $%.2f (press enter to accept)", cart);
  ticketSale+=cart;
  scanf("%*c");
}

int validateInt(char msg[], int min, int max) //takes in console input and parses it to ensure it is an int not string, 
                                              //also checks min/max parameters to ensure value is acceptable range
                                              //keeps looping until an acceptable value is entered
{
  bool valid = false;
  int i = 0;
  while(valid==false)
  {
    printf("%s", msg);
    if(1 == scanf("%d", &i) && i>min && i<=max)
      valid = true;
    else
      printf("Invalid input.\n");
  }
  scanf("%*c");
  return i;
}

void seatsByRow()
{
  int total = 0;
  for(int r=0;r<15;r++)
  {
    for(int c=0;c<30;c++)
    {
      if(seats[r][c]=='-')
        total++;      
    }
    printf("\nRow %d: %d seats left", r+1, total);
    total = 0;
  }
}
