#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *lchild, *rchild;
};

struct node* insert(struct node* root, int data) {
    struct node *t1 = root, *t2 = NULL, *t;

    while (t1 != NULL) {
        t2 = t1;
        if (data == t1->data) {
            printf("Duplicate\n");
            return root;
        }
        else if (data < t1->data)
            t1 = t1->lchild;
        else
            t1 = t1->rchild;
    }

    t = (struct node*)malloc(sizeof(struct node));
    t->data = data;
    t->lchild = t->rchild = NULL;

    if (t2 == NULL)
        root = t;
    else if (data < t2->data)
        t2->lchild = t;
    else
        t2->rchild = t;

    printf("%d is inserted\n", data);
    return root;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->lchild);
        printf("%d ", root->data);
        inorder(root->rchild);
    }
}
struct node* search(struct node *root, int item) {
    struct node *t = root;
    while (t != NULL && t->data != item) {
        if (item < t->data)
            t = t->lchild;
        else
            t = t->rchild;
    }
    return t;
}

struct node* delete(struct node *root, int item) {
    if (root == NULL) {
        printf("%d not found\n", item);
        return root;
    }

    if (item < root->data)
        root->lchild = delete(root->lchild, item);

    else if (item > root->data)
        root->rchild = delete(root->rchild, item);

    else {
        if (root->lchild == NULL) {
            struct node *temp = root->rchild;
            free(root);
            return temp;
        }
        else if (root->rchild == NULL) {
            struct node *temp = root->lchild;
            free(root);
            return temp;
        }

        struct node *succ = root->rchild;
        while (succ->lchild != NULL)
            succ = succ->lchild;

        root->data = succ->data;
        root->rchild = delete(root->rchild, succ->data);
    }
    return root;
}

int main() {
    struct node *t1, *t = NULL;
    int data, opt;

    do {
        printf("\n1. Insert\n");
        printf("2. Display\n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. Exit\n");
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

            default:
                printf("Invalid option\n");
        }

    } while (1);

    return 0;
}

