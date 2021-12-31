#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <sys/file.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>   //including respective header files

void analysisSummary(int * mallocglobal);       //function declaration,takes 1 argument


int main()//main function
{
        int totalstudents;
        int totalscore;
        float average;
        float overallaverage;//assigning & declaring variables

        int *mallocglobal;  //pointer for dynamic memory location
        mallocglobal = (int*) malloc(100 * sizeof(int));  //initializing memory

        mallocglobal[99] = 1;//passing section number
        pthread_t thread1;//creating threads
        pthread_create(&thread1,NULL,analysisSummary,mallocglobal);
        pthread_join(thread1,NULL);

        mallocglobal[99] = 2;//passing section number
        pthread_t thread2;//creating threads
        pthread_create(&thread2,NULL,analysisSummary,mallocglobal);
        pthread_join(thread2,NULL);

        mallocglobal[99] = 3;//passing section number
        pthread_t thread3;//creating threads
        pthread_create(&thread3,NULL,analysisSummary,mallocglobal);
        pthread_join(thread3,NULL);

        average=(float)mallocglobal[2]/mallocglobal[1];
        printf("Avearge Of Section [1]: %f\n",average);//printing average for section 1

        average=(float)mallocglobal[4]/mallocglobal[3];
        printf("Avearge Of Section [2]: %f\n",average);//printing average for section 2

        average=(float)mallocglobal[6]/mallocglobal[5];
        printf("Avearge Of Section [3]: %f\n",average);//printing average for section 3

        totalstudents=mallocglobal[1]+mallocglobal[3]+mallocglobal[5];//summing students
        totalscore=mallocglobal[2]+mallocglobal[4]+mallocglobal[6];//summing marks/grades

        printf("\n\n");//new line
        overallaverage=(float)totalscore/totalstudents;//finding overall average
        printf("Average Of All Sections: %f",overallaverage);//printing average

    return 0;//returnin zero
}//end of main


void analysisSummary(int * mallocglobal )//function anaysis summary, takes  1 argument, takes file number i.e., 1 for section 1,2 for section 2....
{
    int fd;
    int fid;
    int i;
    int j;
    int score=0;
    int students=0;
    int tempscorearray[100];
    int position[100];
    char line[500] = {0};//initializing $ declaring variables
    int *filepointer;//file pointer

    int filenumber = mallocglobal[99];

    if(filenumber==1)
    {
        //filepointer=fopen("CS415_Section1_Midterm.txt","r");//opening file 1
         fd= open("CS415_Section1_Midterm.txt", O_RDONLY, 0);
    }
    else if(filenumber==2)
    {
            //filepointer=fopen("CS415_Section2_Midterm.txt","r");//opening file 2
            fd= open("CS415_Section2_Midterm.txt", O_RDONLY, 0);
    }
    else if(filenumber==3)
    {
        //filepointer=fopen("CS415_Section3_Midterm.txt","r");//opening file 3
        fd= open("CS415_Section3_Midterm.txt", O_RDONLY, 0);
    }

    fid=read(fd, &line, 499);//reading file till EOF reaches

    j=0;
    for(i=0;i<fid-1;i++)
    {
        if(line[i] == ',')//getting number of students i.e., NUMBER OF COMMAS=NUMBER OF STUDENTS
        {
            position[j]=i+1;
            students++;
            j++;
        }
    }

    int temp=0;
    int temp1=0;
    int temp2=0;
    j=0;
    for(i=0;i<students;i++)
    {
        temp=position[j];

         temp1=line[temp]-'0';//converting to int
         temp2=line[temp+1]-'0';//converting to int

         int power=10;
         while(temp2>=power)//concatinating the numbers
            power*=10;

         int tempscore= (temp1*power)+temp2;
         score+=tempscore;//adding up the score
        j++;
    }

    if(filenumber==1)//if file 1 opened
    {
        mallocglobal[filenumber] = students;//storing total students of section 1 in array
        mallocglobal[filenumber+1]=score;//storing total score of section 1 in array
    }
    else if(filenumber==2)//if file 2 opened
    {
        mallocglobal[filenumber+1] = students;//storing total students of section 2 in array
        mallocglobal[filenumber+2]=score;//storing total score of section 2 in array
    }
    else  if(filenumber==3)//if file 3 opened
    {
        mallocglobal[filenumber+2] = students;//storing total students of section 3 in array
        mallocglobal[filenumber+3]=score;//storing total score of section 3 in array
    }
}//endn of function



