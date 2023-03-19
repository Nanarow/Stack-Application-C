#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nd
{
  char value;
  struct nd *next;
} Node;

Node *top = NULL;
int size = 0;

void push(char);
char pop();
void clearStack();
char getTop();
void displayStack();

void display(char);

void infixToPostfix(char[]);
char *getStackItems(); // return list item in stack
int getPri(char);      // return priority

void postfixToInfix(char[]);
void getVarSet(char *);                // return variable set
void addVarSet(char *, int *, char *); // add variable set
void checkVarSet(char);                // check varible set

void reverse(char *);

int main(void)
{

  char eqn1[] = "A+B*C/D";
  char eqn2[] = "(A+B)/C*D-E";
  char eqn3[] = "A*(B+C^D)-E^F*(G/H)";

  char ex1[] = "(A+B)*C/D";
  char ex2[] = "A/(C-D)+D*E";
  char ex3[] = "A-(B-C)*D/E";
  char ex4[] = "H+(J-K)*I/S";
  char ex5[] = "f*(g-h)+(j/k)";
  char ex6[] = "A+B*(C^D-E)/F*G-H/I";

  char myEqn1[] = "A*(B+C)-D*(E+F/(G-H^I*J)-K*L)/M";
  char myEqn2[] = "(N*0)*(P+Q)^(R*(S+T)/(V^W)-Y/Z)";
  char gg[] = "(A*B)+((C-D)^6/E)+F*4-z";
  char test[] = "(A-B^4*((C+5)/p))+(D-E/9)";

  char postfixEqn[] = "ABC+*DEFGHI^J*-/KL*-+*M/-";
  char infixEqn[] = "A*(B+C)-D*(E+F/(G-H^I*J)-K*L)/M";
  
  infixToPostfix(infixEqn);
  postfixToInfix(postfixEqn);

  return 0;
}

void push(char c)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->value = c;
  newNode->next = top;
  top = newNode;
  size++;
}

char pop()
{
  char c;
  Node *current = top;
  c = current->value;
  top = top->next;
  free(current);
  size--;
  return c;
}

char getTop() { return (top == NULL) ? NULL : top->value; }

void clearStack()
{
  Node *delNode;
  while (top != NULL)
  {
    delNode = top;
    top = top->next;
    free(delNode);
    size--;
  }
}

void display(char c) { printf("%c \n", c); }

void displayStack()
{
  Node *current = top;
  if (top == NULL)
  {
    printf("Queue is empty!");
    return;
  }
  while (current != NULL)
  {
    printf("%c --> ", current->value);
    current = current->next;
  }
}

int getPri(char c)
{
  int pri = (c == '^')               ? 3
            : (c == '*' || c == '/') ? 2
            : (c == '+' || c == '-') ? 1
                                     : 0;
  return pri;
}

void infixToPostfix(char eqn[])
{
  printf("\n< Infix To Postfix >  Equation: %s \n", eqn);
  char output[strlen(eqn)];
  int idx = 0;
  printf("%-8s%-10s%-12s%-20s\n", "Step", "Symbol", "Stack", "Output");

  for (int i = 0; i <= strlen(eqn); i++)
  {
    char c = eqn[i];

    if (i != strlen(eqn))
    { // check round
      if (isdigit(c) || isalpha(c))
      { // check digit and alpha
        output[idx++] = eqn[i];
      }
      else
      {
        if (top == NULL || c == '(')
        { // check top and (
          push(c);
        }
        else
        {
          if (c == ')')
          { // chech ()
            while (getTop() != '(')
            {
              output[idx++] = pop();
            }
            pop();
          }
          else
          {
            if (getPri(getTop()) >= getPri(c))
            {
              output[idx++] = pop();
            }
            push(c);
          }
        }
      }
    }
    else
    {
      while (top != NULL)
      {
        output[idx++] = pop();
      }
    }

    output[idx] = '\0';
    printf("  %-8d%-10c%-12s%-20s\n", (i + 1), (c == '\0') ? ' ' : c,getStackItems(), output);
  }
}

char *getStackItems()
{
  if (size == 0)
  {
    return "null";
  }
  char *str = malloc(size * sizeof(char));
  char items[size];
  int idx = size;
  Node *curr = top;
  while (curr != NULL)
  {
    str[--idx] = curr->value;
    curr = curr->next;
  }
  str[size] = '\0';
  return str;
}

void postfixToInfix(char pfx[])
{

  printf("\n< Postfix To Result >  Equation: %s\n", pfx);
  printf("%-8s%-10s%-12s\n", "Step", "Symbol", "Stack");
  for (int i = 0; i < strlen(pfx); i++)
  {

    if (isdigit(pfx[i]) || isalpha(pfx[i]))
    {
      push(pfx[i]);
    }
    else
    {
      checkVarSet(pfx[i]);
    }
    printf("  %-8d%-10c%-12s\n", (i + 1), pfx[i], getStackItems());
  }
}

void checkVarSet(char op)
{
  char var2 = pop(), var1;
  char temp[100];
  int idx = 0;

  temp[idx++] = '(';
  if (var2 != ')')
  {
    var1 = pop();
    if (var1 != ')')
    {
      temp[idx++] = var1;
      // printf("%-20c",var1);
    }
    else
    {
      char set1[100];
      getVarSet(set1);
      addVarSet(temp, &idx, set1);
    }
    temp[idx++] = op;
    temp[idx++] = var2;
    // printf("%-10c",var2);
    temp[idx++] = ')';
  }
  else
  {
    char set2[100];
    getVarSet(set2);
    var1 = pop();
    if (var1 != ')')
    {
      temp[idx++] = var1;
    }
    else
    {
      char set1[100];
      getVarSet(set1);
      addVarSet(temp, &idx, set1);
    }
    temp[idx++] = op;
    addVarSet(temp, &idx, set2);
    temp[idx++] = ')';
  }

  temp[idx] = '\0';
  for (int i = 0; i < idx; i++)
  {
    push(temp[i]);
  }
}

void getVarSet(char *set)
{
  int bracket = 1, idx = 0;
  set[idx++] = ')';
  while (getTop() != '(' || bracket != 1)
  {
    set[idx++] = pop();
    if (set[idx - 1] == ')')
    {
      bracket++;
    }
    else if (set[idx - 1] == '(')
    {
      bracket--;
    }
  }
  set[idx++] = pop();
  set[idx] = '\0';
}

void addVarSet(char *arr, int *ptrIdx, char *str)
{
  char set[strlen(str)];
  strcpy(set, str);
  for (int j = strlen(set) - 1; j > -1; j--)
  {
    int idx = *ptrIdx;
    arr[idx] = set[j];
    *ptrIdx = idx + 1;
  }
}

void reverse(char *str2)
{
  char str[strlen(str2)], rev[strlen(str2)];
  strcpy(str, str2);
  int strI = 0, revI = strlen(str2) - 1;
  rev[0] = '\0';
  while (revI >= 0)
  {
    rev[revI--] = str[strI++];
  }
  printf("%-20s", rev);
}
