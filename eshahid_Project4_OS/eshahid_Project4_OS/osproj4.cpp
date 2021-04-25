//Ebrahim Shahid
//Operating Systems - Project 4
//Banker's Algorithm using C++

#include<iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//to display A, B,C ... while displaying matrix
void displayHeader(int m,ofstream & outfile)
{
    char c='A';
    outfile<<endl<<" ";
    for(int i=0;i<m;i++)
    {
        outfile<<(char)(c+i)<<setw(3);
    }
}

int main()
{
    int n,m; //where n is the number of processes, and m is the number of resources
    int Allocation[10][10],Maximum[10][10],safeSequence[10];
    int A_Matrix[10],N_Matrix[10][10],F_Matrix[10],W_Matrix[10], R_Matrix[10]; //Avaiable, Need, Finish, Work, and Request Matrix definitions

//opening input file for read
    ifstream infile("s1.txt");
//Error handling, terminate the program if no input file given 
if(!infile)
    {
        cout<<"Error: No input file!";
        exit(0);
    }

//If file provided, execute the rest of the program

//reading and number of processes from input file
    infile>>n;
//reading and number of resources from input file
    infile>>m;
//reading allocation matrix (n x m) from input file
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            infile>>Allocation[i][j];
        }
    }
//reading max matrix (n x m) from input file
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            infile>>Maximum[i][j];
        }
    }
//reading available matrix (1 x m)from input file
    for(int i=0;i<m;i++)
    {
        infile>>A_Matrix[i];
    }
// Creating output file
// opening output file write
    ofstream outfile("s1_soln.txt");
// write n and m
    outfile<<"There are "<<n<<" processes in the system.";
    outfile<<endl<<"There are "<<m<<" resource types.";
//Display the allocation matrix
    outfile<<endl<<"The Allocation Matrix is...";
    displayHeader(m,outfile);
    for(int i=0;i<n;i++)
    {
        outfile<<endl<<i<<": ";
        for(int j=0;j<m;j++)
        {
            outfile<<Allocation[i][j]<<setw(3);
        }
    }
//Display the max matrix
    outfile<<endl<<"The Max Matrix is...";
    displayHeader(m,outfile);
    for(int i=0;i<n;i++)
    {
        outfile<<endl<<i<<": ";
        for(int j=0;j<m;j++)
        {
            outfile<<Maximum[i][j]<<setw(3);
        }
    }
//Display the available vector
    outfile<<endl<<"The Available Vector is...";
    displayHeader(m,outfile);
    outfile<<endl<<" 1: ";
    for(int j=0;j<m;j++)
    {
        outfile<<A_Matrix[j]<<setw(3);
    }
//Processing of Bankers algorithm
    while(true){
//calculating need matrix from Max and Allocation
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            N_Matrix[i][j]=Maximum[i][j]-Allocation[i][j];
        }
}
//Display the need matrix
    outfile<<endl<<"The Need Matrix is...";
    displayHeader(m,outfile);
    for(int i=0;i<n;i++)
    {
        outfile<<endl<<i<<": ";
        for(int j=0;j<m;j++)
        {
           outfile<<N_Matrix[i][j]<<setw(3);
        }
    }
//initialize work matrix from available
    for(int i=0;i<n;i++){
        W_Matrix[i]=A_Matrix[i];
    }
    int s=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
        if(F_Matrix[i]==0 && N_Matrix[i][j]<=W_Matrix[j])
            {
                safeSequence[s++]=i+1;
                W_Matrix[i]=W_Matrix[i]+Allocation[i][j];
                F_Matrix[i]=1;//
            }
        }
    }
    if(s==n)
    {
        outfile<<endl<<"THE SYSTEM IS IN A SAFE STATE!";
//reading request vector (1 x m) from s1.txt
        int req;
        infile>>req;
        infile.ignore();
        for(int i=0;i<m;i++)
        {
            infile>>R_Matrix[i];
        }
        for(int j=0;j<m;j++)
        {
            Allocation[req][j]+=R_Matrix[j];
            A_Matrix[j]-=R_Matrix[j];
        }
        outfile<<endl<<"The Request Vector is...";
        displayHeader(m,outfile);
        outfile<<endl<<" 1: ";
        for(int j=0;j<m;j++)
        {
            outfile<<R_Matrix[j]<<setw(3);
        }
        outfile<<endl<<"THE REQUEST CAN BE GRANTED!";
        outfile<<endl<<"The Available Vector is...";
        displayHeader(m,outfile);
        outfile<<endl<<" 1: ";
        for(int j=0;j<m;j++)
        {
            outfile<<A_Matrix[j]<<setw(3);
        }
        cout << "Output sent to s1_soln.txt" << endl;
    break;
}
    else
    {
        outfile<<endl<<"DEAD LOCK IS OCCURED!!!";
        break;
    }
}
    return 0;
}


