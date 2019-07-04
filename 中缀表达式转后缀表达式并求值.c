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
    num.top=Maxlenth;/*����洢��������ջ�Ŀ�ջ��λ��*/
    Stack sign;
    sign.top=Maxlenth;/*����洢��������ջ�Ŀ�ջ��λ��*/
    Stack *N=&num;
    Stack *S=&sign;

    char c=' ';
    int i=0;
    char mid[Maxlenth]={'\0'};
    gets(mid);/*������׺���ʽ*/
    check(mid);/*�ж��Ƿ�Ϊ�Ϸ����룬�Ƿ�����ʱ�����˳�*/
    int j=0;
    
    /*�������ȼ����򽫲�������ջ��ջ����������ջʱ���ڲ������ÿո�������
      ���յĺ�׺���ʽ�����ڲ�����ջ�С�
    */
    for(i=0;i<strlen(mid);i++)
    {  //�ж�mid[i]�Ƿ�Ϊ��������һ���֣��������ֱ��ѹ�������ջ
        if( (mid[i]>='0'&&mid[i]<='9'))/**&&&&&&&&&&&&&&&&&&&&&&��֧��С������ʱע�͵�||mid[i]=='A'||mid[i]=='.'&&&&&&&&&&&&&&&&&&&&&&&&*/ 
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
                        Push(N,c); //���ո�ѹ�������ջ���������ڵ�����������
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
                        { //�������ȼ����ڻ����mid[i]�Ĳ�������������ջ��
                          //ֱ��ջ��Ԫ�����ȼ���mid[i]С����ջ��Ϊֹ
                            Push(N,c);
                            Push(N,Pop(S));
                        }
                        Push(N,c);
                        Push(S,mid[i]);
                    }
                    else
                    {
                        if(mid[i]==')')//����������ʱ��������ջ��������ջ��ֱ������������Ϊֹ
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
    //�Ѳ�����ջ��Ԫ�ص�����������ջ
    while(!Isempty(S))
    {
        Push(N,c);
        Push(N,Pop(S));
    }
    Print(N);/*��ӡ��׺���ʽ*/
    char Array[100];
    stackToArray(N,Array,100);/*����׺���ʽ��ջ��->ջ����˳����뵽Array������*/
    Calculate(Array,strlen(Array));/*�����׺���ʽ*/
    printf("\n������Ϊ(������λС��)��%lf\n",Calculate(Array,strlen(Array)));
}
/*��ջ*/
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
/*ѹջ*/
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
/*�ж�ջ�Ƿ�Ϊ��*/
int Isempty(Stack *S)
{
    if(S->top==Maxlenth)
    {
        return 1;
    }
    return 0;
}
/*����ջ��Ԫ��*/
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
/*��ջ��->ջ����˳���ӡջ*/
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
/*����׺���ʽ��ջ��->ջ����˳����뵽Array������*/
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
/*����ֵ*/
double Calculate(char *Array,int len)
{
  double result[10]={0};
  char Num[20]={'\0'};
  int Ntop=0,rtop=-1;
  int i=0;
  for(i=0;i<len;i++)
  {   //�Ӳ�����ջ��һ������ȡ����������ת����double����
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
        {  //���������Ĳ�������resulջ��������Ԫ�������㣬ջ��ָ���һ������������ջ��
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
/*�������
*/
void clean(char *A)
{
    int i=strlen(A);
    for(i=strlen(A);i>=1;i--)
    {
        A[i]='\0';
    }
}
/*���Ϸ���*/
void check(char *ch)
{
	int i=0;
	int Lcount=0,Rcount=0;
	int len=strlen(ch);
	if(ch[0]!='('&&ch[0]!='+'&&ch[0]!='-'&&!(ch[0]>='0'&&ch[0]<='9'))
	{
		printf("�Ƿ����룡\n");
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
				printf("�Ƿ����룡\n");
				exit(0);
			}
		}
		else if(ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/'||ch[i]=='%'||ch[i]=='^')
		{
			if(ch[i+1]!='('&&!(ch[i+1]>='0'&&ch[i+1]<='9'))
			{
				printf("�Ƿ����룡\n");
				exit(0);
			}
		}
		
		else if(ch[i]=='(')
		{
			if(ch[i+1]!='+'&&ch[i+1]!='-'&&!(ch[i+1]>='0'&&ch[i+1]<='9')&&ch[i+1]!='(')
			{
				printf("�Ƿ����룡\n");
				exit(0);
			}
			Lcount++;
		}
		else if(ch[i]==')')
		{
			if(ch[i+1]!='+'&&ch[i+1]!='-'&&ch[i+1]!='*'&&ch[i+1]!='/'&&ch[i+1]!='%'&&ch[i+1]!='^'&&ch[i+1]!=')')
			{
				printf("�Ƿ����룡\n");
				exit(0);
			}
			Rcount++;
		}
		else
		{
			printf("�Ƿ����룡\n");
			exit(0);
		}
	}
	if(ch[i]==')')
	{
		Rcount++;
	}
	if(Lcount!=Rcount)
	{
		printf("�Ƿ����룡\n");
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
        printf("�Ƿ����룡\n");
        exit(0);
    }
}
