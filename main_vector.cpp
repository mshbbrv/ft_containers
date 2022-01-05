#include "vector.hpp"
#include "iostream"
#include <vector>

int main(){

    std::cout << "--------TEST 0---------\n";
    {
        ft::vector<int>::iterator iter;
        ft::vector<int>::const_iterator const_iter;
//должно работать
        const_iter = iter;
//не должно работать
        //iter = const_iter;
    }

    std::cout << "--------TEST 1---------\n";

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
    std::cout << "\n--------TEST 2---------";
    {
        ft::vector<int> g1;

        for ( int i = 1; i <= 5; i++ )
            g1.push_back( i );

        std::cout << "\nSize : " << g1.size();
        std::cout << "\nCapacity : " << g1.capacity();
        std::cout << "\nMax_Size : " << g1.max_size();

        // resizes the vector size to 4
        g1.resize( 4 );

        // prints the vector size after resize()
        std::cout << "\nSize : " << g1.size();

        // checks if the vector is empty or not
        if ( g1.empty() == false )
            std::cout << "\nVector is not empty";
        else
            std::cout << "\nVector is empty";
    }

    std::cout << "\n--------TEST 3---------";
    {
        ft::vector<int> g1;

        for (int i = 1; i <= 10; i++)
            g1.push_back(i * 10);

        std::cout << "\nReference operator [g] : g1[2] = " << g1[2];

        std::cout << "\nat : g1.at(4) = " << g1.at(4);

        std::cout << "\nfront() : g1.front() = " << g1.front();

        std::cout << "\nback() : g1.back() = " << g1.back();

    }
    std::cout << "\n--------TEST 4---------";
    {
        // Assign vector
        ft::vector<int> v;

        // fill the array with 10 five times
        v.assign(5, 10);

        std::cout << "\nThe vector elements are: ";
        for (int i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        // inserts 15 to the last position
        v.push_back(15);
        int n = v.size();
        std::cout << "\nThe last element is: " << v[n - 1];

        // removes last element
        v.pop_back();

        // prints the vector
        std::cout << "\nThe vector elements are: ";
        for (int i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        // inserts 5 at the beginning
        v.insert(v.begin(), 5);

        std::cout << "\nThe first element is: " << v[0];

        // removes the first element
        v.erase(v.begin());

        std::cout << "\nThe first element is: " << v[0];

        // erases the vector
        v.clear();
        std::cout << "\nVector size after erase(): " << v.size();

        // two vector to perform swap
        ft::vector<int> v1, v2;
        v1.push_back(1);
        v1.push_back(2);
        v2.push_back(3);
        v2.push_back(4);

        std::cout << "\nVector 1: ";
        for (int i = 0; i < v1.size(); i++)
            std::cout << v1[i] << " ";

        std::cout << "\nVector 2: ";
        for (int i = 0; i < v2.size(); i++)
            std::cout << v2[i] << " ";

        // Swaps v1 and v2
        v1.swap(v2);

        std::cout << "\nAfter Swap \nVector 1: ";
        for (int i = 0; i < v1.size(); i++)
            std::cout << v1[i] << " ";

        std::cout << "\nVector 2: ";
        for (int i = 0; i < v2.size(); i++)
            std::cout << v2[i] << " ";

        std::cout << '\n';
    }

}
