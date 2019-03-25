#include<iostream>
using namespace std;
struct node
{
	int info;
	struct node *rlink;
	struct node *llink;
	int height;
};
typedef struct node *NODE;
int height(NODE x)
{
	if(x == NULL)
		return 0;
	return x->height;
}
int max(int a, int b)
{
	return a>b?a:b;
}
NODE getnode()
{
	NODE x;
	x = (NODE)malloc(sizeof(struct node));
	if(x == NULL)
	{
		cout<<"Out of memory!"<<endl;
		exit(0);
	}
	return x;
}
NODE rightrotate(NODE x)
{
	NODE y = x->llink;
	NODE R1 = y->rlink;
	y->rlink = x;
	x->llink = R1;
	y->height = 1 + max(height(y->llink), height(y->rlink));
	x->height = 1 + max(height(x->llink), height(x->rlink));
	return y;
}
NODE leftrotate(NODE x)
{
	NODE y = x->rlink;
	NODE L1 = y->llink;
	y->llink = x;
	x->rlink = L1;
	y->height = 1 + max(height(y->llink), height(y->rlink));
	x->height = 1 + max(height(x->llink), height(x->rlink));
	return y;
}
NODE newNode(int item)
{	
	NODE x = getnode();
	x->info = item;
	x->rlink = NULL;
	x->llink = NULL;
	x->height = 1;
	return x;
}
int balanceFactor(NODE x)
{
	if(x == NULL)
		return 0;
	return (height(x->llink) - height(x->rlink));
}
NODE insert(NODE x, int item)
{
	if(x == NULL)
		return newNode(item);
	if(x->info > item)
		x->llink = insert(x->llink, item);
	else if(x->info < item)
		x->rlink = insert(x->rlink, item);
	else
		return x;
	x->height = 1 + max(height(x->llink), height(x->rlink));
	int balance = balanceFactor(x);
	if(balance > 1 && item < x->llink->info) //L-L Case
		return rightrotate(x);
	if(balance < -1 && item > x->rlink->info) //R-R Case
		return leftrotate(x);
	if(balance > 1 && item > x->llink->info) //L-R Case
	{
		x->llink = leftrotate(x->llink);
		return rightrotate(x);
	}
	if(balance < -1 && item < x->rlink->info) //R-L Case
	{
		x->rlink = rightrotate(x->rlink);
		return leftrotate(x);
	}
	return x;
}
void preOrder(NODE root)  
{  
    if(root != NULL)  
    {  
        cout << root->info << " ";  
        preOrder(root->llink);  
        preOrder(root->rlink);  
    }  
}  
int main()
{
	NODE root = NULL;
	int n, item, ch = 1;
	while(ch == 1)
	{
		cout<<"1. Insert an item\n2. Preorder Traversal\n3.Exit\n";
		cin>>n;
		switch(n)
		{
			case 1: cout<<"Enter the item to be inserted in AVL : ";
				cin>>item;
				root = insert(root, item);
				cout<<"Item is inserted!"<<endl;
				break;
			case 2: cout << "Preorder traversal of the constructed AVL tree is \n";
	    			preOrder(root);
				cout<<endl;
				break;
			case 3: ch = 0;
		}
	}
	return 0;
}  
  
