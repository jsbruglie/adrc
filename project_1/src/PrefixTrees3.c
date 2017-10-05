#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define NOT_FOUND 0
#define KEEP 1
#define DELETE -1

struct node_one_bit
{
	int						next_hop;
	struct node_one_bit		*zero;
	struct node_one_bit		*one;
};

struct node_two_bit
{
	int						next_hop;
	struct node_two_bit		*zero_zero;
	struct node_two_bit		*zero_one;
	struct node_two_bit		*one_zero;
	struct node_two_bit		*one_one;
};

struct tree_one_bit
{
	struct node_one_bit		*root;
};

struct tree_two_bit
{
	struct node_two_bit		*root;
};


struct node_one_bit * create_node_one_bit(int next_hop)
{
	struct node_one_bit *node = NULL;

	node = (struct node_one_bit *) malloc(sizeof(struct node_one_bit));

	node->next_hop = next_hop;
	node->zero = NULL;
	node->one = NULL;

	return node;
}

struct node_two_bit * create_node_two_bit(int next_hop)
{
	struct node_two_bit *node = NULL;

	node = (struct node_two_bit *) malloc(sizeof(struct node_two_bit));

	node->next_hop = next_hop;
	node->zero_zero = NULL;
	node->zero_one = NULL;
	node->one_zero = NULL;
	node->one_one = NULL;

	return node;
}

struct node_one_bit * insert_node_one_bit(struct node_one_bit *root, char *prefix, int next_hop)
{
	struct node_one_bit *aux = NULL;

	aux = root;

	if(root == NULL)
	{
		aux = create_node_one_bit(EMPTY);
	}

	if((*prefix) == '0')
	{
		aux->zero = insert_node_one_bit(aux->zero, prefix+1, next_hop);
	}
	else if((*prefix) == '1')
	{
		aux->one = insert_node_one_bit(aux->one, prefix+1, next_hop);
	}
	else
	{
		aux->next_hop = next_hop;
	}

	return aux;
}

struct node_two_bit * insert_node_two_bit(struct node_two_bit *root, char *prefix, int next_hop)
{
	struct node_two_bit *aux = NULL;

	aux = root;

	if(root == NULL)
	{
		aux = create_node_two_bit(EMPTY);
	}

	if(((*prefix) == '0') && ((*(prefix+1)) == '0'))
	{
		aux->zero_zero = insert_node_two_bit(aux->zero_zero, prefix+2, next_hop);
	}
	else if(((*prefix) == '0') && ((*(prefix+1)) == '1'))
	{
		aux->zero_one = insert_node_two_bit(aux->zero_one, prefix+2, next_hop);
	}
	else if(((*prefix) == '1') && ((*(prefix+1)) == '0'))
	{
		aux->one_zero = insert_node_two_bit(aux->one_zero, prefix+2, next_hop);
	}
	else if(((*prefix) == '1') && ((*(prefix+1)) == '1'))
	{
		aux->one_one = insert_node_two_bit(aux->one_one, prefix+2, next_hop);
	}
	else if ((*prefix) == '\0')
	{
		aux->next_hop = next_hop;
	}
	else
	{}

	return aux;
}

int remove_node_one_bit(struct node_one_bit *root, char *prefix)
{
	int aux = 0;

	if(root == NULL)
	{
		return NOT_FOUND;
	}

	if((*prefix) == '0')
	{
		aux = remove_node_one_bit(root->zero, ++prefix);
		if(aux == DELETE)
		{
			free(root->zero);
			root->zero = NULL;

			if((root->next_hop == 0) && (root->one == NULL))
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
		aux = remove_node_one_bit(root->one, ++prefix);
		if(aux == DELETE)
		{
			free(root->one);
			root->one = NULL;

			if((root->next_hop == 0) && (root->zero == NULL))
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

	else
	{
		if((root->zero == NULL) && (root->one == NULL))
		{
			return DELETE;
		}
		else
		{
			root->next_hop = 0;
			return KEEP;
		}

	}
}

void print_tree_one_bit(struct node_one_bit *root, char *prefix, int depth)
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
		print_tree_one_bit(root->zero, prefix, depth+1);
		prefix[depth] = '1';
		print_tree_one_bit(root->one, prefix, depth+1);
	}
}

int lookup(struct node_one_bit *root, char *address)
{
	if(root == NULL)
	{
		return NOT_FOUND;
	}

	if((*address) == '0')
	{
		return lookup(root->zero, ++address);
	}
	else if((*address) == '1')
	{
		return lookup(root->one, ++address);
	}
	else
	{
		return root->next_hop;
	}

}


void * convert(struct node_one_bit *root, struct node_two_bit **root2, char *prefix, int depth)
{
	if(root != NULL)
	{
		if(root->next_hop != 0)
		{
			if(depth % 2 == 0)
			{
				prefix[depth] = '\0';
				*root2 = insert_node_two_bit(*root2, prefix, root->next_hop);
			}
			else
			{
				prefix[depth] = '0';
				*root2 = insert_node_two_bit(*root2, prefix, root->next_hop);
				prefix[depth] = '1';
				*root2 = insert_node_two_bit(*root2, prefix, root->next_hop);
				prefix[depth] = '\0';
			}
		}

		prefix[depth] = '0';
		convert(root->zero, root2, prefix, depth+1);
		prefix[depth] = '1';
		convert(root->one, root2, prefix, depth+1);
		prefix[depth] = '\0';
	}

}



int main(int argc, char *argv[])
{

	struct node_one_bit *root = NULL;
	struct node_two_bit *root2 = NULL;

	root = insert_node_one_bit(root, "10011", 5);
	root = insert_node_one_bit(root, "111", 3);
	root = insert_node_one_bit(root, "101", 2);
	root = insert_node_one_bit(root, "1", 1);
	root = insert_node_one_bit(root, "011", 9);

	char prefix[17] = "\0";
	char prefix2[17] = "\0";

	print_tree_one_bit(root, prefix, 0);

	fprintf(stdout, "%d\n", lookup(root, "10011"));

	convert(root, &root2, prefix2, 0);

}



