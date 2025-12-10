#ifndef GREETER_H
#define GREETER_H

#include <string>
using namespace std;
namespace NameHello {
    class Greeter {
    private:
        string _name;
    public:
        Greeter(string name);
        string ptintinfo();
    };
}
#endif 