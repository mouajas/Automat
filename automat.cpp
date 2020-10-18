/*
* Title: project-01.cpp
* Abstract: This program is an automat where it will hold food
items and drinks. A user can add food items or drinks to an order, and then either purchase or cancel the whole order.
* Author: Jasmine Moua
* Email: jmoua@csumb.edu
* Estimate: 5 hours
* Date: 09/27/2020
*/

#include <iostream>
using namespace std;

class Food {
  public:
    Food(); // default constructor
    Food(string name, int calories, double price); // parameterized constructor

    string getName(); // return the value of myName
    int getCalories(); // return the value of myCalories
    double getPrice(); // return the value of myPrice

    void setName(string name); // set the value of myName
    void setCalories(int calories); // set the value of myCalories
    void setPrice(double price); // set the value of myPrice

    void display();  // print out information in pattern "name: x calories, $y"
  private:
    string myName;
    int myCalories;
    double myPrice;
};

class Drink {
  public:
    Drink(); // default constructor
    Drink(string name, int ounces, double price); // parameterized constructor
    
    string getName(); // return the value of myName
    int getOunces(); // return the value of myOunces
    double getPrice(); // return the value of myPrice

    void setName(string name); // set the value of myName
    void setOunces(int ounces); // set the value of myOunces
    void setPrice(double price); // set the value of myPrice

    void display();  // print out information in pattern "name: x ounces, $y"
  private:
    string myName;
    int myOunces;
    double myPrice;
};

const int AUTOMAT_MAX = 10; // if more than 9 items print "Automat food full; new food not added"

class Automat {
  public:
    Automat(); // default constructor
    
    bool emptyFood(); // return true if there are no Food items, false otherwise
    bool emptyDrink(); // return true if there are no Drink items, false otherwise
    
    void enqueue(Food f); // add a Food item to the back of the Food queue
    void enqueue(Drink d); // add a Drink item to the back of the Drink queue

    void dequeueFood(); // move myFoodFront forward to remove the frontmost Food
    void dequeueDrink(); // move myDrinkFront forward to remove the frontmost Drink

    Food frontFood(); // get the frontmost Food item
    Drink frontDrink(); // get the frontmost Drink item
    
    int foodCount(); // get the count of Food items currently in the Automat
    int drinkCount(); // get the count of Drink items currently in the Automat

    int getTotalCalories(); // return the sum of the calories of all Food items stored
    int getTotalOunces(); // return the sum of the ounces of all Food items stored
    double getTotalPrice(); // return the sum of the prices of all Food and Drink items

    void display(); // print out the full Automat state
  private:
    int myFoodFront;
    int myFoodBack;
    int myDrinkFront;
    int myDrinkBack;
    Food myFood[AUTOMAT_MAX]; // array of Food objects
    Drink myDrink[AUTOMAT_MAX]; // array of Drink objects
};

const int ORDER_MAX = 5; // this means that the Order can only contain at most 5 Food items and at most 5 Drink items at a time

class Order {
  public:
    Order(); // empty constructor
    
    bool emptyFood(); // return true if there are no Food items, false otherwise
    bool emptyDrink(); // return true if there are no Drink items, false otherwise

    void push(Food f); // add a Food item to the top of the Drink stack
    void push(Drink d); // add a Drink item to the top of the Food stack

    void popFood(); // move myFoodTop down to remove the topmost Food
    void popDrink(); // move myDrinkTop down to remove the topmost Drink

    Food topFood(); // get the topmost Food item
    Drink topDrink(); // get the topmost Drink item

    int foodCount(); // get the count of Food items currently in the Order
    int drinkCount(); // get the count of Drink items currently in the Order

    double getTotalPrice(); // return the sum of the prices of all Food and Drink items

    void display(); // print out the full Automat state
    void cancel(Automat &); // should pop each item from each stack, in order, and enqueue into the Automat - must be passed by reference

    void purchase(); // should reset each stack

    static int getTotalOrders(); // a static method to return myTotalOrders
  private:
    int myFoodTop;
    int myDrinkTop;
    Food myFood[ORDER_MAX];
    Drink myDrink[ORDER_MAX];
    static int myTotalOrders;
};

// default constructor for Food
Food::Food() {
  string myName = "DEFAULT";
  int myCalories = 0;
  double myPrice = 0.0;
}

// set private to public
Food::Food(string name, int calories, double price) {
  myName = name;
  myCalories = calories;
  myPrice = price;
}

// get name of food item
string Food::getName() {
  return myName;
}

// get number of calories of food item
int Food::getCalories() {
  return myCalories;
}

// get price of food item
double Food::getPrice() {
  return myPrice;
}

// set name of food item
void Food::setName(string name) {
  myName = name;
}

// set price of food item
void Food::setPrice(double price) {
  myPrice = price;
}

// set number of calories of food item
void Food::setCalories(int calories) {
  myCalories = calories;
}

