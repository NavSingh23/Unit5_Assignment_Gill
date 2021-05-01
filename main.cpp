//A  Restaurant Project Struct style Dr_T Dr. Tyson McMillan 10-2-2019

#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
#include <fstream>
#include "Input_Validation_Extended.h"
using namespace std; 

class MenuItem
{
  private:
  string name;
  double itemCost; 
  string desc; 
  char addLetter; 
  char removeLetter;
  int count; 

  public:
  MenuItem()
  {
    name = "";
    itemCost = 0.0;
    desc = "";
    addLetter = 'p';
    removeLetter = 'p';
    count = 0;
  }
  void setName(string n) { name = n;}
  void setItemCost(double ic) {itemCost = ic;}
  void setDesc(string d) { desc = d;}
  void setAddLetter(char al) {addLetter = al;}
  void setRemoveLetter(char rl) {removeLetter = rl;}
  void setCount(int c) {count = c;}
  string getName() const { return name;}
  double getItemCost() const {return itemCost;}
  string getDesc() const {return desc;}
  char getAddLetter() const {return addLetter;}
  char getRemoveLetter() const {return removeLetter;}
  int getCount() const {return count;}

};

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Churro", "Pizza", "Nachos", "Hot Dog", "Hamburger"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].setName(defaultMenuNames[i]); 
    entireMenu[i].setAddLetter(defaultAddLetters[i]); 
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(3.00 + i); //set a random starter cost for each item
    entireMenu[i].setCount(0); //initialze all counts to 0
    entireMenu[i].setDesc("delicious"); //set all default desc to "delicous"
  }


}

void showMenu(vector<MenuItem> &m)
{
  
  string reset = "\x1b[0m";
  string Titlecolor = "\x1b[" + to_string(32) + ";1m";
  string Headercolor = "\x1b[" + to_string(33) + ";1m";
  string Menucolor = "\x1b[" + to_string(31) + ";1m";


  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << Titlecolor << "DrT's Effcient Menu" << reset << endl; 
  cout << Headercolor <<"ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<< reset <<endl; 

  for(int i = 0; i < m.size(); i++)
  {
    cout << Menucolor<< m[i].getAddLetter() << ")" << setw(10) << m[i].getName() 
    << setw(5) << "$" << m[i].getItemCost() << setw(5) << "(" << m[i].getRemoveLetter()
    << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() << reset <<endl; 
  }

}

double acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0; 
  double tip = 0.0;
  string reset = "\x1b[0m";
  string Outputcolor = "\x1b[" + to_string(35) + ";1m";

  do
  {
    cout << Outputcolor << "\nPlease choose an item (x to Exit): "<< reset;
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].setCount(m[i].getCount() + 1); //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subtotal += m[i].getItemCost(); //increment the subtotal by the cost of the item 
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) //subtract if and only if the count is > 0
        {
          m[i].setCount(m[i].getCount() - 1); //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subtotal -= m[i].getItemCost(); //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X' 
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X'); 

    double total = 0.0;
  cout << "How much would you like to tip? Recommended 20% ($" << subtotal*.2<< ")" << endl;
  tip = validateDouble(tip);
  total = tip + (subtotal* 1.0825);

  cout << "Pretax: $" << subtotal << endl;
  cout << "Tip: $" << tip << endl;
  cout << "Tax: $" << (subtotal* 1.0825 - subtotal) << endl;
  cout << "Total: $" << total << endl;
  return total;
  //cout << "\nThank you for placing your order." << endl;
  //handle the tip process here
  //handle reciept generation here
}

void printReciept(vector<MenuItem> &m, double subtotal)
{
  cout << fixed << setprecision(2);
  ofstream myfile;
  myfile.open ("C:\\Reciept.html");
  //myfile.open ("reciept.txt");
  cout<< "\n\nDr. T's Restaurant Reciept" << endl;
  myfile << "Dr. T's Restaurant Reciept\n" << endl;

for (int i = 0; i <m.size(); i++)
{
  if(m[i].getCount() != 0)
  {
    cout << endl << "Item: " << m[i].getName() <<" Quantity: " << m[i].getCount() << " Cost: " << m[i].getCount() * m[i].getItemCost() << endl;
    myfile << "Item: " << m[i].getName() <<" Quantity: " << m[i].getCount() << " Cost: " << m[i].getCount() * m[i].getItemCost() << endl;
  }
}

cout << "\nTotal: $" << subtotal << endl;
myfile <<"\nTotal: $" << subtotal << endl;
  
  myfile.close();
}


char paymenttype(double total)
{
  char option = 'z';
  do
  {
  cout << "\nWill you be using" << endl<<  "A: Card" << endl << "B: Cash" << endl;
  option = validateChar(option);
  if (option == 'A' || option == 'a')
  {
    cout << "Card" << endl;
  
  }
  else if(option == 'B' || option == 'b')
  {
    cout << "Cash" << endl;
    cout <<"Cash Amount given by Customer: " << endl;
    double cashAmount = validateDouble(cashAmount);
    if (cashAmount > total)
    {
      double change = cashAmount - total;
      cout << "Your change is: $" << change << endl;
    }
  }
  else
  {
    cout << "Invalid Option" << endl;
  }
  }while(option != 'A' && option !='B' && option != 'a' && option !='b');

  return option;
}





int main() 
{
  char option = 'z';

  do
  {
  vector<MenuItem> wholeMenu; 
  populateMenu(wholeMenu); //put some default values in the menu
  showMenu(wholeMenu); //print the current data of the menu on screen 
  double total = acceptOrder(wholeMenu); 
  char paytype = paymenttype(total);
  printReciept(wholeMenu, total);
  cout << "\n\nIf you would like to Logout of system please press L or press any char for new customer: " << endl;
  option = validateChar(option);
  } while(option != 'L' && option != 'l');


  return 0; 
}