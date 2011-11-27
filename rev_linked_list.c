#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char val;
    struct node *next;
} node;

void print_list(node *root)
{
    while(root != NULL) {
        printf("%c ", root->val);
        root = root->next;
    }
    printf("\n");
}

node *reverse_list(node *root)
{
    node *cur = root;
    node *rev = NULL;
    node *last;
    
    while(cur != NULL) {
        last = rev;
        rev = cur;
        cur = cur->next;
        rev->next = last;
    }
    
    return rev;
}

int main()
{
    node d = { 'd', NULL };
    node c = { 'c', &d };
    node b = { 'b', &c };
    node a = { 'a', &b };
    
    node *root = &a;
    print_list(root);
    root = reverse_list(root);
    print_list(root);
    
    return 0;
}