// print out food name with calories and price
void Food::display() {
  cout << myName << ": " << myCalories << " calories, " << "$" << myPrice << endl; 
}

// default constructor for Drink
Drink::Drink() {
  string myName = "DEFAULT";
  int myOunces = 0;
  double myPrice = 0.0;
}

// set private to public
Drink::Drink(string name, int ounces, double price) {
  myName = name;
  myOunces = ounces;
  myPrice = price;
}

// get name of drink item
string Drink::getName() {
  return myName;
}

// get number of ounces of drink item
int Drink::getOunces() {
  return myOunces;
}

// get price of drink item
double Drink::getPrice() {
  return myPrice;
}

// set name of drink item
void Drink::setName(string name) {
  myName = name;
}

// set number of ounces of drink item
void Drink::setOunces(int ounces) {
  myOunces = ounces;
}

// set price of drink item
void Drink::setPrice(double price) {
  myPrice = price;
}

// print name of drink, ounces, and price
void Drink::display() {
  cout << myName << ": " << myOunces << " ounces, " << "$" << myPrice << endl;
}

// default Automat constructor
Automat::Automat() : myFoodFront(0),myFoodBack(0),myDrinkFront(0),myDrinkBack(0) {
}

// checks if food queue is empty
bool Automat::emptyFood() {
  return (myFoodFront == myFoodBack);
}

// checks if drink queue is empty
bool Automat::emptyDrink() {
  return (myDrinkFront == myDrinkBack);
}

// enqueues food
void Automat::enqueue(Food f) {
  int newBack = (myFoodBack + 1) % AUTOMAT_MAX;
  if (newBack != myFoodFront) { 
    myFood[myFoodBack] = f;
    myFoodBack = newBack;
  }
  // else {
  //   cerr << "*** Queue full -- can't add new value ***\n"
  //           "Must increase value of AUTOMAT_MAX.\n";
  // }
}

// enqueues drink
void Automat::enqueue(Drink d) {
  int newBack = (myDrinkBack + 1) % AUTOMAT_MAX;
  if (newBack != myDrinkFront) { 
    myDrink[myDrinkBack] = d;
    myDrinkBack = newBack;
  }
  // else {
  //   cerr << "*** Queue full -- can't add new value ***\n"
  //           "Must increase value of AUTOMAT_MAX.\n";
  // }
}

// dequeues food
void Automat::dequeueFood() {
  if (!emptyFood()) {
      myFoodFront = (myFoodFront + 1) % AUTOMAT_MAX;
  }
  // else  {
  //   cerr << "*** Queue is empty -- "
  //           "can't remove a value ***\n";
  // }
}

// dequeues drink
void Automat::dequeueDrink() {
  if (!emptyDrink()) {
    myDrinkFront = (myDrinkFront + 1) % AUTOMAT_MAX;
  }
  // else{
  //   cerr << "*** Queue is empty -- "
  //           "can't remove a value ***\n";
  // }
}

Food Automat::frontFood() {
  if (!emptyFood()) {
    return (myFood[myFoodFront]);
  }
  // else {
  //   cerr << "*** Queue is empty -- returning garbage value ***\n";
  //   Food bad;
  //   return bad;
  // }
};

Drink Automat::frontDrink() {
  if (!emptyFood()) {
    return (myDrink[myDrinkFront]);
  }
  // else {
  //   cerr << "*** Queue is empty -- returning garbage value ***\n";
  //   Drink bad;
  //   return bad;
  // }
};

int Automat::foodCount() {
  int count = 0;
  for (int i = myFoodFront; i != myFoodBack; i = (i + 1)%AUTOMAT_MAX) {
    count++;
  }
  return count;
}

int Automat::drinkCount() {
  int count = 0;
  for (int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX) {
    count++;
  }
  return count;
}

int Automat::getTotalCalories() {
  int sum = 0;
  for (int i = myFoodFront; i != myFoodBack; i = (i + 1)%AUTOMAT_MAX) {
    sum = sum + myFood[i].getCalories();
  }
  return sum;
}


int Automat::getTotalOunces() {
  int total = 0;
  for (int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX) {
    total = total + myDrink[i].getOunces();
  }
  return total;
}

double Automat::getTotalPrice() {
  double priceFood = 0.0;
  for (int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX) {
    priceFood = priceFood + myFood[i].getPrice();
  }

  double priceDrink = 0.0;
  for (int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX) {
    priceDrink = priceDrink + myDrink[i].getPrice();
  }

  double totalPrice = 0.0;
  totalPrice = priceFood + priceDrink;
  return totalPrice;
}

void Automat::display() {
  cout << "Automat: " << endl;

  cout << "\tFood: " << endl;

  for (int i = myFoodFront; i != myFoodBack; i = (i + 1)%AUTOMAT_MAX) {
    cout << "\t\t";
    myFood[i].display();
  }

  cout << "\t\t" << foodCount() << " food items - Total Calories: " << getTotalCalories() << endl;

  cout << "\tDrink: " << endl;

  for (int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX) {
    cout << "\t\t";
    myDrink[i].display();
  }

  cout << "\t\t" << drinkCount() << " drinks - Total Calories: " << getTotalOunces() << endl;

  // cout << "Total Price: $" << getTotalPrice() << endl;
}

