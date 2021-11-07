#include <bits/stdc++.h>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;

map<string, long long int> contacts;

void menu();

struct trie
{
    struct trie *ch[26];
    bool islast;
};

struct trie *getnode(void)
{
    struct trie *p = new trie;
    for (int i = 0; i < 26; i++)
        p->ch[i] = NULL;
    p->islast = false;
};

struct trie *root = getnode();

void insertt(string key)
{
    struct trie *temp = root;
    for (int i = 0; i < key.length(); i++)
    {
        int id = key[i] - 'a';
        if (temp->ch[id] == NULL)
            temp->ch[id] = getnode();
        temp = temp->ch[id];
    }
    temp->islast = true;
}

bool isEmpty()
{
    for (int i = 0; i < 26; i++)
        if (root->ch[i])
            return false;
    return true;
}

struct trie *remove(trie *del, string key, int depth = 0)
{
    if (!del)
        return NULL;

    if (depth == key.size())
    {

        if (del->islast)
            del->islast = false;

        if (isEmpty())
        {
            delete (del);
            del = NULL;
        }

        return del;
    }

    int index = key[depth] - 'a';
    del->ch[index] =
        remove(del->ch[index], key, depth + 1);

    if (isEmpty() && del->islast == false)
    {
        delete (del);
        del = NULL;
    }

    return del;
}

bool search(string str)
{
    struct trie *temp = root;
    for (int i = 0; i < str.length(); i++)
    {
        int id = str[i] - 'a';
        if (temp->ch[id] == NULL)
            return false;
        temp = temp->ch[id];
    }
    if (temp != NULL && temp->islast == true)
        return true;
}

void sug(struct trie *cur, string prefix)
{
    //	cout<<prefix<<"\n";
    if (cur->islast == true)
        cout << "\n\t\t\t\t\t\t\t\t" << prefix << "  " << contacts[prefix] << "\n";
    for (int i = 'a'; i <= 'z'; i++)
    {
        struct trie *next = cur->ch[i - 'a'];
        if (next != NULL)
            sug(next, prefix + (char)i);
    }
}

void displaycontacts(string str)
{
    string prefix = "";
    int i;
    struct trie *prev = root;

    for (i = 0; i < str.length(); i++)
    {
        prefix += str[i];
        int id = prefix[i] - 'a';
        struct trie *current = prev->ch[id];
        if (current == NULL)
        {
            i++;
            cout << "\n\t\t\t\t\t\t\t\tNot found";
            break;
        }
        if (i == str.length() - 1)
        {
            cout << "\n\t\t\t\t\t\t\t\tsuggestions of " << prefix << " are\n";
            sug(current, prefix);
        }
        prev = current;
        //	cout<<"\n";
    }

    for (; i < str.length(); i++)
    {
        prefix += (char)str[i];
        cout << "\n\t\t\t\t\t\t\t\tNo Results Found for " << prefix
             << "\n";
    }
}

int phlen(long long int ph)
{
    int ans = 0;

    while (ph > 0)
    {
        ph /= 10;
        ans++;
    }

    return ans;
}

bool firstNum(long long int ph)
{
    for (int i = 0; i < 9; i++)
    {
        ph /= 10;
    }

    if (ph == 0)
    {
        return false;
    }

    return true;
}

bool phonValidator(long long int ph)
{

    if (ph < 0 || phlen(ph) != 10 || firstNum(ph) == false)
    {
        return false;
    }

    for (auto mp : contacts)
    {
        if (mp.second == ph)
        {
            return false;
        }
    }

    return true;
}

bool nameValidator(string name)
{
    for (auto mp : contacts)
    {
        if (mp.first == name)
        {
            return false;
        }
    }

    return true;
}

