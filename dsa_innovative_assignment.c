// DSA - Innovative Assignment
/* */
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
int max(int a,int b)
{
    return (a<b)?b:a;
}
/* Bank Structure for storing Information of Bank Users*/
struct Bank {
    char name[20];
    int id;
    double curr,save;
    double returns,debt;
};

struct Bank arr[10];/* Array Of Structure(Bank)*/
int n=0;
/* For Keeping Record of Number of Bank Accounts */
/* Node Structure for Binary Search Tree*/
struct Node {
    char name[20];
    int id;
    double curr,save;
    double returns,debt;
    struct Node* left;
    struct Node* right;
};

struct Node* root1=NULL;
struct Node* root2=NULL;
/* Creating New Node */
/* In Each Node data of 1 user will be stored in BST*/
struct Node* NEW(struct Bank ob)
{
        struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
        strcpy(temp->name,ob.name);
        temp->id=ob.id;
        temp->curr=ob.curr;temp->save=ob.save;
        temp->returns=ob.returns;temp->debt=ob.debt;
        temp->left=temp->right=NULL;
}
/* Displaying User Information According to Id Number*/
void display1(struct Bank ob)
{
    printf("Name : %s\n",ob.name);
    printf("Account No. : %d\n",ob.id);
    printf("Current Account = %0.3lf , Saving Account = %0.3lf\n",ob.curr,ob.save);
    printf("Profit Returns = %0.3lf , Debt = %0.3lf\n\n",ob.returns,ob.debt);
}

void display2(struct Node* root)
{
    if(!root)
        return;

    printf("Name : %s\n",root->name);
    printf("Account No. : %d\n",root->id);
    printf("Current Account = %0.3lf , Saving Account = %0.3lf\n",root->curr,root->save);
    printf("Profit Returns = %0.3lf , Debt = %0.3lf\n\n",root->returns,root->debt);
}
/* Comparing the height of left subtree and rightsubtree*/
int depth(struct Node* root)
{
    if(!root)
        return 0;
    return max(depth(root->left),depth(root->right)) + 1;
}
/* Inserting the node in the BST-1*/
struct Node* insert1(struct Node* root,struct Bank ob)
{
    if(!root)
    {
        root = NEW(ob);
        return root;
    }

    if(strcmp(ob.name,root->name) < 0)
        root->left=insert1(root->left,ob);
    else
        root->right=insert1(root->right,ob);

    return root;
}
/* Inserting the node in the BST-2*/
struct Node* insert2(struct Node* root,struct Bank ob)
{
    if(!root)
    {
        root = NEW(ob);
        return root;
    }

    if(ob.curr < root->curr)
        root->left=insert2(root->left,ob);
    else
        root->right=insert2(root->right,ob);

    return root;
}
/* Adding User Info in BST where each node represents 1 user*/
void add()
{
    if(n == 10)
    {
        printf("Accounts limit reached! You cant create more Accounts!\n\n");
        return;
    }

    struct Bank temp;
    strcpy(temp.name,"");
    temp.id=n+1;
    temp.curr=temp.save=temp.returns=temp.debt=0;

    printf("Name : ");
    fflush(stdin);
    gets(temp.name);

    printf("\nCurrent Account Initial Balance : \n");

    do {
        printf("Enter Value ( >= 0) : ");
        scanf("%lf",&temp.curr);
    } while(temp.curr < 0);

    printf("\nSaving Account Initial Balance : \n");
    do {
        printf("Enter Value ( >= 5000) : ");
        scanf("%lf",&temp.save);
    } while(temp.save < 5000);

    printf("\n");

    temp.returns = 0.1*temp.save;

    arr[n]=temp;

    root1=insert1(root1,arr[n]);
    root2=insert2(root2,arr[n]);

    n++;
}
/* Searching for Node In BST-1*/
struct Node* search1(struct Node* root,char name[])
{
    if(!root)
        return NULL;