Order::Order() : myFoodTop(-1),myDrinkTop(-1) {
  myTotalOrders++;
}

bool Order::emptyFood() { 
  return (myFoodTop == -1); 
}

bool Order::emptyDrink() {
  return (myDrinkTop == -1);
}

void Order::push(Food f) {
  if (myFoodTop < ORDER_MAX - 1) {
    ++myFoodTop;
    myFood[myFoodTop] = f;
  }
  // else {
  //   cerr << "*** Stack full -- can't add new value ***\n"
  //           "Must increase value of ORDER_MAX.\n";
  //   return;
  // }
}

void Order::push(Drink d) { 
  if (myDrinkTop < ORDER_MAX - 1) {
    ++myDrinkTop;
    myDrink[myDrinkTop] = d;
  }
  // else {
  //   cerr << "*** Stack full -- can't add new value ***\n"
  //           "Must increase value of ORDER_MAX.\n";
  //   return;
  // }
}

void Order::popFood() {
  if (!emptyFood()) {
    myFoodTop--;
  } 
  // else {
  //   cerr << "*** Stack is empty -- can't remove a value ***\n";
  // }
}

void Order::popDrink() {
  if (!emptyDrink()) {
    myDrinkTop--;
  } 
  // else {
  //   cerr << "*** Stack is empty -- can't remove a value ***\n";
  // }
}

Food Order::topFood() { 
  if (!emptyFood()) {
      return (myFood[myFoodTop]);
  }
  // else {
  //   cerr << "*** Stack is empty -- returning garbage value ***\n";
  //   Food bad;
  //   return bad;
  // }
}

Drink Order::topDrink() { 
  if (!emptyDrink()) {
      return (myDrink[myDrinkTop]);
  }
  // else {
  //   cerr << "*** Stack is empty -- returning garbage value ***\n";
  //   Drink bad;
  //   return bad;
  // }
}

int Order::foodCount() { 
  int count = 0; 
  for (int i = myFoodTop; i >= 0; i--) {
    count++;
  }
  return count;
}

int Order::drinkCount() { 
  int count = 0; 
  for (int i = myDrinkTop; i >= 0; i--) {
    count++;
  }
  return count;
}

double Order::getTotalPrice() { 
  double priceFood = 0.0;
  for (int i = myFoodTop; i >= 0; i--) {
    priceFood = priceFood + myFood[i].getPrice();
  }

  double priceDrink = 0.0;
  for (int i = myDrinkTop; i >= 0; i--) {
    priceDrink = priceDrink + myDrink[i].getPrice();
  }

  double totalPrice = 0.0;
  totalPrice = priceFood + priceDrink;
  return totalPrice;
}

void Order::display() { 
  cout << "Order: " << endl;

  cout << "\tFood (" << foodCount() << " items):" << endl;
  for (int i = myFoodTop; i >= 0; i--) {
    cout << "\t\t";
    myFood[i].display();
  }

  cout << "\tDrink (" << drinkCount() << " items):" << endl;
  for (int i = myDrinkTop; i >= 0; i--) {
    cout << "\t\t";
    myDrink[i].display();
  }

  cout << "\tOrder total: $" << getTotalPrice() << endl;
}

void Order::cancel(Automat & a) { 
  while(!(emptyFood())) {
    a.enqueue(myFood[myFoodTop]);
    popFood();
  }

  while(!(emptyDrink())) {
    a.enqueue(myDrink[myDrinkTop]);
    popDrink();
  }
}

void Order::purchase() { 
  myFoodTop = -1;
  myDrinkTop = -1; 
}

int Order::myTotalOrders = 0;

int Order::getTotalOrders() {
  return myTotalOrders;
}

int main() {
  Automat a;
  a.enqueue(Food("Let's Potato Chips", 300, 1.50));
  a.enqueue(Food("Mini Donuts", 500, 1));
  a.enqueue(Drink("Coffee", 6, 5.50));
  a.enqueue(Drink("Nacho Drink", 22, 2.50));
  cout << "Starting Automat\n";
  a.display();

  Order o;
  o.push(a.frontFood());
  a.dequeueFood();
  o.push(a.frontDrink());
  a.dequeueDrink();
  cout << endl;
  cout << "Ordered one food, one drink\n";
  o.display();
  cout << endl;
  a.display();

  cout << endl;
  cout << "Canceled order\n";
  o.cancel(a);
  o.display();
  cout << endl;
  a.display();

  cout << endl;
  cout << "Ordered one food, one drink, purchased\n";
  cout << endl;
  o.push(a.frontFood());
  a.dequeueFood();
  o.push(a.frontDrink());
  a.dequeueDrink();
  o.purchase();
  o.display();
  cout << endl;
  a.display();
}