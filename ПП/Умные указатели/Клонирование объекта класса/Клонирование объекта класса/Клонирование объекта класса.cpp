#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class tridiagonal_matrix
{
public:
    vector<double> m_down;
    vector<double> m_upper;
    vector<double> m_middle;

    tridiagonal_matrix(
        const vector<double>& down,
        const vector<double>& upper,
        const vector<double>& middle) :
        m_down{ down }, m_upper{ upper }, m_middle{ middle }
    {
    };

    ~tridiagonal_matrix() { 
        cout << "destructor called\n"; 
    }

    unique_ptr<tridiagonal_matrix> clone() const
    {
        return make_unique<tridiagonal_matrix>(m_down, m_upper, m_middle);
    }
};

int main()
{
    auto down = vector<double>{ -4.0, 5.0 };
    auto upper = vector<double>{ 14.0, 8.0 };
    auto middle = vector<double>{ 3.0, 1.0, 7.0 };

    auto matrix = make_unique<tridiagonal_matrix>(down, upper, middle);
    auto matrix_clone = matrix->clone();

    return 0;
}