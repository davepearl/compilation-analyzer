# 1.Lexicon Analyzer
## 1.Design requirements
One of the keys to lexical analysis is how to identify the types of words, especially in the face of identifiers and reserved words with the same definition form and exact same structure, and how to correctly solve the recognition and processing of them, which is an important task in lexical analysis. Since we have fewer words in the program statement, we ignore the word input error check in the lexical analysis stage, and focus the compiler on the intermediate code generation stage. The function of the lexer is to input the source program and output the word symbols.
## 2.Key steps
Design the scaner() function.
We need to identify and analyze five kinds of word symbols, and here we divide the word symbols into three major parts for recognition. First, it determines whether a character is a keyword or identifier and compares it with a defined keyword to determine whether it is a keyword or identifier, then it recognizes the number, and finally it determines the other characters, which are recognized by the defined judgment one by one, so that all the characters are recognized.
   The selection structure (if, else if, else) is used to classify the characters to be recognized, and the recognized strings are processed separately in the struct. The scaner() function also has the word category and the property of the word as the return value, so that the function communicates with the program to achieve the purpose of generating a binad.
   ```
   if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) 
    {
        m=0;
		while(1){
			if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				token[m++]=ch;
				ch=prog[p++];

			}else{
				p--;
				break;
			}
		}

        token[m]='\0';

		syn=0;

		for(n=0;n<8;n++){

			if (strcmp(token, rwtab1[n]) == 0)
			{
				syn = 2;
				break;
			}
			 
		}	
		for(n=0;n<10;n++){
		
		if (strcmp(token, rwtab[n]) == 0) {
				syn = 1;
				break;
			}
	}
		if(!syn)syn=2;	


    }
   ```
   ```
   else if (ch >= '0' && ch <= '9')
    {
       sum=0;
         
        syn = 3;
		while(1){
			if(ch >= '0' && ch <= '9') {
				sum*=10;
				sum+=ch -'0';
                ch=prog[p++];
			}else{
				p--;
				break;
			}
		}

        
    }
```
```
else switch (ch)   //其他字符 
	{
		case'<':m = 0; token[m++] = ch;
				ch = prog[p++];
				if (ch == '>')
				{
					syn = 4;
					token[m++] = ch;
				}
				else if (ch == '=')
				{
					syn = 4;
					token[m++] = ch;
				}
				else if (ch == '<')
				{
					syn = 4;
					token[m++] = ch;
				}
					else
					{
						syn = 4;
						p--;
					}
					break;
			case'>':m = 0; token[m++] = ch;
					ch = prog[p++];
					if (ch == '=')
					{
						syn = 4;
						token[m++] = ch;
					}
					else if (ch == '>')
				{
					syn = 4;
					token[m++] = ch;
				}
					else
					{
						syn = 4;
						p--;
					}
					break;
			case':':m = 0; token[m++] = ch;
					ch = prog[p++];
					if (ch == '=')
					{
						syn = 4;
						token[m++] = ch;
					}
					else
					{
						syn = 4;
						p--;
					}
					break;
			case'/':m = 0; token[m++] = ch;
					ch = prog[p++];
					if (ch == '/')
					{
						syn = 5;
						token[m++] = ch;
					}
					else
					{
						syn = 4;
						p--;
					}
					break;
			case'*':syn = 4; token[0] = ch; break;
			case'+':syn = 4; token[0] = ch; break;
			case'-':syn = 4; token[0] = ch; break;
			case'=':syn = 4; token[0] = ch; break;
			case';':syn = 5; token[0] = ch; break;
			case',':syn = 5; token[0] = ch; break;
			case'(':syn = 5; token[0] = ch; break;
			case')':syn = 5; token[0] = ch; break;
			case'{':syn = 5; token[0] = ch; break;
			case'}':syn = 5; token[0] = ch; break;
			case'"':syn = 5; token[0] = ch; break;
			case'#':syn = 0; token[0] = ch; break;
			case'\n':syn = -2; break;
			default: syn = -1; break;
	}

}

```
Design the main() function
The symbol of the source program is read in turn, and the words of the source program are segmented and recognized until the end of the source program. For the correct word, it is stored in the symbol table in the form of < symbol code, value > according to its species. Mishandling of incorrect words.
Load the input program to be analyzed as the content of the character array, call the scaner() function on the read character array, and choose different ways to print the binary according to the different binales, until the scaner() function scans the "#" program terminator and terminates the program. The main() function needs to contain error handling, which is represented as "Error in row + digit".
```
int main()
{
	p = 0;
	row = 1;
	cout << "Please input string:" << endl;
	do
	{
	cin.get(ch);
	prog[p++] = ch;
	} while (ch != '#');
	p=0;
    do{
      scaner();
      switch (syn)
      {
		case 0: break;
		case 3: cout << "(" << syn << "," << sum << ")" << endl; break;
		case -1: cout << "Error in row " << row << "!" << endl; break;
		case -2: row = row++;break;
		default: cout << "(" << syn << "," << token << ")" << endl; break;
      }
	  
	  if(syn==-2)row++;
    } while (syn != 0); 
}
```

