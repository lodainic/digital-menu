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
    int ID;
    int stock;
    string name;
    float price;
};

bool mycomp(item &a, item &b);
vector<item> read_file();
void save_order(int total_cost, list<item> l);
void print_menu(vector<item> v);
float cost(stack<float> s);

int main()
{
    list<item> order_list;
    stack<float> price_stack;
    int id = -1;
    float total_cost;

    vector<item> menu = read_file();
    print_menu(menu);
    
    cont:while (id != 0)
    {
        cin >> id;
        if (menu[id - 1].stock > 0)
        {
            menu[id - 1].stock--;
            order_list.push_back(menu[id - 1]);
            price_stack.push(menu[id - 1].price);
        }
        else
        {
            cout << "Item#" << id << " is sold out" << endl;
            cout << "Anything else?" << endl;
        }
    }
    total_cost = cost(price_stack);
    order_list.sort(mycomp);
    system("clear"); // clear linux terminal
    //system("cls"); clear windows command prompt
    save_order(total_cost, order_list);
    order_list.clear();
    price_stack = stack<float>();
    this_thread::sleep_for(3s);
    system("clear");
    print_menu(menu);
    id = -1;
    goto cont;
    return 0;
}
bool mycomp(item &a, item &b)
{
    return a.ID < b.ID;
}
vector<item> read_file()
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
        itm.ID = stoi(temp[0]);
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
void save_order(int total_cost, list<item> l)
{
    list<item>::iterator itl;
    cout << "Get your printed order ticket!" << endl;
    cout << "*************************" << endl;
    for (itl = l.begin(); itl != l.end(); itl++)
    {
        cout << itl->name << endl;
    }
    cout << "Total: " << total_cost << " units " << endl;
    cout << endl;
    cout << "Enjoy !" << endl;
    cout << "*************************" << endl;
}
void print_menu(vector<item> v)
{
    vector<item>::iterator itv;
    cout << "************** MENU ***************" << endl;
    cout << "ID    Stock            Name " << endl;
    for (itv = v.begin(); itv != v.end(); itv++)
    {
        cout << itv->ID << "       " << itv->stock << "       " << itv->name << "   " << itv->price << " units" << endl;
    }
    cout << "Select by ID (0: end selection): " << endl;
}