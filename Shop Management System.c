#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
struct product
{
	char product_name[30];
	float price;
	int quantity;
	struct discount_p
	{
		int quantity;
		float discount;
	} add;
struct product *p;
};
void newproduct(void)
{
	FILE *fp;
	struct product b;
	printf("enter product name : \n");
	fflush(stdin);
	gets(b.product_name);
	printf("enter price of product : \n");
	fflush(stdin);
	scanf("%f",&b.price);
	printf("enter quantity of that product : \n");
	scanf("%d",&b.quantity);
	printf("enter discount coupon enter quantity and discount \n");
	scanf("%d%f",&b.add.quantity,&b.add.discount);
	fp=fopen("product.txt","a+");
	fwrite(&b,sizeof(b),1,fp);
	fclose(fp);
}

void display(void)
{
	int found=0;
	struct product b;
	FILE *fp;
	fp=fopen("product.txt","r");
	while(fread(&b,sizeof(b),1,fp))
	{
		printf("\n\n product name : %s\nproduct price : %0.2f\nproduct quantity %d \n",b.product_name,b.price,b.quantity);
		printf("discount coupon : quantity : %d \t discount : %0.2f\n",b.add.quantity,b.add.discount);
		found=1;
	}
	fclose(fp);
	if(found==0)
	{
		printf("\n File is empty \n");
	}
}