# 2.Grammar Analyzer
## 1.Design requirements
Predictive analytics is an implementation of LL(1) analytics, which correlates non-terminators and terminators through a table, which is the predictive analytics table, which can be said to be the core part of predictive analytics. When we approach this approach, we first build a predictive analytics table. 
First of all, let's introduce the structure of a predictive analytics table, which is simply a table, and the two properties of the table are non-terminators and terminators (including '#').
If there is no generate, you can write a flag to indicate that it does not match the specific generate, and enter the error handler. 
When constructing a predictive analytics table according to grammar, you need to scan all the generative formulas:
1. Calculate the FIRST set on the right side of the generator, and if the FIRST set contains a terminator, then put the generator into the corresponding non-terminator and terminator grids
2. If the ε is in the FIRST set, then calculate the FOLLOW set of the non-terminator, and if the FOLLOW set contains the terminator, then put this generator into the corresponding non-terminator and terminator grids

Once the predictive analytics table is constructed, we can use the predictive analytics method for syntax analysis. We use a stack to store process data, and the main steps are as follows:
3. Get element A at the top of the stack, and get the element A that the input string is pointing to at the current pointer
4. If A = '#' and a = '#', the match is successful
5. If A = a but A and a are not '#', then pop the top element of the stack and enter the string pointer +1
6. If A is a non-terminator, the predictive analysis table is queried, and the right part of the generative formula determined by A and a is pressed into the stack from right to left, and if the right part is ε, then no operation is done
7. If you find the predictive analysis table and get the preset error character, call error()

## 2.Key steps
In this experiment, the predictive analysis program is designed and implemented, and the experimental platform only requires the design of the find_first function and the find_follow function of solving the non-terminator FIRST() and FOLLOW() according to the generative formula, and the generative function of the predictive analysis table.
Construct a FIRST set: Scan all generators, for each X, use the following rules continuously until the FIRST set of each set no longer increases, and scan all generators again each time if there is a change in the FIRST set:
IF X IS THE TERMINATOR, THEN FIRST(X) = {X}.
If X is a non-terminator and there is a generative X → a... then add a to the FIRST set. If X → ε is also one of the generics, then add the ε to the FIRST set as well.
If X is a non-terminator, and X → Y... is a generic, where Y is a non-terminator, then FIRST(Y) {ε} (i.e., the FIRST set is stripped ε) is added to FIRST(X).
```
<![endif]-->

size_t find_first(noterminal* this_noterminal, production* this_production)

{

noterminal* this_noterminal_temp;

char temp[2]= {0};

char *TEMP2,*help;

while(this_production->source!=this_noterminal->character)

this_production=this_production->next;

if(this_noterminal->first_number==0)

{

this_noterminal->FIRST=(char*)malloc(MAX_AMOUNT+1);

memset(this_noterminal->FIRST,0,MAX_AMOUNT+1);

}

while(this_production&&this_production->source==this_noterminal->character)

{

TEMP2=this_production->result;

while(*TEMP2)

{

if(is_appeared(*TEMP2,terminal_all))

{

temp[0]=this_production->result[0];

combine(this_noterminal->FIRST,temp);

break;

}

else

{

this_noterminal_temp=NOTERMINAL_HEAD.next;

while(this_noterminal_temp->character!=*TEMP2)

this_noterminal_temp=this_noterminal_temp->next;

if(this_noterminal_temp->first_number==0)  //没求first集

find_first(this_noterminal_temp,PRODUCTION_HEAD.next);

combine(this_noterminal->FIRST,this_noterminal_temp->FIRST);

help=this_noterminal->FIRST;

while(*help&&*help!='^')

help++;

if(*help&&*(TEMP2+1))  //包含'^'

{

while(*help)

{

*help=*(help+1);

help++;

}

}

else break;

TEMP2++;

}

}

this_production=this_production->next;

}

this_noterminal->first_number=strlen(this_noterminal->FIRST);

return success;

}
```

