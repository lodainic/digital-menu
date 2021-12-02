#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <thread>

using namespace std;

struct item
{
    int id;
    int stock;
    string name;
    float price;
};

bool myComp(item &a, item &b);
vector<item> readFile();
void saveOrder(int totalCost, list<item> l);
void printMenu(vector<item> v);
float cost(stack<float> s);

int main()
{
    list<item> orderList;
    stack<float> priceStack;
    int id = -1;
    float totalCost;

    vector<item> menu = readFile();
    printMenu(menu);
    
    cont:while (id != 0)
    {
        cin >> id;
        if (menu[id - 1].stock > 0)
        {
            menu[id - 1].stock--;
            orderList.push_back(menu[id - 1]);
            priceStack.push(menu[id - 1].price);
        }
        else
        {
            cout << "Item#" << id << " is sold out" << endl;
            cout << "Anything else?" << endl;
        }
    }
    totalCost = cost(priceStack);
    orderList.sort(myComp);
    system("clear"); // clear linux terminal
    //system("cls"); clear windows command prompt
    saveOrder(totalCost, orderList);
    orderList.clear();
    priceStack = stack<float>();
    this_thread::sleep_for(3s);
    system("clear");
    printMenu(menu);
    id = -1;
    goto cont;
    return 0;
}
bool myComp(item &a, item &b)
{
    return a.id < b.id;
}
vector<item> readFile()
{
    item itm;
    vector<item> itms;
    string x;
    ifstream inFile;

    inFile.open("menu.txt");
    if (!inFile)
    {
        cerr << "Unable to open menu.txt file";
        exit(1); // call system to stop
    }
    while (inFile >> x)
    {
        stringstream ss(x);
        vector<string> temp;
        while (ss.good())
        {
            string substr;
            getline(ss, substr, ',');
            temp.push_back(substr);
        }
        itm.id = stoi(temp[0]);
        itm.stock = stoi(temp[1]);
        itm.name = temp[2];
        itm.price = stof(temp[3]);
        itms.push_back(itm);
    }
    inFile.close();

    return itms;
}
float cost(stack<float> s)
{
    float c = 0;
    while (!s.empty())
    {
        c += s.top();
        s.pop();
    }
    return c;
}
void saveOrder(int totalCost, list<item> l)
{
    list<item>::iterator itl;
    cout << "Get your printed order ticket!" << endl;
    cout << "*************************" << endl;
    for (itl = l.begin(); itl != l.end(); itl++)
    {
        cout << itl->name << endl;
    }
    cout << "Total: " << totalCost << " units " << endl;
    cout << endl;
    cout << "Enjoy !" << endl;
    cout << "*************************" << endl;
}
void printMenu(vector<item> v)
{
    vector<item>::iterator itv;
    cout << "************** MENU ***************" << endl;
    cout << "id    Stock            Name " << endl;
    for (itv = v.begin(); itv != v.end(); itv++)
    {
        cout << itv->id << "       " << itv->stock << "       " << itv->name << "   " << itv->price << " units" << endl;
    }
    cout << "Select by id (0: end selection): " << endl;
}