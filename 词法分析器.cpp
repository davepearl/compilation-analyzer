#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
char prog[200], token[20];
char ch;
int syn, p, m = 0, n, row, sum = 0;
const char* rwtab[10] = { "if","int","for","while","do","return","break","continue","using","namespace" };
const char* rwtab1[8] = { "main","a","b","c","d","e","f","g" };

void scaner()
{
	for (n = 0; n < 8; n++) token[n] = NULL;
	ch = prog[p++];
	while (ch == ' ')
	{
		ch = prog[p];
		p++;
	}
	
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