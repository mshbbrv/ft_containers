#if 0 //CREATE A REAL STL EXAMPLE
#include <vector>
namespace ft = std;
#else
#include "vector.hpp"
#endif
#include "iostream"

int main(){

    std::cout << "--------ITER TEST---------\n";
    {
        ft::vector<int>::iterator iter;
        ft::vector<int>::const_iterator const_iter;
//должно работать
        const_iter = iter;
//не должно работать
        //iter = const_iter;
    }

    std::cout << "--------CONSTR TEST---------\n";
    {
        ft::vector<int> v;

        ft::vector<int> v1(5, 3);
        std::cout << "Output v1 of begin and end: ";
        for ( ft::vector<int>::iterator i = v1.begin(); i != v1.end(); ++i )
            std::cout << *i << " ";

        ft::vector<int> v2(v1.begin(), v1.end());
        std::cout << "\nOutput v2 of begin and end: ";
        for ( ft::vector<int>::iterator i = v2.begin(); i != v2.end(); ++i )
            std::cout << *i << " ";

        ft::vector<int> v3(v2);
        std::cout << "\nOutput v3 of begin and end: ";
        for ( ft::vector<int>::iterator i = v3.begin(); i != v3.end(); ++i )
            std::cout << *i << " ";

        ft::vector<int> v4 = v3;
        std::cout << "\nOutput v4 of begin and end: ";
        for ( ft::vector<int>::iterator i = v4.begin(); i != v4.end(); ++i )
            std::cout << *i << " ";

    }

    std::cout << "\n--------ITER TEST---------\n";
    {

        ft::vector<int> g1;

        for ( int i = 1; i <= 5; i++ )
            g1.push_back( i );

        std::cout << "Output of begin and end: ";
        for ( ft::vector<int>::iterator i = g1.begin(); i != g1.end(); ++i )
            std::cout << *i << " ";


        std::cout << "\nOutput of rbegin and rend: ";
        for ( ft::vector<int>::reverse_iterator ir = g1.rbegin(); ir != g1.rend();
        ++ir )
            std::cout << *ir << " ";

    }

    std::cout << "\n--------CAPACITY TEST---------";
    {
        ft::vector<int> g1;

        for ( int i = 1; i <= 5; i++ )
            g1.push_back( i );

        std::cout << "\nSize : " << g1.size();
        std::cout << "\nCapacity : " << g1.capacity();
        std::cout << "\nMax_Size : " << g1.max_size();

        g1.resize( 4 );
        std::cout << "\nSize : " << g1.size();

        if ( g1.empty() == false )
            std::cout << "\nVector is not empty";
        else
            std::cout << "\nVector is empty";
    }

    std::cout << "\n--------ELEMENT ACCESS TEST---------";
    {
        ft::vector<int> g1;

        for (int i = 1; i <= 10; i++)
            g1.push_back(i * 10);

        std::cout << "\nReference operator [g] : g1[2] = " << g1[2];

        std::cout << "\nat : g1.at(4) = " << g1.at(4);

        std::cout << "\nfront() : g1.front() = " << g1.front();

        std::cout << "\nback() : g1.back() = " << g1.back();

    }
    std::cout << "\n--------MODIFIERS TEST---------";
    {
        ft::vector<int> v;
        v.assign(5, 10);

        std::cout << "\nThe vector elements are: ";
        for (size_t i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        ft::vector<int> v2;
        v2.assign(v.begin(), v.end());

        std::cout << "\nThe v2 elements are: ";
        for (size_t i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        v.push_back(15);
        int n = v.size();
        std::cout << "\nThe last element is: " << v[n - 1];

        v.pop_back();

        std::cout << "\nThe vector elements are: ";
        for (size_t i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        v.insert(v.begin(), 5);
        std::cout << "\nThe first element is: " << v[0];

        v.erase(v.begin());

        std::cout << "\nThe first element is: " << v[0];

        v.insert(v.begin(), 2, 13);
        std::cout << "\nThe vector elements are: ";
        for (size_t i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        v.erase(v.begin(), v.begin() + 2);
        std::cout << "\nThe vector elements are: ";
        for (size_t i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        ft::vector<int> v3(3, 13);
        v.insert(v.begin() + 2, v3.begin(), v3.end());
        std::cout << "\nThe vector elements are: ";
        for (size_t i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        v.clear();
        std::cout << "\nVector size after erase(): " << v.size();

        ft::vector<int> v4, v5;
        v4.push_back(1);
        v4.push_back(2);
        v5.push_back(3);
        v5.push_back(4);

        std::cout << "\nVector 4: ";
        for (size_t i = 0; i < v4.size(); i++)
            std::cout << v4[i] << " ";

        std::cout << "\nVector 5: ";
        for (size_t i = 0; i < v5.size(); i++)
            std::cout << v5[i] << " ";

        // Swaps v1 and v2
        v4.swap(v5);

        std::cout << "\nAfter Swap \nVector 4: ";
        for (size_t i = 0; i < v4.size(); i++)
            std::cout << v4[i] << " ";

        std::cout << "\nVector 5: ";
        for (size_t i = 0; i < v5.size(); i++)
            std::cout << v5[i] << " ";

        std::cout << '\n';
    }

}
