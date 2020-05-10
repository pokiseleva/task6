#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
char* getline()
{
    char* line = (char*)malloc(1024), *linep = line;
    int lenmax = 100, len = lenmax;
    int c;
    if (!line)
        return NULL;
    while (1)
    {
        c = fgetc(stdin);
        if (c == '\n' && linep == line)
            continue;
        if (c == EOF)
            break;
        if (--len == 0)
        {
            len = lenmax;
            char* linen = (char*)realloc(linep, lenmax *= 2);
            //
            if (!linen)
            {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }
        if ((*line++ = c) == '\n')
            break;
    }
    *(line-1) = '\0';
    *line = '\0';
    return linep;
}

int isspace(char x) {
    return (x <= 32) || x == ' ' || x <= '\t' || x == '\0';
}

int isdigit(char x) {
    return (x >= '0' && x <= '9');
}
int _isopsym(char x) {
    return x == '*' || x == '/' || x == '+' || x == '-';
}
int isopsym(const char* p, int i) {
    char x = p[i];
    if (x == '-'&&i==0||(x == '-'&&i!=0&&p[i-1]=='('))
    {
        if (isdigit(p[i+1]))
            return false;
    }
    return x == '*' || x == '/' || x == '+' || x == '-';}


int isnumber(const char* p, int i) {
    char x = p[i];
    return !( isspace(x) || isopsym(p,i) || x == '=' || x == '(' || x == ')');
}

double calc(char* s, int r, int* l)
{
    char op, t;
    double x1, x2, x0;
    while (isspace(s[r]) || s[r] == '=')
        r--;
    if (!isopsym(s,r))
    {
        *l = r;
        while ( *l >= 0 && (!isspace(s[*l])) )
            (*l)--;
        (*l)++;
        t = s[r+1], s[r+1] = '\0';
        sscanf(s + (*l), "%lf", &x0);
        s[r+1] = t;
        return x0;
    }
    op = s[r];
 x2 = calc(s, r-1, l);
   x1 = calc(s, (*l)-1, l);
    if (op == '+')
    {
        return x1 + x2;
    }
    else if (op == '-')
    {
        return x1 - x2;
    }
    else if (op == '*')
    {
        return x1 * x2;
    }
    else if (op == '/')
    {if (x2 == 0){

                cout<<endl<<"!Error!"<<endl;

                exit(1);

            }
        return x1 / x2;
    }
    return 0;
}


struct st
{
    char c;
    struct st *next;
};
struct st *push(struct st *, char);
char DEL(struct st **);
int PRIOR(char);
int i;
int main(void)
{
    char EMPT[] = "";
 int n=0;
 int str2[500];
char *st1[500];
    st1[0] = EMPT;
char u[1000];
    struct st *OPERS=NULL;
    // char a[80];
    char *a;
    char outstring[1000];
    int p,l,k, point;
    do
    {
        puts("enter the expression(in the end'='):");
        fflush(stdin);
        a = getline(); // fgets(a);
       strcpy (u, a);
        k=point=0;
        char * pch = strtok (u," *-/+");
int j;i=0;

               printf("\n");
        while(a[k]!='\0'&&a[k]!='=')
        {

            if(a[k]==')')
            {

                while((OPERS->c)!='(')

                    outstring[point++]=DEL(&OPERS);
                DEL(&OPERS);
            }

            if (isnumber(a,k)||((a[k]=='+'||a[k]=='-')&&k!=0&&a[k-1]=='e')) // || (isdigit(a[k]) && k != 1 && a[k-2]=='e'))
              outstring[point++]=a[k];

             if (( isnumber(a,k-1) && k != 0 && (!isnumber(a,k)))&&(k!=0&&a[k-1]!='e'&&!isnumber(a,k))) // && a[k] != '.'
             {
                outstring[point++]=' ';
             }

            if(a[k]=='(')

                OPERS=push(OPERS, '(');

            if (k!=0&&a[k-1]!='e'){

                if (isopsym(a, k))
                {
                    if(OPERS==NULL)
                        OPERS=push(OPERS, a[k]);
                    else
                    if(PRIOR(OPERS->c)<PRIOR(a[k]))
                        OPERS=push(OPERS, a[k]);
                    else
                    {
                        while((OPERS!=NULL)&&(PRIOR(OPERS->c)>=PRIOR(a[k])))
                        {
                          outstring[point++]=' ';
                             outstring[point++]=DEL(&OPERS);
                            outstring[point++]=' ';
                        }
                        OPERS=push(OPERS, a[k]);
                    }
                }
            }
            k++;


        }

        while(OPERS!=NULL)
        {
               outstring[point++]=' ';
             outstring[point++]=DEL(&OPERS);
            outstring[point++]=' ';
        }

        outstring[point++] = '=';
        outstring[point] = '\0';
        cout<<endl<< outstring<<endl;

        int l;
        double y = calc(outstring, point-1, &l);
        printf("value = %.3lf", y);
    }
    while(getchar()!='n');


}

struct st *push(struct st *HEAD, char a)
{
    struct st *PTR;

    if((PTR=(st*)malloc(sizeof(struct st)))==NULL)
    {
        puts("Error");
        exit(-1);
    }
    PTR->c=a;
    PTR->next=HEAD;
    return PTR;
}


char DEL(struct st **HEAD)
{
    struct st *PTR;
    char a;
    if(*HEAD==NULL) return '\0';
    PTR=*HEAD;
    a=PTR->c;
    *HEAD=PTR->next;
    free(PTR);
    return a;
}


int PRIOR(char a)
{
    switch(a)
    {
    case '*':
    case '/':
        return 3;

    case '-':
    case '+':
        return 2;

    case '(':
        return 1;
    }
}
