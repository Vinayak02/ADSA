#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;
struct node
{
	int info;
	struct node *llink;
	struct node *rlink;
};
typedef struct node *NODE;
NODE root;
NODE getnode()
{
	NODE x;
	x=(NODE)malloc(sizeof(struct node));
	if(x==NULL)
	{
	printf("Out of memory\n");
	exit(0);
	}
	return x;
}
NODE insert(int item,NODE root);
NODE search(int item,NODE root);
NODE deletee(int item,NODE root);
void recursive_inorder(NODE root);
void recursive_preorder(NODE root);
void recursive_postorder(NODE root);
void iterative_inorder(NODE root);
void iterative_preorder(NODE root);
void iterative_postorder(NODE root);
void iterative_levelorder(NODE root);
int main()
{
	int ch=1,n,item;
	NODE s;
	while(ch)
	{
		printf("OPERATIONS : \n1.Inserting a node\n2.Searching a node\n3.Deleting a node\n4.Pre-Order Traversal\n5.Post-Order Traversal\n6.In-Order Traversal\n7.Exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1 :printf("Enter the item that you want to insert : ");
					scanf("%d",&item);
					root=insert(item,root);
					break;
			case 2 :printf("Enter the item that you want to search : ");
					scanf("%d",&item);
					s=search(item,root);
					if(s==NULL)
						printf("The element is not present in the tree\n");
					else
						printf("The element %d is found!\n", s->info);
					break;
			case 3 :printf("Enter the item that you want to delete : ");
					scanf("%d",&item);
					root=deletee(item,root);
					if(root == NULL)
					printf("Item is not present in the tree.\n");
					else
					printf("The element has been deleted.\n");
					break;
			case 4 :recursive_preorder(root);
					printf("\n");
					break;
			case 5 :recursive_postorder(root);
					printf("\n");
					break;
			case 6 :recursive_inorder(root);
					printf("\n");
					break;
			default :ch=0;
		}
	}
	return 0;
}
NODE insert(int item,NODE root)
{
	NODE temp,cur,parent;
	temp=getnode();
	temp->info=item;
	temp->llink=NULL;
	temp->rlink=NULL;
	if(root==NULL)
		return temp;
	cur=root;
	while(cur!=NULL)
	{
		parent = cur;
		if(cur->info>item)
		cur=cur->llink;
		else if(cur->info<item)
		cur=cur->rlink;
	}
	if(parent->info>item)
		parent->llink=temp;
	else
		parent->rlink=temp;
	return root;
}
NODE search(int item,NODE root)
{
	NODE cur;
	cur=root;
	while(cur!=NULL)
	{
		if(cur->info==item)
			break;
		else if(cur->info>item)
			cur=cur->llink;
		else
			cur=cur->rlink;
	}
	return cur;
}
NODE deletee(int item,NODE root)
{
	NODE cur,parent,suc,q;
	if(root==NULL)
	{
		printf("Tree doesn't exist!\n");
		return root;
	}
	parent=NULL;
	cur=root;
	while(cur!=NULL)
	{
		if(cur->info==item)
			break;
		parent=cur;
		if(cur->info>item)
			cur=cur->llink;
		else
			cur=cur->rlink;
	}
	if(cur==NULL)
	{
		printf("Item not found\n");
		return root;
	}
	if(cur->llink==NULL)
		q=cur->rlink;
	else if(cur->rlink==NULL)
		q=cur->llink;
	else
	{
		suc=cur->rlink;
		while(suc->llink!=NULL)
		suc=suc->llink;
		q=cur->rlink;
		suc->llink=cur->llink;
	}
	if(q==NULL)
	{
		free(cur);
		return root;
	}
	else if(parent->llink==cur)
		parent->llink=q;
	else
		parent->rlink=q;
	free(cur);
	return root;
}
void recursive_inorder(NODE root)
{
	if(root==NULL)
	return;
	recursive_inorder(root->llink);
	printf("->%d",root->info);
	recursive_inorder(root->rlink);
}
void recursive_preorder(NODE root)
{
	if(root==NULL)
	return;
	printf("->%d",root->info);
	recursive_preorder(root->llink);
	recursive_preorder(root->rlink);
}
void recursive_postorder(NODE root)
{
	if(root==NULL)
	return;
	recursive_postorder(root->llink);
	recursive_postorder(root->rlink);
	printf("->%d",root->info);
}
void iterative_levelorder(NODE root)
{
	queue<NODE> q;
	q.push(root);
	NODE cur, a;
	while(!q.empty())
	{
		cur = q.top();
		cout<<cur->info<<"->";
		q.pop();
		a = q.top();
		if(a->llink != NULL)
			q.push(a->llink);
		if(a->rlink != NULL)
			q.push(a->rlink);
	}
}