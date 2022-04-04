#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
void menulist();
void orderlist();
void payment();
void admincontrol();
int adultorder();
int childorder();
int price[]={0,150,200,220,400,150,190,190,90,390,290,350,400,250,500,350,90,195,60,180,700,480,150,550,220,250,300,480,280,340,150,200,220,180};
int adultnum,childnum;
float billingtotal=0;
float subtotal=0;

struct ONLINE{
	char name[30];
	char bank[50];
	int ac_no;
	float bal;
};

void main()
{
	FILE *menu;
	char c;
	int option;
	subtotal=0;
	menu=fopen("MAINMENU.dat","rb");
	c=fgetc(menu);
	while(c!=EOF){
		printf("%c",c);
		c=fgetc(menu);
	}
	fclose(menu);
	printf("\n\n\tPRESS 1 FOR CUSTOMER ORDER");
	printf("\n\tPRESS 2 FOR ADMINISTRATION CONTROL");
	printf("\n\tPRESS 3 FOR EXIT");
	printf("\n\n\tEnter your option:");
	ahere:
	scanf("%d",&option);
	if(option==1){
		menulist();
		char response = 'y';
	    while(response == 'y'|| response == 'Y'){
	        printf("\n\tPlease enter the number of adults:");
	        adult:
	        scanf("%d",&adultnum);
			if(adultnum<0){
				printf("\tPlease enter the correct number of adults:");
				goto adult;
			}   
	        printf("\tPlease enter the number of childrens:");
	        child:
	        scanf("%d",&childnum); 
			if(childnum<0){
				printf("\tPlease enter the correct number of childrens:");
				goto child;
			}          
	    	orderlist();
	        printf("\n\tWould you like to order more?(y/n):");
	        here:
	        scanf(" %c",&response);
	    }
	    if(response == 'n'|| response == 'N'){	 	
	    	payment();      
		}
		else{
			printf("\tPlease enter the correct option(y/n):");
			goto here;
		}
	    printf("\n\n\n\n\t      ******************** THANK YOU FOR COMING  ********************\n");
		printf("\t**********************   PLEASE VISIT US NEXT TIME  ********************** \n");		
	}
	else if(option==2){
		admincontrol();
	}
	else if(option==3){
		printf("\n\t- - THANK YOU!! - -");
		exit(0);
	}
	else{
		printf("\tPlease enter the correct option!!:");
		goto ahere;
	}
}

   //MENULIST CONTROL------>
void menulist()
{
	FILE *menu;
	char c;
	menu=fopen("FOODMENU.dat","rb");
	if(menu==NULL){
		printf("Error while opening MENU!!!");
		exit(0);
	}
	printf("\n");
	c=fgetc(menu);
	while(c!=EOF){
		printf("%c",c);
		c=fgetc(menu);
	}
}

   //MAIN ORDER CONTROL------>
void orderlist()
{
	FILE *bills;
	float adultstotal,childstotal,total;
	float discount,vat;
	int dper;
	adultstotal=adultorder();
	childstotal=childorder();
	total=adultstotal+childstotal;
	if(total > 10000){
		discount=((total * 10)/100);
		dper=10;
	}
	else if(total > 7000){
		discount=((total * 7)/100);
		dper=7;
	}
	else if(total > 5000){
		discount=((total * 5)/100);
		dper=5;
	}
	else if(total > 3000){
		discount=((total * 3)/100);
		dper=3;
	}
	else{
		discount=((total * 1)/100);
		dper=1;
	}
	vat=(total-discount)*13/100;
	//printing in console
	printf("\n\n\n\n \t\t\t     ********************************    \n");
    printf(" \t\t   ******************  FINAL BILL   *******************      \n\n");
    printf(" \t\t\tAdult/Child\tCount\t\tTotal Price\n");
    printf(" \t\t\tAdults\t\t  %d\t\t   %5.2f\n",adultnum,adultstotal);
    printf(" \t\t\tChildren\t  %d\t\t   %5.2f\n",childnum,childstotal);
    printf(" \t\t\tTotal bill\t\t\t   %5.2f\n",adultstotal+childstotal);
    printf(" \t\t\tDiscount(%d%%)\t\t\t  -%5.2f\n",dper,discount);
    printf(" \t\t\tVat(13%%)\t\t\t  +%5.2f\n",vat);
    printf(" \t\t\t___________________________________________\n");
    printf(" \t\t\tSub Total\t\t\t Rs %5.2f\n",billingtotal=(total-discount+vat));
    subtotal+=billingtotal;
        //printing in file
    bills=fopen("BILLs.txt","a");                                                
    fprintf(bills,"\n\n\n\n \t\t\t     ********************************    \n");
    fprintf(bills," \t\t   ******************  FINAL BILL   *******************      \n\n");
    fprintf(bills," \t\t\tAdult/Child\tCount\t\tTotal Price\n");
    fprintf(bills," \t\t\tAdults\t\t  %d\t\t   %5.2f\n",adultnum,adultstotal);
    fprintf(bills," \t\t\tChildren\t  %d\t\t   %5.2f\n",childnum,childstotal);
    fprintf(bills," \t\t\tTotal bill\t\t\t   %5.2f\n",adultstotal+childstotal);
    fprintf(bills," \t\t\tDiscount(%d%%)\t\t\t  -%5.2f\n",dper,discount);
    fprintf(bills," \t\t\tVat(13%%)\t\t\t  +%5.2f\n",vat);
    fprintf(bills," \t\t\t___________________________________________\n");
    fprintf(bills," \t\t\tSub Total\t\t\t Rs %5.2f\n",(total-discount+vat));
    fclose(bills);
}

   //ADULTS CONTROL CONTROL------>
