#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <boost/algorithm/string.hpp> 
#include <bits/stdc++.h> 
using namespace std;
string initial;
int fin_num;//no of final state
int tran_num;//no of transitions
string* in_state,*next_state,*var,*tran,*final1;
char *changed_var;
ofstream fout;
void turing(string,string,int,string);//functions used as turing machine
string print(string string1);
string name;//name of the program
int main()
{

	int num_loop,i;
	fstream fin;
	fin.open("input1.txt",ios::in);
	fout.open("output.txt",ios::in);
	string s;
	string skip;//used to skip the "--------" part in the input file after one teast case is finished
	fin >> num_loop;//used to know how many test cases are there.
	for(int j=0;j<num_loop;j++)
	{
		if(j>0)
		{
			fin >> skip;
		}
		fout << "For input set" << j+1 << ":" << endl;
		fin >> name;
		fin >> initial;//initial state
		fin >> fin_num;//number of final states
		
		
		final1=new string[fin_num];//array of final states
		//cout << "Enter the final states ";
		for(int i=0;i<fin_num;i++)
		{
			fin >> final1[i];
		}
		//cout << "Enter the no of transitions";
		
		/*If in ith transitiom in q0 it sees 1 makes it blank goes to q1 and moves the pointer right then :
		in_state[i]=q0
		nest_state[i]=q1
		var[i]=1
		changed_var[i]=B
		tran[i]=r*/
		
		fin >> tran_num;//no of total transitions
		in_state=new string[tran_num];//initial state for a transition suppose nth
		next_state=new string[tran_num];//next state for nth transition
		var=new string[tran_num];//nth transition on var
		changed_var=new char[tran_num];//changed variable after transition 
		tran=new string[tran_num];//transition to left or right
		string tran_str;
		
		vector<string> result;
		for(int i=0;i<tran_num;i++)
		{
		
		
			if(i==0)
			{
				getline(fin,tran_str);
			}			
			getline(fin,tran_str);
			boost::split(result,tran_str,boost::is_any_of(" "));//split line into words and store in the vector result
			in_state[i]=result[1];
			s=result[3];
			var[i]=s[0];
			next_state[i]=result[7];
			changed_var[i]=result[9][0];
			tran[i]=result[11];
		}
		
		string input;
		//cout << "Enter the input string ";
		fin >> input;//input string actually the initial content in the tape.
		int count=0;
		//int i;
		
		string temp_str="";//used to append 1000 'B' before and after input string to make the string looks like consist of infinite blanks.
		
		for(int k=0;k<1000;k++)
		{
			temp_str=temp_str+"B";
		}
		input=temp_str+input+temp_str;
		for(i=0;i<input.length();i++)//after the loop i will point to the first element in the tape.
		{
			if(input[i]!='B')
			{
				break;
			}
		}
		//cout << "i is " << i << endl;
		string res="";//store the result of each tree in case of non determinism
		turing(initial,input,i,res);//call turing funtion for the output of the test case
		fout << "\n-------------------------------------------\n\n";//used to differentiate between questions
		
	}

	fin.close();
	fout.close();
	return 0;
}

void turing(string state,string string1,int head,string res)
{
	int flag;
	res=res+"pointer is "+to_string(head) +"\nstring is "+print(string1)+"\n";//store the answers to print at last
	//fout << "pointer is " << head << endl;//prints the pointer
	//fout << "string is " ;
	
	//print(string1);//print function prints the string without left and right blanks
	int i;
	string temp_string=string1;//used to remember the initial string which comes through the call.
	flag=0;//flag is used to see if any change is possible in the string
	for(i=0;i<tran_num;i++)//searched in every transition state
	{
		string1=temp_string;//makes string 1 to initial value
		string temp_s(1, string1[head]);//store the character at the string1[head] in temp_s as a string 
		if(temp_s.compare(var[i])==0) //compare if any transition is possible at this temp_S 
		{
			if(in_state[i].compare(state)==0)//compares if initial state is same as state with which function is called
			{
				string1[head]=changed_var[i];//If two condition satisfies change the string1[head] with proper next variable
				if(tran[i].compare("r")==0)//see if the pointer should be moved to right
				{
					flag=1;
					turing(next_state[i],string1,head+1,res);//if it should be moved right call turing with the head pointing to next index
				}
				else
				{
					flag=1;
					turing(next_state[i],string1,head-1,res);//if it should be moved left call turing with the head pointing to previous index
				}
			}
		}
	}
	int reached=0;//to keep a track if reached in final state
	if(flag==0)
	{
		fout << res;
		for(i=0;i<fin_num;i++)
		{
			if(state.compare(final1[i])==0)//if no change is possible in the string check if the machine is in final stage
			{
				//fout << string1 << endl;
				fout << "Reached final state of" << " " << name;
				reached=1;
			}
		}
		if(reached==0)
		{
			fout << "Did not reach final state of" << " " << name;
		}
		fout << "\n*******************************************\n\n";//used to differentiate between answers of same question in case of non determinism
		return;
	}
}


string print(string string1)//returns the string without excess 'B'
{
	string temp_str="";
	int len=string1.length();
	int first=0,last=len-1;
	while(string1[first]=='B')//first points to the index where first symbol is there
	{
		first++;
	}
	while(string1[last]=='B')//last points to the index where last symbol is there
	{
		last--;
	}
	temp_str=temp_str+'B';//append a 'B' just to show infinite B's are there in left
	for(int k=first;k<=last;k++)
	{
		temp_str=temp_str+string1[k];//append the actual value
	}
	temp_str=temp_str+'B';//append a 'B' just to show infinite B's are there in right
	return temp_str;
}