    int k=strcmp(name,root->name);
    if(k < 0)
        return search1(root->left,name);
    else if(k > 0)
        return search1(root->right,name);

    return root;
}
/* Searching for node in BST-2*/
struct Node* search2(struct Node* root,int curr)
{
    if(!root)
        return NULL;

    if(curr < root->curr)
        return search2(root->left,curr);
    else if(curr > root->curr)
        return search2(root->right,curr);

    return root;
}
/* Deleting the node in BST-1*/
struct Node* delete_node1(struct Node* root,char name[])
{
    if(!root)
        return NULL;

    int k=strcmp(name,root->name);

    if(k < 0)
    {
        root->left=delete_node1(root->left,name);
        return root;
    }
    else if(k > 0)
    {
        root->right=delete_node1(root->right,name);
        return root;
    }

    if(!root->left)
    {
        struct Node* temp=root->right;
        root=NULL;
        free(root);
        return temp;
    }
    else if(!root->right)
    {
        struct Node* temp=root->left;
        root=NULL;
        free(root);
        return temp;
    }

    if(depth(root->left) > depth(root->right))
    {
        struct Node* temp=root->left;

        while(temp->right)
            temp=temp->right;

        strcpy(root->name,temp->name);
        root->id=temp->id;
        root->curr=temp->curr;root->save=temp->save;
        root->returns=temp->returns;root->debt=temp->debt;

        root->left=delete_node1(root->left,temp->name);
    }
    else
    {
        struct Node* temp=root->right;

        while(temp->left)
            temp=temp->left;

        strcpy(root->name,temp->name);
        root->id=temp->id;
        root->curr=temp->curr;root->save=temp->save;
        root->returns=temp->returns;root->debt=temp->debt;

        root->right=delete_node1(root->right,temp->name);
    }

    return root;
}

struct Node* delete_node2(struct Node* root,int curr)
{
    if(!root)
        return NULL;


    if(curr < root->curr)
    {
        root->left=delete_node2(root->left,curr);
        return root;
    }
    else if(curr > root->curr)
    {
        root->right=delete_node2(root->right,curr);
        return root;
    }

    if(!root->left)
    {
        struct Node* temp=root->right;
        root=NULL;
        free(root);
        return temp;
    }
    else if(!root->right)
    {
        struct Node* temp=root->left;
        root=NULL;
        free(root);
        return temp;
    }

    if(depth(root->left) > depth(root->right))
    {
        struct Node* temp=root->left;

        while(temp->right)
            temp=temp->right;

        strcpy(root->name,temp->name);
        root->id=temp->id;
        root->curr=temp->curr;root->save=temp->save;
        root->returns=temp->returns;root->debt=temp->debt;

        root->left=delete_node2(root->left,temp->curr);
    }
    else
    {
        struct Node* temp=root->right;

        while(temp->left)
            temp=temp->left;

        strcpy(root->name,temp->name);
        root->id=temp->id;
        root->curr=temp->curr;root->save=temp->save;
        root->returns=temp->returns;root->debt=temp->debt;

        root->right=delete_node2(root->right,temp->curr);
    }

    return root;
}

void delete_node(int id)
{
    if(id<1 || id>n)
    {
        printf("Invalid Id!\n\n");
        return;
    }

    id--;
    n--;

    root1=delete_node1(root1,arr[id].name);
    root2=delete_node2(root2,arr[id].curr);

    for(int i=id;i<n;i++)
        arr[i]=arr[i+1];
}

void inorder1(struct Node* root)
{
    if(!root) return;
    inorder1(root->left);
    display2(root);
    inorder1(root->right);
}

void inorder2(struct Node* root)
{
    if(!root) return;
    inorder2(root->right);
    display2(root);
    inorder2(root->left);
}

