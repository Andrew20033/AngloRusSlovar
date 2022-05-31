#include <iostream>
#include <string.h>
#include <locale.h>
#include <stdio.h>

using namespace std;

struct Tree
{
    char eng[30];
    char rus[30];
    int n;
    Tree* left;
    Tree* right;
};

Tree* Add(Tree* root, char a[30], char b[30])
{
    int l = strlen(a), i; int j = strlen(b);
    if (root)
    {
        bool f = false; Tree* p = root; Tree* r;
        while ((p) && !f)
        {
            r = p;


            if (strcmp(r->eng, a) == 0) { f = true; }
            if (strcmp(r->eng, a) > 0) p = p->right; else p = p->left;

        }if (!f)
        {
            Tree* Add = new Tree;
            strcpy(Add->eng, a);
            strcpy(Add->rus, b);
            Add->left = 0;
            Add->right = 0;
            if (strcmp(r->eng, a) > 0) { r->right = Add; }
            else r->left = Add;
        }
    }
    else
    {
        root = new Tree;
        strcpy(root->eng, a);
        strcpy(root->rus, b);
        root->left = 0;
        root->right = 0;
    }
    return root;
}




Tree* Delete(Tree* root, char a[30])
{
    if (root)
    {
        if (strcmp(root->eng, a) < 0)
            root->right = Delete(root->right, a);
        else
            if (strcmp(root->eng, a) > 0)
                root->left = Delete(root->left, a);
            else
            {
                Tree* q = root;
                if (root->left == 0)
                {
                    root = root->right;
                    delete q;
                }
                else
                    if (root->right == 0)
                    {
                        root = root->left;
                        delete q;
                    }
                    else
                    {
                        q = q->left;
                        if (q->right == NULL)
                        {
                            strcpy(root->eng, q->eng);
                            strcpy(root->rus, q->rus);
                            root->n = q->n;
                            root->left = q->left;
                            delete q;
                        }
                        else
                        {
                            Tree* r = q;
                            while (q->right)
                            {
                                r = q;
                                q = q->right;
                            }
                            strcpy(root->eng, q->eng);
                            strcpy(root->rus, q->rus);
                            root->n = q->n;
                            r->right = q->left;
                            delete q;
                        }
                    }
            }
    }
    return root;
};


Tree* AddN(Tree* root, char a[30], char b[30], int n)
{
    if (root)
    {
        bool f = false; Tree* p = root; Tree* r;
        while ((p) && !f)
        {
            r = p;


            if (r->n == n) { f = true; }
            if (r->n > n) p = p->right; else p = p->left;

        }if (!f)
        {
            Tree* Add = new Tree;
            strcpy(Add->eng, a);
            strcpy(Add->rus, b);
            Add->n = n;
            Add->left = 0;
            Add->right = 0;
            if (r->n > n) { r->right = Add; }
            else r->left = Add;
        }
    }
    else
    {
        root = new Tree;
        strcpy(root->eng, a);
        strcpy(root->rus, b);
        root->n = n;
        root->left = 0;
        root->right = 0;
    }
    return root;
}


void Show(Tree* root)
{
    if (root)
    {
        Show(root->right);
        cout << root->eng << " - " << root->rus << " [" << root->n << "]" << endl;
        Show(root->left);
    }
}




void Print(Tree* root)
{
    if (root)
    {
        cout << root->eng << " - " << root->rus << " [" << root->n << "]" << endl;
        Print(root->left);
        Print(root->right);
    }
}

Tree* MakeFindTree(int n)
{
    Tree* root = NULL; int k = 0;
    char a[30], b[30];
    for (int i = 0; i < n; i++)
    {
        cout << "Vvedite ang slovo: ";
        while (k == 0) { cin >> a; if ((int(a[0]) >= int('A')) && (int(a[0]) <= int('z'))) { k++; } else { cout << "Povtorite vvod" << endl; } }
        k = 0;
        cout << "Vvedite rus slovo: ";
        cin >> b;
        root = Add(root, a, b);
    }
    return root;
}

void VivodEng(Tree* root, char a[30])
{
    if (root)
    {
        if (strcmp(root->eng, a) == 0) {
            cout << root->eng << " - " << root->rus << " [" << root->n << "]" << endl;
            root->n = root->n + 1;
        }if (strcmp(root->eng, a) > 0)
            VivodEng(root->right, a); else
            VivodEng(root->left, a);
    }
}

void VivodRus(Tree* root, char a[30])
{
    if (root)
    {
        if (strcmp(root->rus, a) == 0) {
            cout << root->rus << " - " << root->eng << " [" << root->n << "]" << endl;
            root->n = root->n + 1;
        }if (strcmp(root->rus, a) > 0)
            VivodRus(root->right, a); else
            VivodRus(root->left, a);
    }
}


Tree* NovTree(Tree* root, Tree* root2, int n)
{
    if (root)
    {
        char a[30]; strcpy(root->eng, a);
        if (n < root->n) { n = root->n; strcpy(root->eng, a); }
        root = NovTree(root->left, root2, root->n);
        root = NovTree(root->right, root2, root->n);
        root2 = AddN(root2, root->eng, root->rus, n);
        Delete(root, a);
    }
    return root2;
}


int main()
{
    Tree* root = NULL; Tree* root2 = NULL;
    cout << "Dobro Pogalovat! " << endl;
    int n, k; char a[30];
    cout << "vvedite col el= ";
    cin >> n;
    root = MakeFindTree(n);
    Show(root);
    n = 0;

    while (a[0] != '1') {
        n = 0; cout << "Vvedite slovo ili '1' dlya vivoda slov:  ";
        cin >> a; if (a[0] != '1')
        {
            if ((int(a[0]) > int('A') - 1) && (int(a[0]) < int('z') + 1))
            {
                VivodEng(root, a); n++;
            }
            else if ((int(a[0]) > int('À') - 1) && (int(a[0]) < int('ÿ') + 1)) { VivodRus(root, a); n++; }
            else if (n == 0) { cout << "Net takogo slova " << endl; }
        }
    }

    cout << "Slovar posle raboti: " << endl;
    Show(root);

    cout << "Noviy Slovar : " << endl;
    while (root) {
        n = root->n;
        root2 = NovTree(root->left, root2, n);
        root2 = NovTree(root->right, root2, n);
    }
    Show(root2);
    cin >> n;
    return 0;
}