#include <iostream>
#include "Greeter.h"
using namespace std;
namespace NameHello{
Greeter::Greeter(string name) { _name = name; }
string Greeter::ptintinfo() { return "Здравствуйте, " + _name + "!"; }
}