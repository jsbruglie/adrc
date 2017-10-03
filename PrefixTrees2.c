#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_NODE 0
#define NOT_FOUND 0
#define KEEP 1
#define DELETE -1

struct node
{
	int				next_hop;
	struct node		*left;
	struct node		*right;
};

struct binary_tree
{
	struct node		*root;
};

struct node * create(int next_hop)
{
	struct node *new = NULL;

	new = (struct node *) malloc(sizeof(struct node));

	new->next_hop = next_hop;
	new->left = NULL;
	new->right = NULL;

	return new;
}

struct node * insert(struct node *root, char *prefix, int next_hop)
{
	struct node *aux;

	aux = root;

	if(root == NULL)
	{
		aux = create(EMPTY_NODE);
	}

	if((*prefix) == '\0')
	{
		aux->next_hop = next_hop;
	}
	else if((*prefix) == '0')
	{
		aux->left = insert(aux->left, ++prefix, next_hop);
	}
	else if((*prefix) == '1')
	{
		aux->right = insert(aux->right, ++prefix, next_hop);
	}

	return aux;
}

int delete(struct node *root, char *prefix)
{
	int aux = 0;

	if(root == NULL)
	{
		return NOT_FOUND;
	}

	if((*prefix) == '\0')
	{
		if((root->left == NULL) && (root->right == NULL))
		{
			return DELETE;
		}
		else
		{
			root->next_hop = 0;
			return KEEP;
		}

	}
	else if((*prefix) == '0')
	{
		aux = delete(root->left, ++prefix);
		if(aux == DELETE)
		{
			free(root->left);
			root->left = NULL;

			if((root->next_hop == 0) && (root->right == NULL))
			{
				return DELETE;
			}
			else
			{
				return KEEP;
			}
		}
		else
		{
			return aux;
		}
	}
	else if((*prefix) == '1')
	{
		aux = delete(root->right, ++prefix);
		if(aux == DELETE)
		{
			free(root->right);
			root->right = NULL;

			if((root->next_hop == 0) && (root->left == NULL))
			{
				return DELETE;
			}
			else
			{
				return KEEP;
			}
		}
		else
		{
			return aux;
		}
	}
	return aux;
}

void print(struct node *root, char *prefix, int depth)
{
	if(root != NULL)
	{
		if(root->next_hop != 0)
		{
			prefix[depth] = '\0';
			fprintf(stdout, "%s %d\n", prefix, root->next_hop);
		}
		else
		{
			//fprintf(stdout, "X\n");
		}
		prefix[depth] = '0';
		print(root->left, prefix, depth+1);
		prefix[depth] = '1';
		print(root->right, prefix, depth+1);
	}
}

int main(int argc, char *argv[])
{

	struct node *root = NULL;

	root = insert(root, "10011", 5);
	root = insert(root, "111", 3);
	root = insert(root, "101", 2);
	root = insert(root, "1", 1);
	root = insert(root, "011", 9);

	char prefix[17] = "\0";

	print(root, prefix, 0);

}











