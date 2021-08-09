#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
//-------------------------------for counting lines-----------------------
  void *countlines(void *argp)
  {
      char para[100];
      para=(para*) argp;
      int cnt=0;
      for(int i=0;i<strlen(para);i++)
      if(para[i]=='.')
      {
        cnt++;
      }
      pthread_exit((void *)cnt);
  }
  //-------------------------for pattern search---------
  void *patternsearch(void *argp)
  { 
      char para[100];
      char key[10];
      para=(para*) argp;
      key=(key*) argp;
     for(int i=0;i<strlen(para);i++)
     { 
        int flag=1;
        int res=0;
        if(para[i]==key[0] && i+strlen(key)-1<strlen(para))
        {  
            i++;
            printf("%c\t",para[i]);
            printf("%c\n",key[1]);

            for (int j = 1; j < strlen(key) ; j++)
            { 
                if(para[i]==key[j])
                { 
                    i++;
                    continue;
                }
                else
                {
                    flag=0;
                    break;
                }
            }
            if(flag)
            {
                res= 1;
                pthread_exit((void *)res);
	
            }
        }
      }
    
  }
 //--------------------------count word-----------------     
 void *countword(void *argp)
 {
 char para[100];
  para=(para*) argp;
 int cnt=0;
 int cnt1=0;
 int cnt2=0;
 int cnt3=0;
 int cnt4=0,cnt5=0;
 int cnt6=0;
   for(int i=0;i<strlen(para);i++)
   {
        if(para[i]==' ')
        {
            cnt++;
        }
        if(para[i]=='s'&& i+1<strlen(para)){
        if((para[i-1]==' '|| i-1==-1) && para[i]=='s' && para[i+1]=='h' && para[i+2]=='e' && (para[i+3]==' ' || i+1==strlen(para)))
        {  
            cnt1++;
        }}
        if(para[i]=='h' && i+1<strlen(para)){
            if((para[i-1]==' '|| i-1==-1) && para[i]=='h' && para[i+1]=='e' && (para[i+2]==' '|| i+1==strlen(para)))
            {  
                cnt2++;
            }}
        if(para[i]=='i' && i+1<strlen(para)){
            if((para[i-1]==' '|| i-1==-1) && para[i]=='i' && para[i+1]=='t' && (para[i+2]==' '|| i+1==strlen(para)))
            {   
                cnt3++;
            }}
        if(para[i]=='a' && i+1<strlen(para)){
            if((para[i-1]==' '|| i-1==-1) && para[i]=='a' && para[i+1]=='m' && (para[i+2]==' '|| i+1==strlen(para)))
            {   
                cnt4++;
            }}
        if(para[i]=='i' && i+1<strlen(para)){
            if((para[i-1]==' '|| i-1==-1) && para[i]=='i' && para[i+1]=='s' && (para[i+2]==' '|| i+1==strlen(para)))
            {  
                cnt5++;
            }}
        if(para[i]=='a' && i+2<strlen(para)){
            if((para[i-1]==' '|| i-1==-1) && para[i]=='a' && para[i+1]=='r' && para[i+2]=='e' && (para[i+3]==' '|| i+1==strlen(para)))
            {
                cnt6++;
            }}
   }
        printf("%d,%d,%d,%d,%d,%d,%d\n",cnt,cnt1,cnt2,cnt3,cnt4,cnt5,cnt6);
        int ans =(cnt+2)-(cnt1+cnt2+cnt3+cnt4+cnt5+cnt6);
        pthread_exit((void *)ans);
	
 }

 //---------------------------------------main code starts here-------------------------      
void main()
{
    printf("----------WELCOME TO THE THREAD-BOOK-------\n");
    
    char ch[100];
    pthread_t tid[100];
    
    //pthread_t tid1,tid2;
   printf("\nEnter a para ending with # \n");
    scanf("%[^'\n']s", ch);

    int l;int k;
    char key[10];
    int val;
    do
    {
    printf("Enter the operation you want to perform\n");
    printf("1.Create\n2.Count of Lines\n3.Pattern Searching\n4.Count of Words Except\n5.Exit\n");
    scanf("%d",&val);
    
    switch(val)
    {
        case 1:
                printf("The Entered paragraph is\n %s\n",ch); 
               break;
        
        case 2:
                //k=countlines(ch);
               printf("The number of Lines \t%d:\n",countlines());
               pthread_create(&tid[ch],NULL,countlines,(void*)&ch);
               pthread_join(tid[ch],(void*)&countlines);
               break;
        case 3:
                 
                printf("\nEnter the word you want to search\n");
                scanf("%s",&key);
                pthread_create(&tid[ch],NULL,patternsearch,(void*)&ch);
                pthread_join(tid[ch],(void*)&patternsearch);
               if(patternsearch()==1)
               {
                   printf("FOUND\n");
               }
               else
               {
                   printf("NOT FOUND\n");
                }
               break;
        case 4:
               //l=countword(ch);
               pthread_create(&tid[ch],NULL,countword,(void*)&ch);
               pthread_join(tid[ch],(void*)countword);
               printf("\n The count of words are \t%d\n "countword());
               break;
        case 5:
                break;
       default: printf("Sorry INVALID Option! Please try some other Option\n");
                   
   }
     
     }while(val!=5);
}