void withdraw(int id,int val)
{
    if(id<1 || id>n)
    {
        printf("Invalid Id!\n\n");
        return;
    }

    id--;

    int choice = 0;
    printf("Current Account = 1 , Savings Account = 2\n");
    printf("Option : ");
    scanf("%d",&choice);
    printf("\n");

    if(choice == 1)
    {
        if(val > arr[id].curr)
        {
            printf("You cannot withdraw more than your Current balance !\n\n");
            return;
        }

        root1=delete_node1(root1,arr[id].name);
        root2=delete_node2(root2,arr[id].curr);

        arr[id].curr-=val;

        root1=insert1(root1,arr[id]);
        root2=insert2(root2,arr[id]);
    }
    else if(choice == 2)
    {
        if(val > arr[id].save-5000)
        {
            printf("You have to keep a minimum balance of 5000 in your Savings account , you cannot withdraw more than that !\n\n");
            return;
        }

        root1=delete_node1(root1,arr[id].name);
        root2=delete_node2(root2,arr[id].curr);

        arr[id].save-=val;
        arr[id].returns=0.1*arr[id].save;

        root1=insert1(root1,arr[id]);
        root2=insert2(root2,arr[id]);
    }
    else
    {
        printf("Invalid Option !\n\n");
        return;
    }

    printf("Transaction Successful !\n\n");
}
/* */
void deposit(int id,int val)
{
    if(id<1 || id>n)
    {
        printf("Invalid Id!\n");
        return;
    }

    id--;

    int choice = 0;
    printf("Current Account = 1 , Savings Account = 2\n");
    printf("Option : ");
    scanf("%d",&choice);
    printf("\n");

    if(choice == 1)
    {
        root1=delete_node1(root1,arr[id].name);
        root2=delete_node2(root2,arr[id].curr);

        arr[id].curr+=val;

        root1=insert1(root1,arr[id]);
        root2=insert2(root2,arr[id]);
    }
    else if(choice == 2)
    {
        root1=delete_node1(root1,arr[id].name);
        root2=delete_node2(root2,arr[id].curr);

        arr[id].save+=val;
        arr[id].returns=0.1*arr[id].save;

        root1=insert1(root1,arr[id]);
        root2=insert2(root2,arr[id]);
    }
    else
    {
        printf("Invalid Option !\n\n");
        return;
    }

    printf("Deposit Successful !\n\n");
}

void balance(int id)
{
    if(id<1 || id>n)
    {
        printf("Invalid Id!\n\n");/* */
        return;
    }

    id--;
    printf("Name : %s\n",arr[id].name);
    printf("Current Balance : %0.3lf\n",arr[id].curr);
    printf("Savings Balance : %0.3lf\n\n",arr[id].save);
}
/* Function For Checking If User is eligible for loan or not (Criteria-->Loan can be taken for amount>=1000)*/
void loan(int id,int val)
{
    if(id<1 || id>n)/* Out Of Bound*/
    {
        printf("Invalid Id!\n\n");
        return;
    }
    else if(val < 1000)
    {
        printf("Loan only valid for value >=1000 !\n\n");
        return;
    }

    id--;
     /*Deleting the Node So that  */
    root1=delete_node1(root1,arr[id].name);
    root2=delete_node2(root2,arr[id].curr);

    arr[id].curr+=val;/* Inserting Money In Current Account*/
    arr[id].debt+=val*1.15;/* Loan is available at 15%interest P.A.*/
    /* Inserting The Node Again*/
    root1=insert1(root1,arr[id]);
    root2=insert2(root2,arr[id]);

    printf("Amount transferred to your current account!\n");
    printf("Total Current Debt : %lf\n\n",arr[id].debt);
}
/* Money Transfer From One Account To Another*/
void transfer(int a,int b,int val) {
    if(a>n || b>n || a<1 || b<1)
    {
        printf("Invalid Account Nos. !\n\n");
        return;
    }

    a--;b--;

    if(val > arr[a].curr)
    {
        printf("Value to be transferred is greater than Current Account Balance of %d !\n\n",a+1);
        return;
    }
/*Deleting Both the nodes */
    root1=delete_node1(root1,arr[a].name);
    root2=delete_node2(root2,arr[a].curr);

    root1=delete_node1(root1,arr[b].name);
    root2=delete_node2(root2,arr[b].curr);
/* Updating the values of current node*/
    arr[a].curr-=val;
    arr[b].curr+=val;
/* Inserting The Updated Nodes*/
    root1=insert1(root1,arr[a]);
    root2=insert2(root2,arr[a]);

    root1=insert1(root1,arr[b]);
    root2=insert2(root2,arr[b]);

    printf("Money Transfer Successful from Account %d to Account %d !\n\n",a+1,b+1);
}

