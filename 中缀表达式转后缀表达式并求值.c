#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Maxlenth 100

typedef struct Stack{
int top;
char s[Maxlenth];
}Stack;

char Pop(Stack *S);
char top(Stack *S);
int Isempty(Stack *S);
double Calculate(char *Array,int len);
void stackToArray(Stack *S,char *ch,int len);
void Push(Stack *S,char pu);
void Print(Stack *S);
void clean(char *A);
void check(char *ch);


int main()
{
    Stack num;
    num.top=Maxlenth;/*定义存储操作数的栈的空栈底位置*/
    Stack sign;
    sign.top=Maxlenth;/*定义存储操作符的栈的空栈底位置*/
    Stack *N=&num;
    Stack *S=&sign;

    char c=' ';
    int i=0;
    char mid[Maxlenth]={'\0'};
    gets(mid);/*读入中缀表达式*/
    check(mid);/*判断是否为合法输入，非法输入时程序退出*/
    int j=0;
    
    /*按照优先级规则将操作符进栈出栈，操作数入栈时相邻操作数用空格间隔开。
      最终的后缀表达式保存在操作数栈中。
    */
    for(i=0;i<strlen(mid);i++)
    {  //判断mid[i]是否为操作数的一部分，如果是则直接压入操作数栈
        if( (mid[i]>='0'&&mid[i]<='9'))/**&&&&&&&&&&&&&&&&&&&&&&不支持小数或负数时注释掉||mid[i]=='A'||mid[i]=='.'&&&&&&&&&&&&&&&&&&&&&&&&*/ 
        {
            Push(N,mid[i]);
        }
        else
        {
            if(mid[i]=='(')
            {
                Push(S,mid[i]);
            }
            else
            {
                if(mid[i]=='+'||mid[i]=='-')
                {
                    while(top(S)!='('&&(!Isempty(S)))
                    {
                        Push(N,c); //将空格压入操作数栈以区分相邻的两个操作数
                        Push(N,Pop(S));
                    }
                    Push(N,c);
                    Push(S,mid[i]);
                }
                else
                {
                    if(mid[i]=='*'||mid[i]=='/'||mid[i]=='%')
                    {
                        while((top(S)=='*'||top(S)=='/'||top(S)=='%')&&(!Isempty(S)) )
                        { //弹出优先级大于或等于mid[i]的操作符到操作数栈，
                          //直到栈顶元素优先级比mid[i]小或者栈空为止
                            Push(N,c);
                            Push(N,Pop(S));
                        }
                        Push(N,c);
                        Push(S,mid[i]);
                    }
                    else
                    {
                        if(mid[i]==')')//遇到左括号时弹操作符栈到操作数栈，直到弹出左括号为止
                        {
                            while(top(S)!='(' )
                            {
                                Push(N,c);
                                Push(N,Pop(S));
                            }
                            Push(N,c);
                            Pop(S);
                        }
                    }
                }
            }
        }
    }
    //把操作符栈的元素弹出到操作数栈
    while(!Isempty(S))
    {
        Push(N,c);
        Push(N,Pop(S));
    }
    Print(N);/*打印后缀表达式*/
    char Array[100];
    stackToArray(N,Array,100);/*将后缀表达式按栈底->栈顶的顺序存入到Array数组中*/
    Calculate(Array,strlen(Array));/*计算后缀表达式*/
    printf("\n计算结果为(保留六位小数)：%lf\n",Calculate(Array,strlen(Array)));
}
/*弹栈*/
char Pop(Stack *S)
{
    if(S->top==Maxlenth)
    {
      printf("Stack is empty!\n");
      exit(1);
    }
    char po;
    po=S->s[S->top];
    S->top++;
    return po;
}
/*压栈*/
void Push(Stack *S,char pu)
{
    if(S->top==0)
    {
        printf("Stack is full!\n");
        exit(1);
    }
    S->top--;
    S->s[S->top]=pu;
}
/*判断栈是否为空*/
int Isempty(Stack *S)
{
    if(S->top==Maxlenth)
    {
        return 1;
    }
    return 0;
}
/*返回栈顶元素*/
char top(Stack *S)
{
    if(Isempty(S))
    {
        return '\0';
    }
    else
    {
        return S->s[S->top];
    }
}
/*按栈底->栈顶的顺序打印栈*/
void Print(Stack *S)
{
    int i=0;
   if(S->top>=Maxlenth)
   {
       printf("Stack is empty!\n");
   }
   for(i=Maxlenth-1;i>=S->top;i--)
   {
       printf("%c",S->s[i]);
   }
}
/*将后缀表达式按栈底->栈顶的顺序存入到Array数组中*/
void stackToArray(Stack *S,char *ch,int len)
{
    int i=0,j=Maxlenth-1;
    while(j>=S->top&&i<len)
    {
        ch[i]=S->s[j];
        i++;
        j--;
    }
    ch[i]='\0';
}
/*计算值*/
double Calculate(char *Array,int len)
{
  double result[10]={0};
  char Num[20]={'\0'};
  int Ntop=0,rtop=-1;
  int i=0;
  for(i=0;i<len;i++)
  {   //从操作数栈中一个个读取出操作数并转换成double类型
      if((Array[i]=='-'||Array[i]=='+')&&(i<len-1)&&(Array[i+1]>='0'&&Array[i]<='9'))
      {
          for(Ntop=0;Ntop<20&&Array[Ntop+i]!=' ';Ntop++)
          {
              Num[Ntop]=Array[Ntop+i];
          }
          rtop++;
          result[rtop]=atof(Num);
          i=Ntop+i;
          clean(Num);
          Ntop=0;
          continue;
      }
      else {
         if(Array[i]>='0'&&Array[i]<='9')
         {
              for(Ntop=0;Ntop<20&&Array[Ntop+i]!=' ';Ntop++)
          {
              Num[Ntop]=Array[Ntop+i];
          }
          rtop++;
          result[rtop]=atof(Num);
          i=Ntop+i;
          clean(Num);
          Ntop=0;
          continue;
         }
        else
        {  //根据遇到的操作符对resul栈顶的两个元素做运算，栈顶指针减一，运算结果存入栈顶
            switch(Array[i])
            {
            case '+':
                result[rtop-1]=result[rtop]+result[rtop-1];
                rtop--;
                break;
            case '-':
                 result[rtop-1]=result[rtop-1]-result[rtop];
                rtop--;
                break;
            case '*':
                 result[rtop-1]=result[rtop]*result[rtop-1];
                rtop--;
                break;
            case '/':
                 result[rtop-1]=result[rtop-1]/result[rtop];
                rtop--;
                break;
            case '%':
                 result[rtop-1]=(int)result[rtop-1]%(int)result[rtop];
                rtop--;
                break;
            default:
					;
            }
        }
      }
  }
  return result[rtop];
}
/*清空数组
*/
void clean(char *A)
{
    int i=strlen(A);
    for(i=strlen(A);i>=1;i--)
    {
        A[i]='\0';
    }
}
/*检查合法性*/
void check(char *ch)
{
	int i=0;
	int Lcount=0,Rcount=0;
	int len=strlen(ch);
	if(ch[0]!='('&&ch[0]!='+'&&ch[0]!='-'&&!(ch[0]>='0'&&ch[0]<='9'))
	{
		printf("非法输入！\n");
		exit(0);
	}
	if(ch[0]=='(')
	{
		Lcount++;
	}

	for(i=1;i<len-1;i++)
	{
		if(ch[i]>='0'&&ch[i]<='9')
		{
			if(ch[i+1]!='+'&&ch[i+1]!='-'&&ch[i+1]!='*'&&ch[i+1]!='/'&&ch[i+1]!='%'&&ch[i+1]!='^'&&!(ch[i]>='0'&&ch[i]<='9')&&ch[i+1]!='.')
			{
				printf("非法输入！\n");
				exit(0);
			}
		}
		else if(ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/'||ch[i]=='%'||ch[i]=='^')
		{
			if(ch[i+1]!='('&&!(ch[i+1]>='0'&&ch[i+1]<='9'))
			{
				printf("非法输入！\n");
				exit(0);
			}
		}
		
		else if(ch[i]=='(')
		{
			if(ch[i+1]!='+'&&ch[i+1]!='-'&&!(ch[i+1]>='0'&&ch[i+1]<='9')&&ch[i+1]!='(')
			{
				printf("非法输入！\n");
				exit(0);
			}
			Lcount++;
		}
		else if(ch[i]==')')
		{
			if(ch[i+1]!='+'&&ch[i+1]!='-'&&ch[i+1]!='*'&&ch[i+1]!='/'&&ch[i+1]!='%'&&ch[i+1]!='^'&&ch[i+1]!=')')
			{
				printf("非法输入！\n");
				exit(0);
			}
			Rcount++;
		}
		else
		{
			printf("非法输入！\n");
			exit(0);
		}
	}
	if(ch[i]==')')
	{
		Rcount++;
	}
	if(Lcount!=Rcount)
	{
		printf("非法输入！\n");
		exit(0);
	}
    if(ch[0]=='-'&&ch[1]=='(')
    {

        char ch1[Maxlenth]={'\0'};
        ch1[0]='0';
        ch=strcpy(ch,strcat(ch1,ch));
    }
    if((ch[0]=='+'||ch[0]=='-')&&len>=2&&!((ch[1]>='0'&&ch[1]<='9')||(ch[1]=='(')))
    {
        printf("非法输入！\n");
        exit(0);
    }
}
