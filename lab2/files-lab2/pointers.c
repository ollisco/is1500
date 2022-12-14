// Author Olle Jernström

#include <stdio.h>
#include <string.h>

char *text1 = "This is a string.";
char *text2 = "Yet another thing.";
int count = 0;

int *list1[20];
int *list2[20];

void printlist(const int *lst)
{
  printf("ASCII codes and corresponding characters.\n");
  while (*lst != 0)
  {
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char *c)
{
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c, (int)*(c + 1), (int)*(c + 2), (int)*(c + 3));
}

void copycodes(char *text, int *list)
{
  // loop could also be while text[i] != '\0'
  for (int i = 0; i < strlen(text); i++)
  {
    int hex = (int)(*(text + i));
    *(list + i) = hex;
    count++;
  }
}

void work()
{
  copycodes(text1, list1);
  copycodes(text2, list2);
}

int main(void)
{
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char *)&count);
}
