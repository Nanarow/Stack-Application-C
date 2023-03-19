# Stack-Application-C
stack c implementation , stack application infix to postfix and postfix to infix

## Installation

```bash
git clone https://github.com/Nanarow/Stack-Application-C.git
```

## Usage
run **`main.exe`**
```bash
main.exe
```

## Example
use **`infixToPostfix()`** function to convert infix expression to postfix expression 
```c
int  main(void)
{
	char infixEqn[]  =  "A*(B+C)-D*(E+F/(G-H^I*J)-K*L)/M";
	infixToPostfix(infixEqn);
	
	return  0;
}
```
**output**
```
< Infix To Postfix >  Equation: A*(B+C)-D*(E+F/(G-H^I*J)-K*L)/M
Step    Symbol    Stack       Output
  1       A         null        A
  2       *         *           A
  3       (         *(          A
  4       B         *(          AB
  5       +         *(+         AB
  6       C         *(+         ABC
  7       )         *           ABC+
  8       -         -           ABC+*
  9       D         -           ABC+*D
  10      *         -*          ABC+*D
  11      (         -*(         ABC+*D
  12      E         -*(         ABC+*DE
  13      +         -*(+        ABC+*DE
  14      F         -*(+        ABC+*DEF
  15      /         -*(+/       ABC+*DEF
  16      (         -*(+/(      ABC+*DEF
  17      G         -*(+/(      ABC+*DEFG
  18      -         -*(+/(-     ABC+*DEFG
  19      H         -*(+/(-     ABC+*DEFGH          
  20      ^         -*(+/(-^    ABC+*DEFGH
  21      I         -*(+/(-^    ABC+*DEFGHI
  22      *         -*(+/(-*    ABC+*DEFGHI^
  23      J         -*(+/(-*    ABC+*DEFGHI^J
  24      )         -*(+/       ABC+*DEFGHI^J*-
  25      -         -*(+-       ABC+*DEFGHI^J*-/
  26      K         -*(+-       ABC+*DEFGHI^J*-/K
  27      *         -*(+-*      ABC+*DEFGHI^J*-/K
  28      L         -*(+-*      ABC+*DEFGHI^J*-/KL
  29      )         -*          ABC+*DEFGHI^J*-/KL*-+
  30      /         -/          ABC+*DEFGHI^J*-/KL*-+*
  31      M         -/          ABC+*DEFGHI^J*-/KL*-+*M
  32                null        ABC+*DEFGHI^J*-/KL*-+*M/-
```
use **`postfixToInfix()`** function to convert  postfix expression to infix expression
```c
int  main(void)
{
	char postfixEqn[]  =  "ABC+*DEFGHI^J*-/KL*-+*M/-";
	postfixToInfix(postfixEqn);
	
	return  0;
}
```
**output**
```
< Postfix To Result >  Equation: ABC+*DEFGHI^J*-/KL*-+*M/-
Step    Symbol    Stack
  1       A         A
  2       B         AB
  3       C         ABC
  4       +         A(B+C)
  5       *         (A*(B+C))
  6       D         (A*(B+C))D
  7       E         (A*(B+C))DE
  8       F         (A*(B+C))DEF
  9       G         (A*(B+C))DEFG
  10      H         (A*(B+C))DEFGH
  11      I         (A*(B+C))DEFGHI
  12      ^         (A*(B+C))DEFG(H^I)
  13      J         (A*(B+C))DEFG(H^I)J
  14      *         (A*(B+C))DEFG((H^I)*J)
  15      -         (A*(B+C))DEF(G-((H^I)*J))
  16      /         (A*(B+C))DE(F/(G-((H^I)*J)))
  17      K         (A*(B+C))DE(F/(G-((H^I)*J)))K
  18      L         (A*(B+C))DE(F/(G-((H^I)*J)))KL
  19      *         (A*(B+C))DE(F/(G-((H^I)*J)))(K*L)
  20      -         (A*(B+C))DE((F/(G-((H^I)*J)))-(K*L))
  21      +         (A*(B+C))D(E+((F/(G-((H^I)*J)))-(K*L)))
  22      *         (A*(B+C))(D*(E+((F/(G-((H^I)*J)))-(K*L))))
  23      M         (A*(B+C))(D*(E+((F/(G-((H^I)*J)))-(K*L))))M
  24      /         (A*(B+C))((D*(E+((F/(G-((H^I)*J)))-(K*L))))/M)
  25      -         ((A*(B+C))-((D*(E+((F/(G-((H^I)*J)))-(K*L))))/M))
```
> **Both functions** will show you the conversion steps.
