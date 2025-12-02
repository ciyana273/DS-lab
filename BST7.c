#include<stdio.h>
#include<stdlib.h>
struct node {
    int data;
    struct node *lchild, *rchild;
};
struct node *insert(struct node *root, int data) {
struct node *t1 = root, *t2 = NULL, *t;
while (t1 != NULL && t1->data != data) {
t2 = t1;
if (data < t1->data)
t1 = t1->lchild;
else
t1 = t1->rchild;
}
if (t1 != NULL) {
printf("Duplicate!!\n");
return root;
}
t = (struct node *)malloc(sizeof(struct node));
t->data = data;
t->lchild = t->rchild = NULL;
if (root == NULL)
root = t;
else {
if (data < t2->data)
t2->lchild = t;
else
t2->rchild = t;
}
printf("%d inserted\n", data);
return root;
}
void inorder(struct node *root) {
if (root != NULL) {
inorder(root->lchild);
printf("%d\t", root->data);
inorder(root->rchild);
}
}
struct node *search(struct node *root, int item) {
struct node *t = root;
while (t != NULL && t->data != item) {
if (item < t->data)
t = t->lchild;
else
t = t->rchild;
}
return t;
}
struct node *delete(struct node *root, int item) {
struct node *t = root, *par = NULL, *suc, *sucpar;
while (t != NULL && t->data != item) {
par = t;
if (item < t->data)
t = t->lchild;
else
t = t->rchild;
}
if (t == NULL) {
printf("%d not found\n", item);
return root;
}
if (t->lchild == NULL && t->rchild == NULL) {
if (par == NULL)
root = NULL;
else if (t == par->lchild)
par->lchild = NULL;
else
par->rchild = NULL;
}
else if (t->lchild == NULL || t->rchild == NULL) {
struct node *child = (t->lchild != NULL) ? t->lchild : t->rchild;
if (par == NULL)
root = child;
else if (t == par->lchild)
par->lchild = child;
else
par->rchild = child;
}
else {
sucpar = t;
suc = t->rchild;
while (suc->lchild != NULL) {
sucpar = suc;
suc = suc->lchild;
}
t->data = suc->data;
if (suc == sucpar->lchild)
sucpar->lchild = suc->rchild;
else
sucpar->rchild = suc->rchild;
t = suc;
}
free(t);
printf("%d deleted\n", item);
return root;
}

int main() {
struct node *t1, *t = NULL;
int data, opt;
do {
printf("\n1.Insert\n2.Display\n3.Search\n4.Delete\n5.Exit\n");
printf("Option: ");
scanf("%d", &opt);
switch (opt) {
case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                t = insert(t, data);
                break;
            case 2:
                inorder(t);
                printf("\n");
                break;
            case 3:
                printf("Item to search: ");
                scanf("%d", &data);
                t1 = search(t, data);
                if (t1 == NULL)
                    printf("Not found\n");
                else
                    printf("Item found\n");
                break;
            case 4:
                printf("Item to delete: ");
                scanf("%d", &data);
                t = delete(t, data);
                break;
            case 5:
                exit(0);
        }
    } while (1);
    return 0;
}