void search_item(void)
{
	int found=0;
	struct product b;
	FILE *fp;
	char product[30];
 printf("\n enter search element name : ");
	          fflush(stdin);
	          gets(product);
	fp=fopen("product.txt","r");
	while(fread(&b,sizeof(b),1,fp))
	{
		if(!strcmp(b.product_name,product))
		{
		printf("\n\n product name : %s\nproduct price : %0.2f\nproduct quantity %d\n",b.product_name,b.price,b.quantity);
		printf("discount coupon : quantity : %d \t discount : %0.2f\n",b.add.quantity,b.add.discount);
		found=1;
		break;	
		}
	}
	fclose(fp);
	if(!found)
	printf("\n search element not found\n");

}
void modification()
{
	FILE *fp,*f;
	char product[25];
	int found=0,v=1,key,d,quan;
	struct product b;
	fp=fopen("product.txt","r");
	f=fopen("pro.txt","a");
	printf("enter product name : ");
	fflush(stdin);
	gets(product);
	while(fread(&b,sizeof(b),1,fp))
	{
		if(!strcmp(b.product_name,product))
		{  
		while(v){
			
				printf("what you want to modified\n 1.price\n2.qauntity\n3.discount\n4.product name \n5.Exit\n ");
   scanf("%d",&key);
   switch(key)
   {
   	case 1 : printf("enter new price \n");
   	        scanf("%f",&b.price);
   	        break;
   	case 2 : printf("what you are looking for 1.new qauntity \n2.Add quantity\n");
	         scanf("%d",&d);
			 if(d==1)
			 {
			 	printf("enter new quantity \n");
			 	scanf("%d",&b.quantity);
			 	
					 } 
			else if(d==2) {
				printf("enter quantity to add with old quantity\n");
				scanf("%d",&quan);
				b.quantity+=quan;
			}	
		
			break;
	case  3: printf("enter new quantity and discount coupon \n");
	        scanf("%d%f",&b.add.quantity,&b.add.discount);
			break;
	case 4: printf("enter new name of %s product \n",b.product_name);
	       fflush(stdin);
	        gets(b.product_name);
			break;
	case 5 : v=0;
	         break;		
	default: printf("invalid choice ");				 			        
   }
			
			
	}
		found=1;
		fwrite(&b,sizeof(b),1,f);
		}
		else
		fwrite(&b,sizeof(b),1,f);
	}
	if(!found)
	printf("\n Searched element not found\n");
    fclose(f);
	fclose(fp);
	remove("product.txt");
	rename("pro.txt","product.txt");
}
void deleteproduct(void)
{
	FILE *fp,*f;
	int found=0;
	struct product b;
	char product[25];
	printf("enter product name : ");
	fflush(stdin);
	gets(product);
	fp=fopen("product.txt","r");
	f=fopen("pro.txt","a");
	while(fread(&b,sizeof(b),1,fp))
	{
		if(!strcmp(b.product_name,product))
		{
			found=1;
		}
		else
		fwrite(&b,sizeof(b),1,f);
		
	}
	fclose(fp);
	fclose(f);
	remove("product.txt");
	rename("pro.txt","product.txt");
	if(!found)
	printf("\nwanted element not found \n");
}
void buyproduct()
{
	char product[30];
	struct product b,d;
	char customer[30];
	int i,quantity,found,dis_quantity,fun=0;
	float price,dis_discount;
	FILE *fp,*f;
	printf("enter product name : ");
	fflush(stdin);
	gets(product);
	fp=fopen("product.txt","r");
	while(fread(&b,sizeof(b),1,fp)&&found==0)
	{
	
		if(!strcmp(b.product_name,product))
		{ found=1;
		 fclose(fp);
		}
	}
	if(!found)
	printf("product not found\n");
	else
	{
		printf("\nenter quantity of product \n");
		scanf("%d",&quantity);
		fp=fopen("product.txt","r");
		f=fopen("pro.txt","a");
		while(fread(&b,sizeof(b),1,fp))
		{
			if(!strcmp(b.product_name,product))
			{
				if(b.quantity>=quantity)
				 {
				 	b.quantity-=quantity;
				 	price=b.price;
				 	dis_quantity=b.add.quantity;
				 	dis_discount=b.add.discount;
				 	fwrite(&b,sizeof(b),1,f);
				 	fun=1;
				 }
				
			}
			else fwrite(&b,sizeof(b),1,f);
			
		}
		fclose(fp);
		fclose(f);
		remove("product.txt");
		rename("pro.txt","product.txt");
		if(fun)
		{
			printf("enter customer name :\n");
			fflush(stdin);
			gets(customer);
			strcat(customer,".txt");
			fp=fopen(customer,"a");
			d.price=price;
			d.quantity=quantity;
			d.add.quantity=dis_quantity;
			d.add.discount=dis_discount;
			strcpy(d.product_name,product);
			fwrite(&d,sizeof(d),1,fp);
			fclose(fp);
			
		}
	
	}
	
	
}
void seebill(void)
{
	FILE *fp;
	struct product b;
	char path[30];
	float finalbill=0;
	printf("enter file name\n");
	fflush(stdin);
	gets(path);
	strcat(path,".txt");
	fp=fopen(path,"r");
	if(fp==NULL){
		printf("\n File not exits\n");
		exit(1);
	}
	 printf("\nProduct name : \tPrice: \t Quantity :\t\n");
	while(fread(&b,sizeof(b),1,fp))
	{
		printf("%12s\t%.3f\t%6d\n",b.product_name,b.price,b.quantity);
		if(b.quantity>=b.add.quantity)
		finalbill+=(b.quantity*b.price-(b.quantity*b.price*(b.add.discount/100)));
		else 
			finalbill+=b.price*b.quantity;
	}
	printf("\n\t\t\t\t Finalbill = %0.2f",finalbill);
	fclose(fp);
}
void customer()
{
    int i,b=1;

    while(b==1)
    {
    	system("cls");
		printf("\n Enter your choice \n1.Buyproduct\n2.search_iteam\n3.seebill\n4.Exit\n");
    scanf("%d",&i);
		switch(i)
	{
		case 1: buyproduct();
		        break;
		case 2: search_item();
		        break;
		case 3 : seebill();
		         break;        
		case 4: b=0;
		 break;
		
		default : printf("\n Invalid choice \n");		        
	}
	getch();
	}
}
void owner(void)
{
	 int choice,dr,b=1;
	while(b==1)
    {   
         system("cls");
    	 printf("\n\nenter your choice \n1.add product\n2.Delete product\n3.Display product\n4.Search_item\n5.exit");
    scanf("%d",&choice);
    switch(choice)	
    {
    	case 1: printf("\nenter your choice 1.add new product\n2.MOdification\n");
    	        scanf("%d",&dr);
    	        switch(dr)
    	        {
    	        	case 1: newproduct();
    	        	        break;
    	        	case 2 : modification();
					        break;
					default : printf("\n Invalid choice\n");		        
				}
				break;
		case 2 : deleteproduct();
		         break;
		case 3: display();
		        break;
		        
		case 4 :search_item();
		         break;     
	       case 5 :b=0; 
		            break;    
	   default : printf(" \n Invalid choice\n")	;		 				 		
	}
	getch();
}
}

int main()
{ 
   
    int n,b=1;
 
  
   
    while(b==1)
    {
    	system("cls");
	 printf("enter your choice \n1.Customer\n2.Owner\n3.Exit\n");
    scanf("%d",&n);
    switch(n)
    {
    	case 1 : customer();
    	        break;
    	case 2: owner();
		          break;
		case 3 : b=0;
		break;
		default : printf("invalid choice\n");		          
	}
	getch();
}
	
    
}