void addContacts()
{
    while (1)
    {
        string name, choice;
        long long int phno;
    RETRY:
        cout << "\t\t\t\t\t\t\t\tEnter the contact's Name - ";
        cin >> name;

        if (nameValidator(name) == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tthis name already exists,please enter different name.";
            goto RETRY;
        }

    START:
        cout << "\n\t\t\t\t\t\t\t\tEnter the phone number of the contact - ";
        cin >> phno;

        if (phonValidator(phno) == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tTHIS IS AN INVALID PHONE NUMBER";
            goto START;
        }

        insertt(name);
        contacts[name] = phno;
        cout << "\n\t\t\t\t\t\t\t\tDo You Want To Add More Contacts(yes/no)\n";
        cin >> choice;
        if (choice == "no" || choice == "NO" || choice == "No" || choice == "nO")
            break;
    }
}

void removeContact()
{
    cout << "\n\t\t\t\t\t\t\t\tENTER NAME OF THE CONTACT YOU WANT TO DELETE: \n";
    string nm;
    cin >> nm;
    int f = 0;

    for (auto mp : contacts)
    {
        if (mp.first == nm)
        {
            cout << "\n\t\t\t\t\t\t\t\tCONTACT DELETED!!";
            remove(root, nm);
            contacts.erase(nm);
            return;
        }
    }

    if (f == 0)
    {
        cout << "\n\t\t\t\t\t\t\t\tCONTACT NOT FOUND!!";
    }
}

void displayAll()
{
    cout << "\n\t\t\t\t\t\t\t\t"
         << "NAME"
         << "      "
         << "NUMBER";
    for (auto mp : contacts)
    {
        cout << "\n\t\t\t\t\t\t\t\t" << mp.first << "   " << mp.second;
    }
    return;
}

void searchByname()
{

    string nm;
    cout << "\n\t\t\t\t\t\t\t\tENTER NAME OF CONTACT YOU WANT TO SEARCH: ";
    cin >> nm;

    int f = 0;
    for (auto mp : contacts)
    {
        if (mp.first == nm)
        {
            cout << "\n\t\t\t\t\t\t\t\tCONTACT FOUND!!";
            cout << "\n\t\t\t\t\t\t\t\t"
                 << "NAME"
                 << "      "
                 << "NUMBER";
            cout << "\n\t\t\t\t\t\t\t\t" << mp.first << "   " << mp.second;
            f = 1;
        }
    }
    if (f == 0)
    {
        cout << "\n\t\t\t\t\t\t\t\tCONTACT NOT FOUND!!";
    }
}

void searchByNumber()
{

    long long int ph;
START:
    cout << "\n\t\t\t\t\t\t\t\tENTER PHONE NUMBER OF CONTACT YOU WANT TO SEARCH: ";
    cin >> ph;

    if (phlen(ph) != 10 || ph < 0 || firstNum(ph) == 0)
    {
        cout << "\n\t\t\t\t\t\t\t\tENTER VALID PHONE NUMBER!";
        goto START;
    }

    int f = 0;
    for (auto mp : contacts)
    {
        if (mp.second == ph)
        {
            cout << "\n\t\t\t\t\t\t\t\tCONTACT FOUND!!";
            cout << "\n\t\t\t\t\t\t\t\t"
                 << "NAME"
                 << "      "
                 << "NUMBER";
            cout << "\n\t\t\t\t\t\t\t\t" << mp.first << "   " << mp.second;
            f = 1;
        }
    }

    if (f == 0)
    {
        cout << "\n\t\t\t\t\t\t\t\tCONTACT NOT FOUND!!";
    }
}

void searchPrefix()
{
    string search;
    cout << "\n\t\t\t\t\t\t\t\tName or Prefix of the contact's name you want to search - ";
    cin >> search;
    displaycontacts(search);
}

