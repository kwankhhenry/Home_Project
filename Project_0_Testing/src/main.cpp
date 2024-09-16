#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

void printer(int i)
{
  cout << i << ", ";
}

template<class T>
void f(T& a)
{
  cout << 1 + a << endl;
}

void f(double &a)
{
  cout << 2 + a << endl;
}

int main()
{
  /*vector<int> v1;
  int i;
  do{
    cin >> i;
    v1.push_back(i);
  }while( i !=9 && !cin.bad());
  for_each(v1.begin(), v1.end(), printer);
  */
  double a = 1.5;
  f(a);
  return 0;

  /*
  ifstream inputfile("input.txt");
  vector<char> v1;
  char c;

  do
  {
    inputfile >> c;
    v1.push_back(c);
  } while (inputfile.good());
  inputfile.close();
  for_each(v1.begin(), v1.end(), printer);*/

  /*string s;
  getline(cin, s);
  stringstream input(s);
  vector<int> v1;
  int i;
  do
  {
    input >> hex >> i;
    v1.push_back(i);
  } while (!input.fail());
  
  for_each(v1.begin(), v1.end(), printer);
  return 0;*/

  /*int mynumbers[] = {3, 9, 0, 2, 1, 4, 5};
  vector<int> v1(mynumbers, mynumbers+7);
  fstream outfile("output.txt", ios::trunc | ios::out);
  int i;

  while(outfile.good())
  {
    outfile >> i;
    v1.push_back(i);
  }
  outfile.close();
  for_each(v1.begin(), v1.end(), printer);
  outfile.close();
  outfile.open("output.txt");*/
}