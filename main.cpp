#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

struct cvor
{
    int info;
    struct cvor *left, *right, *pr;
};

int *unos2(int k, int a, int b)
{
    srand((unsigned) time(nullptr));
    int j, pom, *K = new int [k];

    for(int i = 0; i < k; i++)
    {
        pom = a + rand() % (b - a);

        for(j = i - 1; j >= 0 and K[j] > pom; j--)
            K[j + 1] = K[j];
        K[j + 1] = pom;
    }

    return K;
}

cvor* prethodnik(cvor *tr)
{
    cvor *prev = tr;
    if(tr -> left)
        for(cvor *i = tr -> left; i; prev = i, i = i -> right);

    return prev;
}

void ubaciStablo(int key, cvor *&root)
{
    cvor *novi = new cvor;
    novi -> left = nullptr;
    novi -> right = nullptr;
    novi -> info = key;

    cvor *tr = root, *prev = root;
    while (tr != nullptr)
    {
        if(tr -> info == key)
        {
            prev = prethodnik(tr);
            break;
        }

        prev = tr;
        if (tr -> info < key)
            tr = tr -> right;
        else
            tr = tr -> left;
    }
    novi -> pr = prev;

    if(!prev)
        root = novi;

    else if(prev -> info < key)
    {
        novi -> right = prev -> right;
        prev -> right = novi;
    }

    else
    {
        novi -> left = prev -> left;
        prev -> left = novi;
    }
}

void kreirajStablo(int *K, int n, cvor *&root)
{
    int first, second, mid;
    stack <pair <int, int>> stack;
    stack.push( {0, n - 1});

    while(!stack.empty())
    {
        first = stack.top().first;
        second =stack.top().second;
        stack.pop();

        if(first <=second)
        {
            mid = (second + first)/ 2;

            ubaciStablo(K[mid], root);
            stack.push({mid +1, second} );
            stack.push( {first, mid -1});
        }
    }
}

int pretraziStablo(int key, int &br, cvor *root)
{
    cvor *tr = root;
    while (tr != nullptr)
    {
        br++;
        if(tr -> info == key)
            return 1;
        if (tr -> info < key)
            tr = tr -> right;
        else
            tr = tr -> left;
    }
    return -1;
}

void evaluacijaStablo(int k, int a, int b, cvor *root)
{
    int br = 0, sum = 0, *niz = unos2(k, a, b);
    cout << "pretraga se vrsi na sledecim kljucevima:" << endl;
    for(int i = 0; i < k; i++)
        cout << niz[i] << " ";
    cout << endl;
    for(int i = 0; i < k; i++)
    {
        br = 0;
        pretraziStablo(niz[i], br, root);
        sum += br;
        cout << br << " ";
    }
    cout << endl << "prosecan broj koraka je: " << (float)sum / k;
}

//naci visinu
void ispisiStablo(int visina, cvor *root)
{
    int curr = 64, prev;
    queue <cvor *> queue;
    queue.push(root);

    for(int i = 0; i <= visina; i++ )
    {
        prev = curr;
        curr = (curr - 2) / 2;

        for(int k = 0; k < curr; k++ )
            cout << " ";

        for(int k = 0; k < pow(2, i); k++ )
        {
            cvor *tr = queue.front();
            queue.pop();

            queue.push(tr ? tr -> left : tr);
            queue.push(tr ? tr -> right : tr);

            if(tr)
                cout << tr -> info;
            else
                cout << "  ";

            for(int l = 0; l < prev; l++)
                cout << " ";
        }

        cout <<  endl << endl << endl;
    }
}

void ispisiInorder(cvor *root, int z)
{
    auto br1 = root;
    auto br2 = root;
    stack <cvor*> s1;
    stack <cvor*> s2;
    s1.push(br1);
    s2.push(br2);
    br1 = br1->left;
    br2 = br2->right;
    while(1)
    {
        if((br1== nullptr && s1.empty()) || (br2== nullptr && s2.empty()))
            break;

        while(br1)
        {
            s1.push(br1);
            br1 = br1->left;
        }
        while(br2)
        {
            s2.push(br2);
            br2 = br2->right;
        }

        br1 = s1.top();
        s1.pop();
        br2 = s2.top();
        s2.pop();
        if(br1->info + br2->info < z)
            br1 = br1->right;

        else if(br1->info + br2->info > z)
            br2 = br2->left;

        else
        {
            cout << br1 << " + " << br2 << endl;
            return;
        }
    }
}

void obrisiStablo(cvor *root)
{
    queue <cvor *> queue;
    queue.push(root);

    while(!queue.empty())
    {
        cvor *tr = queue.front();
        queue.pop();

        if(tr -> left != nullptr)
            queue.push(tr -> left);
        if(tr -> right != nullptr)
            queue.push(tr -> right);

        delete tr;
    }
}

void meni2()
{
    cout << "\nUnesite redni broj zeljene stavke:\n\t(1) Formiranje stabla na osnovu uredjenog niza"
            "\n\t(2) Umetanje novog kljuca u stablo\n\t(3) Pretraga stabla na zadati kljuc"
            "\n\t(4) Formatiran ispis stabla\n\t(5) Evaluacija pretrazivanja u BST\n\t"
            "(6) Brisanje stabla iz memorije\n\n\t(0) Kraj programa\n\n";
}

int main() {
    //int n = 0 // treba za stavku 5.
    int n = 10, a = 1, b = 100;
    int br = 0, izbor, kljuc, *K;
    cvor *root = nullptr;
    cout << "Dobrodosli! :)" << endl;
    while(true)
    {
        meni2();
        cin >> izbor;
        switch(izbor)
        {
            case 0:
                cout << "Prijatan dan! :)";
                return 0;

            case 1:
                root = nullptr;
                K = unos2(n, a, b);
                kreirajStablo(K, n, root);
                cout << "stablo je napravljeno!" << endl;
                break;

            case 2:
                cout << "unesite kljuc koji zelite da ubacite" << endl;
                cin >> kljuc;
                ubaciStablo(kljuc, root);
                cout << "kljuc je uspesno ubacen!" << endl;
                break;

            case 3:
                cout << "unesite kljuc koji pretrazujete" << endl;
                cin >> kljuc;
                a = pretraziStablo(kljuc, br, root);
                if(a != -1)
                    cout << "trazeni kljuc se nalazi u stablu" << endl;
                else
                    cout << "trazeni kljuc se ne nalazi u stablu" << endl;
                break;

            case 4:
                if(root)
                    //ispisiStablo(4, root);
                    ispisiInorder(root, 14);
                else
                    cout << "prvo napravite stablo!" << endl;
                break;

            case 5:
                if(root)
                    evaluacijaStablo(n, a, b, root);
                else
                    cout << "prvo napravite stablo!" << endl;
                break;

            case 6:
                if(root)
                    obrisiStablo(root);
                cout << "stablo je uspesno obrisano!" << endl;
                root = nullptr;
                break;

            case 8:
                cout << "hehe :)" << endl;
                break;

            default:
                cout << "izabrali ste nepostojecu opciju, pokusajte ponovo" << endl;
        }
    }
}