void menuUser()
{
    int ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|     DSA PROJECT CONTACT PREFIX SEARCH USING  TRIE   |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                [1]DISPLAY CONTACTS                  |\n";
        cout << "\t\t\t\t\t\t\t\t|                [2]SEARCH BY PREFIX                  |\n";
        cout << "\t\t\t\t\t\t\t\t|                [3]SEARCH BY NAME                    |\n";
        cout << "\t\t\t\t\t\t\t\t|                [4]SEARCH BY NUMBER                  |\n";
        cout << "\t\t\t\t\t\t\t\t|                [5]NUMBER OF RECORDS                 |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                   [6]EXIT                           |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            displayAll();
            break;
        case 2:
            searchPrefix();
            break;
        case 3:
            searchByname();
            break;
        case 4:
            searchByNumber();
            break;
        case 5:
            cout << "\n\t\t\t\t\t\t\t\tNUMBER CONTACTS CURRENTLY IN SYSTEM ARE:" << contacts.size();
            break;
        case 6:
            return;
        }
        getch();
    } while (ch != 6);
}

void administrator()
{
ADMIN:
    string username;
    string pass = "";
    char ch;
    cout << "\t\t\t\t\t\t\t\tEnter username\n\t\t\t\t\t\t\t\t";
    cin >> username;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\tEnter password\n\t\t\t\t\t\t\t\t";
    ch = _getch();
    while (ch != 13)
    { //character 13 is enter
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if ((pass == "qwerty" && username == "vaibhav") || (pass == "qwerty" && username == "vikas"))
    {
        loading();
        menu();
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\t\tAccess aborted...\n";
        cout << "\n\t\t\t\t\t\t\t\tdo you want to try again?(y/n)  ";
        char c;
        cin >> c;
        if (c == 'y' || c == 'Y')
        {
            goto ADMIN;
        }
        else
        {
            return;
        }
    }
}

void loading()
{
    // char x=219;
    char x = 254;
    cout << "\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\tPHONEBOOK MANAGEMENT SYSTEM\n ";
    cout << "\t\t\t\t\t\t\t\tLoading: ";
    for (int i = 0; i < 35; i++)
    {
        cout << x;
        Sleep(100);
        if (i > 10 && i <= 20)
            Sleep(50);
        if (i > 20)
            Sleep(25);
    }
    system("cls");
}

int main()
{
    int ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|     DSA PROJECT CONTACT PREFIX SEARCH USING  TRIE   |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                [1]User                              |\n";
        cout << "\t\t\t\t\t\t\t\t|                [2]Administrator Login               |\n";
        cout << "\t\t\t\t\t\t\t\t|                [3]Exit                              |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            loading();
            menuUser();
            break;
        case 2:
            administrator();
            break;
        }
        getch();
    } while (ch != 3);
}

void menu()
{
    int ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|     DSA PROJECT CONTACT PREFIX SEARCH USING  TRIE   |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                [1]ADD CONTACTS                      |\n";
        cout << "\t\t\t\t\t\t\t\t|                [2]DISPLAY ALL CONTACTS              |\n";
        cout << "\t\t\t\t\t\t\t\t|                [3]SEARCH PREFIX                     |\n";
        cout << "\t\t\t\t\t\t\t\t|                [4]SEARCH BY NAME                    |\n";
        cout << "\t\t\t\t\t\t\t\t|                [5]SEARCH BY NUMBER                  |\n";
        cout << "\t\t\t\t\t\t\t\t|                [6]DELETE CONTACT                    |\n";
        cout << "\t\t\t\t\t\t\t\t|                [7]NUMBER OF CONTACTS                |\n";
        cout << "\t\t\t\t\t\t\t\t|                [8]EXIT                              |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            addContacts();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchPrefix();
            break;
        case 4:
            searchByname();
            break;
        case 5:
            searchByNumber();
            break;
        case 6:
            removeContact();
            break;
        case 7:
            cout << "\n\t\t\t\t\t\t\t\tNUMBER CONTACTS CURRENTLY IN SYSTEM ARE:" << contacts.size();
            break;
        case 8:
            return;
        }
        getch();
    } while (ch != 8);
}