Constructing a FOLLOW set: Scanning all generators.For each non-terminator A of grammar G, construct FOLLOW(A) The following rules can be used continuously until each FOLLOW set is no longer growing:
For the grammatical opening symbol S, place # in FOLLOW(S).
If there is a generation A → αBβ, where α and β are strings of non-terminators and terminators, and B is non-terminators, then add FIRST(β) {ε} to FOLLOW(B).
If there is a → αB or A → αBβ ε∈FIRST(β), FOLLOW(A) is added to FOLLOW(B).
```
<![endif]-->

size_t find_follow(noterminal* this_noterminal, production* this_production)

{

char* help=NULL;

char* temp_result;

int symbol=0;

char terminal_array[2]= {0};

noterminal* FOLLOW_TEMP,*FOLLOW_HELP;

if(this_noterminal->follow_number==0)

{

this_noterminal->FOLLOW=(char* )malloc(MAX_AMOUNT+1);

memset(this_noterminal->FOLLOW,0,MAX_AMOUNT+1);

}

//第一个非终结符包含有#

if(this_noterminal==NOTERMINAL_HEAD.next)

*this_noterminal->FOLLOW='#';

while(this_production)

{

temp_result=this_production->result;

//一个产生式未结尾

while(*temp_result)

{

if(*temp_result!=this_noterminal->character)

{

temp_result++;

continue;

}

temp_result++;

if(!*temp_result)

symbol=1;

while(*temp_result)

{

if(is_appeared(*temp_result,terminal_all))

{

terminal_array[0]=*temp_result;

combine(this_noterminal->FOLLOW,terminal_array);

}

else

{

FOLLOW_TEMP=NOTERMINAL_HEAD.next;

while(FOLLOW_TEMP->character!=*temp_result)

FOLLOW_TEMP=FOLLOW_TEMP->next;

combine(this_noterminal->FOLLOW,FOLLOW_TEMP->FIRST);

help=this_noterminal->FOLLOW;

while(*help&&*help!='^')

help++;

if(*help)//包含'^'

{

while(*help)

{

*help=*(help+1);

help++;

}

symbol=1;

}

else

{

symbol=0;

break;

}

}

temp_result++;

}

if(symbol&&this_production->source!=this_noterminal->character)

{

FOLLOW_HELP=NOTERMINAL_HEAD.next;

while(FOLLOW_HELP->character!=this_production->source)

FOLLOW_HELP=FOLLOW_HELP->next;

if(FOLLOW_HELP->follow_number==0)

find_follow(FOLLOW_HELP,PRODUCTION_HEAD.next);

combine(this_noterminal->FOLLOW,FOLLOW_HELP->FOLLOW);

symbol=0;

}

}

this_production=this_production->next;

}

this_noterminal->follow_number=strlen(this_noterminal->FOLLOW);

return success;

}
```

