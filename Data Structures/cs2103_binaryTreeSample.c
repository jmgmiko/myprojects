#include <stdio.h>
#include <stdlib.h>

struct node
{
  int key_value;
  struct node *left;
  struct node *right;
};

void insert(int key, struct node **leaf);
struct node *search(int key, struct node *leaf);
void destroy_tree(struct node *leaf);

int main ()
{
	struct node *root=NULL;
	struct node *look;
	insert (11, &root);
	insert (25, &root);
	insert (8, &root);
	insert (15, &root);
	insert (10, &root);
	insert (4, &root);
	insert (31, &root);
	look=search (4, root);
	printf ("%d", look->key_value);
	getch ();
	destroy_tree(root);
	return 0;
}

void insert(int key, struct node **leaf)
{
    struct node **trav;
    for (trav=leaf; *trav!=NULL; ) {
    	if (key>(*trav)->key_value) {
    		trav=&(*trav)->right;
		}
		else {
			trav=&(*trav)->left;
		}
	}
	*trav=malloc (sizeof (struct node *));
	(*trav)->key_value=key;
	(*trav)->left=NULL;
	(*trav)->right=NULL;
}

struct node *search(int key, struct node *leaf)
{
  if( leaf !=NULL )
  {
      if(key==leaf->key_value)
      {
          return leaf;
      }
      else if(key<leaf->key_value)
      {
          return search(key, leaf->left);
      }
      else 
      {
          return search(key, leaf->right);
      }
  }
  else {
  	return NULL;
  }
}

void destroy_tree(struct node *leaf)
{
  if( leaf != 0 )
  {
      destroy_tree(leaf->left);
      destroy_tree(leaf->right);
      free( leaf );
  }
}