int adultorder()
{
    int option,i,amount;
    int adultstotal=0;
    char response = 'y';
	if(adultnum <=0){
    	printf("\n ");
    	return adultstotal;
    }
	else{
	    printf("\n\n\t*---ADULTS-->:\n");
	    for(i=0;i<adultnum;i++){
	        printf("\tAdult[%d]Please enter your orders:\n",i+1);
	        do{
	            printf("\tPlease enter your option::");
	            option:
	            scanf("%d",&option);
				if(option<1 || option>33){
					printf("\t**SORRY WE DONOT HAVE THIS ORDER IN MENU**\n");
					printf("\tPlease enter the correct option:");
					goto option;
					}
	            printf("\tPlease enter your amount of order:");
	            amount:
	            scanf("%d",&amount);
				if(amount<1){
					printf("\tPLease enter the correct amount:");
						goto amount;
				}       
	            adultstotal=adultstotal+(amount * price[option]);
	            here:
				printf("\n\tWould you like to order more?(y/n):");
	            scanf("\n%c",&response);
	        }while(response == 'y' || response == 'Y');
	        printf("\n");
	    }
	}
    if(response=='n'||response=='N'){
    	return adultstotal;
	}
	else{
		printf("\t--Enter the correct option--");
		goto here; 
	}
}

   //CHILDRENS CONTROL CONTROL------>
int childorder()
{
    int option,i,amount;
    int childstotal=0;
    char response = 'y';
	if(childnum<=0){
      	printf("\n ");
      	return childstotal;
    }
	else{
	    printf("\n\n\t*---CHILDS-->:\n");
	    for(i=0;i<childnum;i++){
	        printf("\tChild[%d]Please enter your orders:\n",i+1);
	    	do{
	            printf("\tPlease enter your option::");
	            option:
	            scanf("%d",&option);
				if(option<1 || option>33){
					printf("\t**SORRY WE DONOT HAVE THIS ORDER IN MENU**\n");
					printf("\tPlease enter the correct option:");
					goto option;
				}
	           	printf("\tPlease enter your amount of order:");
	           	amount:
	            scanf("%d",&amount);    
				if(amount<1){
					printf("\tPLease enter the correct amount:");
					goto amount;
				}              
	            childstotal=childstotal+(amount* price[option]); 
				here:    
	            printf("\n\tWould you like to order more?(y/n):");
	            scanf("\n%c",&response);       
	        }while(response == 'y' || response == 'Y');
		}
	}
	if(response=='n'||response=='N'){
    	return childstotal;
	}
	else{
		printf("\t--Enter the correct option--");
		goto here; 
	}
}

   //PAYMENT CONTROL------>