Predictive analytics table structure:
According to the FIRST set on the right side of the generator, if the FIRST set contains a terminator, then put the generator in the box corresponding to the non-terminator and the terminator
If the ε is in the FIRST set, then the FOLLOW set of the non-terminator is calculated, and if the FOLLOW set contains the terminator, then the generator is placed in the corresponding non-terminator and terminator grids.
```
<![endif]-->

void prediction_table(void)

{  int line=0,row=0,current_character=0,number=0;

char* FIRST_CLUM,*test_exper;

noterminal* temp_noterminal=NOTERMINAL_HEAD.next,*temp_noterminal21;

terminal*  temp_terminal=TERMINAL_HEAD.next;

production* temp_production=PRODUCTION_HEAD.next;

char hah[5][7];

memset(hah,0,sizeof(hah));

for(line=0; line<5; line++)

{

for(row=0; row<7; row++)

hah[line][row]=0;

}

line=0;

while(temp_production)

{

row=0;

if(is_appeared(*temp_production->result,terminal_all)&&(*temp_production->result!='^'))

{

while(terminal_all[row]!=*temp_production->result)

row++;

hah[current_character][row]=line+1;

}

else

{

temp_noterminal=NOTERMINAL_HEAD.next;

if(*temp_production->result=='^')

{

while(temp_noterminal->character!=temp_production->source)

temp_noterminal=temp_noterminal->next;

FIRST_CLUM=temp_noterminal->FOLLOW;

if(is_appeared('#',FIRST_CLUM))

{

row=0;

while(terminal_all[row] != '#')

row++;

hah[current_character][row]=line+1;

}

while(*FIRST_CLUM)

{

row=0;

while(terminal_all[row]!=*FIRST_CLUM)

row++;

hah[current_character][row]=line+1;

FIRST_CLUM++;

}

if(temp_production->next&&temp_production->source!=temp_production->next->source)

current_character++;

temp_production=temp_production->next;

line++;

continue;

}

//是非终结符

while(temp_noterminal->character!=*temp_production->result)

temp_noterminal=temp_noterminal->next;

FIRST_CLUM=temp_noterminal->FIRST;

while(*FIRST_CLUM)

{

row=0;

while(terminal_all[row]!=*FIRST_CLUM)

row++;

hah[current_character][row]=line+1;

FIRST_CLUM++;

}

temp_noterminal21=NOTERMINAL_HEAD.next;

while(temp_noterminal21->character!=temp_production->source)

temp_noterminal21=temp_noterminal21->next;

if(is_appeared('^',temp_noterminal->FIRST)&&is_appeared('#',temp_noterminal21->FOLLOW))

{

row=0;

while(terminal_all[row]!=*FIRST_CLUM)

row++;

hah[line][row]=line+1;

FIRST_CLUM++;

}

}

if(temp_production->next&&temp_production->source!=temp_production->next->source)

current_character++;

temp_production=temp_production->next;

line++;

}

printf("\n预测分析表\n\n");

printf(" \t");

for(temp_terminal=TERMINAL_HEAD.next; temp_terminal; temp_terminal=temp_terminal->next)

printf("%c\t",temp_terminal->character);

temp_noterminal=NOTERMINAL_HEAD.next;

for(line=0; line<5; line++)

{

printf("\n%c\t",temp_noterminal->character);

for(row=0; row<7; row++)

printf("%c\t",hah[line][row]==0?' ':(hah[line][row]-0+'0'));

temp_noterminal=temp_noterminal->next;

}

printf("\n\n");

system("pause");

printf("\n\n");

memset(TEST_STACK,0,sizeof(TEST_STACK));

init_stack();

test_exper=TEST_LIST[0];

test_exper[strlen(test_exper)]='#';

STACK_PUSH(NOTERMINAL_HEAD.next->character);

while(!STACK_EMPTY())

{

printf("分析栈\t");

for(number=0; number<=amount; number++)

printf("%c",TEST_STACK[number]);

printf("\t剩余字符串\t%s\n",test_exper);

if(TEST_STACK[amount]==*test_exper)

{

STACK_POP();

test_exper++;

}

else

{

line=0;

row=0;

temp_noterminal=NOTERMINAL_HEAD.next;

while(temp_noterminal->character!=TEST_STACK[amount])

{

temp_noterminal=temp_noterminal->next;

line++;

}

while(terminal_all[row]!=*test_exper)

row++;

row=hah[line][row];

if(!row)

break;

temp_production=PRODUCTION_HEAD.next;

while(--row)

temp_production=temp_production->next;

FIRST_CLUM=temp_production->result;

current_character=strlen(FIRST_CLUM);

FIRST_CLUM=FIRST_CLUM+current_character-1;

STACK_POP();

while(current_character)

{

if(*FIRST_CLUM!='^')

STACK_PUSH(*FIRST_CLUM);

FIRST_CLUM--;

current_character--;

}

}

}

printf("分析栈\t");

for(number=0; number<=amount; number++)

printf("%c",TEST_STACK[number]);

printf("\t剩余字符串\t%s\n",test_exper);

if(STACK_EMPTY()&&*test_exper=='#')

printf("\n合法输入\n");

else

printf("\n不合法输入\n");

return ;

}
```