int main()
{
    printf("Welcome to Bank/ATM Interface !\n\n");
    int choice=0;
    while(choice!=6)
    {
        printf("*************************\n");
        printf("1. Create New Account\n");
        printf("2. Choose Account\n");
        printf("3. Display All Accounts Details in ID Order\n");
        printf("4. Display All Accounts Details in Naming Order\n");
        printf("5. Display All Accounts Details in Descending Order of Current Balance\n");
        printf("6. Exit\n");
        printf("*************************\n\n");

        printf("Option 1 : ");
        scanf("%d",&choice);

        printf("\n");

        if(choice == 1)
            add();
        else if(choice == 2)
        {
            if(!n)
            {
                printf("No Accounts Available !\n\n");
                continue;
            }

            printf("Choose account : \n");
            int x = 0;
            do {
                printf("Select from (1 - %d) : ",n);
                scanf("%d",&x);
            } while(x<1 && x>n);

            x--;

            printf("\n*************************\n");
            printf("(1) Withdraw\n");
            printf("(2) Check Balance\n");
            printf("(3) Deposit\n");
            printf("(4) Loan\n");
            printf("(5) Money Transfer\n");
            printf("*************************\n\n");

            printf("Option 2 : ");
            int choice2;
            scanf("%d",&choice2);

            int val=0;
            if(choice2 == 1)
            {
                printf("\nEnter the amount to be Withdrawn : \n");
                val=0;

                do {
                    printf("Enter Value ( >= 0) : ");
                    scanf("%d",&val);
                } while(val<0);

                printf("\n");

                withdraw(x+1,val);
            }
            else if(choice2 == 2)
            {
                printf("Account %d Balance : \n\n",x+1);
                balance(x+1);
            }
            else if(choice2 == 3)
            {
                printf("\nEnter the amount to be Deposited : \n");
                val=0;

                do {
                    printf("Enter Value ( >= 0) : ");
                    scanf("%d",&val);
                } while(val<0);

                printf("\n");

                deposit(x+1,val);
            }
            else if(choice2 == 4)
            {
                printf("\nEnter the amount to be Lent : \n");
                val=0;

                do {
                    printf("Enter Value >=0 : ");
                    scanf("%d",&val);
                } while(val<0);

                printf("\n");

                loan(x+1,val);
            }
            else if(choice2 == 5)
            {
                printf("\nEnter Account no. : \n");
                int y=0;

                do {
                    printf("Select from (1 - %d) : ",n);
                    scanf("%d",&y);
                } while(y<1 && y>n);

                printf("\nEnter the amount to be Transferred : \n");
                val=0;

                do {
                    printf("Enter Value >=0 : ");
                    scanf("%d",&val);
                } while(val<0);

                printf("\n");

                transfer(x+1,y,val);
            }
            else
                printf("Invalid Option 2 !\n\n");
        }
        else if(choice == 3)
        {
            for(int i=0;i<n;i++)
                display1(arr[i]);
        }
        else if(choice == 4)
            inorder1(root1);
        else if(choice == 5)
            inorder2(root2);
        else if(choice == 6)
        {
            printf("Exiting .... \n\n");
            break;
        }
        else
            printf("Invalid Option 1 !\n\n");
    }

    return 0;
}