void payment(){
	FILE *fop;
	int option,option2;
	printf("\n\n\tHow do you want to pay?\n");
    printf("\t\t1.Cash\n\t\t2.Online Payment");
    printf("\n\n\t\tEnter your option:");
    here:
    scanf("%d",&option);
    switch(option){
    	case 1:
    		fop=fopen("PAYMENT.txt","a");
    		printf("\n\n\t\t\tYou choosed CASH!");
    		printf("\n\t\t\tTotal amount is:Rs %.2f",subtotal);
    		fprintf(fop,"\n\tCASH PAYMENT:Total amount:%.2f",subtotal);
    		printf("\n\t\t\tCASH RECEIVED :)");
    		fclose(fop);                             
    		printf("\n\n\t\tDo you want to continue to main menu?(y/n):");
    		here1:
    		scanf(" %c",&option2);
    		if(option2=='Y'||option2=='y'){
    			billingtotal=0;
    			main();
			}
			else if(option2=='n'||option2=='N'){
				printf("\n\tTHANK YOU!!");
				exit(0);
			}
			else{
				printf("\n\t\tPlease enter the correct option:");
				goto here1;
			}
    		break;
    		
    	case 2:
    		{
    			struct ONLINE online;
    			int i=0;
				char ch;
				char pwd[30];
				fop=fopen("PAYMENT.txt","a");
				printf("\n\n\t\t\tYou choosed ONLINE PAYMENT!");
				printf("\n\t\t\tTotal amount is:Rs %.2f",subtotal);
				printf("\n\t\t\tEnter your name:");	
				fflush(stdin);
				gets(online.name);
				fprintf(fop,"\n\n\tONLINE PAYMENT:\n\t\tName:%s",online.name);
				printf("\t\t\tEnter the name of the bank:");
				fflush(stdin);
				gets(online.bank);
				fprintf(fop,"\n\t\tBank:%s",online.bank);
				printf("\t\t\tEnter your Account no:");
				scanf("%d",&online.ac_no);
				fprintf(fop,"\n\t\tAc/No:%d",online.ac_no);
				printf("\t\t\tEnter the Amount:");
				scanf("%f",&online.bal);
				fprintf(fop,"\n\t\tAmount:%.2f\n",online.bal);
				printf("\n\t\t\tEnter PIN No:");
				while((ch = _getch())!=13){
					pwd[i]=ch;
					i++;
					printf("*");
				}
				pwd[i]='\0';
				printf("\n\n\t\t\t\t\t\tCASH RECEIVED :)");
				fclose(fop);
				printf("\n\n\t\tDo you want to continue to main menu?(y/n):");
	    		here2:
	    		scanf(" %c",&option2);
	    		if(option2=='Y'||option2=='y'){
	    			billingtotal=0;
	    			main();
				}
				else if(option2=='n'||option2=='N'){
					printf("\n\tTHANK YOU!!");
					exit(0);
				}
				else{
					printf("\n\t\tPlease enter the correct option:");
					goto here2;
				}
				break;
			}
			
			default:
				printf("\n\t\tPlease enter the correct option:");
				goto here;
		}
}

   //ADMIN CONTROL------>
void admincontrol(){
	FILE *fpwd;
	int i=0,j=0,k=3;
	int adminchoice;
    char ch,c;
    char pwd[30],realpwd[30];
    fpwd=fopen("CONFIDENTIAL.dat","r");
    c=fgetc(fpwd);
    while(c!=EOF){
    	realpwd[j]=c;
    	c=fgetc(fpwd);
    	j++;
	}
	fclose(fpwd);
    here:
    printf("\n\tEnter Password:");
   	while((ch = _getch())!=13){
   		pwd[i]=ch;
        i++;
        printf("*");
	}
    pwd[i]='\0';
    realpwd[j]='\0';
    if((strcasecmp(pwd,realpwd))==0){
    	printf("\n\n\t\tWELCOME");
    	chere:
    	printf("\n\t\t1.Bills Enquery\n\t\t2.Payment Details");
    	printf("\n\n\t\tEnter your option:");
    	bhere:
    	scanf("%d",&adminchoice);
    	switch(adminchoice){
    		case 1:{
    			FILE *bill;
				char c,ch;
				bill=fopen("BILLs.txt","r");
				if(bill==NULL){
					printf("Error while opening BILLs!!!");
					exit(0);
				}
				printf("\n");
				c=fgetc(bill);
				while(c!=EOF){
					printf("%c",c);
					c=fgetc(bill);
				}
				printf("\n\tDo you like to continue with administration control?(y/n):");
				ahere:
				scanf(" %c",&ch);
				if(ch=='y'||ch=='Y'){
					goto chere;
				}
				else if(ch=='n'||ch=='N'){
					main();
				}
				else{
					printf("\n\tPlease enter the correct option(y/n):");
					goto ahere;
				}
			}
			
			case 2:{
				FILE *fop;
				char c;
				fop=fopen("PAYMENT.txt","r");
				if(fop==NULL){
					printf("Error while opening PAYMENT FILE!!!");
					exit(0);
				}
				printf("\n");
				c=fgetc(fop);
				while(c!=EOF){
					printf("%c",c);
					c=fgetc(fop);
				}
				fclose(fop);
				printf("\n\n\tDo you like to continue with administration control?(y/n):");
				rhere:
				scanf(" %c",&ch);
				if(ch=='y'||ch=='Y'){
					goto chere;
				}
				else if(ch=='n'||ch=='N'){
					main();
				}
				else{
					printf("\n\tPlease enter the correct option(y/n):");
					goto rhere;
				}
			}
			
			 default:
			 	printf("\n\t\tPlease enter the correct option:");
				goto bhere;
		}
	}
    else if(k==0){
    	printf("\n\n\tUnauthorized Person Detected!!!\n\t*PROGRAM TERMINATED :(");
    	exit(0);
	}
	else{
		printf("\n\tIncorrect Password.  [%d attempt left]",k);
		i=0;
		k--;
		goto here;
	}	
}