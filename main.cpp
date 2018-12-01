#include "quadratic_equation.cpp"

bool is_square( lint x ) {
    lint y =  (lint) sqrt( x );
    return y*y != x;
}

void solve( lint n ) {
    std::cout << std::setw( 5 ) << "D" << "|" << std::setw( 7 ) << "Caliber" << "|" 
              << std::setw( 12 ) << "class number\n"
              << "==========================" << std::endl;
    for (lint idx=5; idx<n; ++idx) {
        if ( (idx%4 == 0 || idx%4 == 1) && is_square( (lint) idx ) ) {
            std::vector< cfracs > v;
            v = continued_fraction( idx );
            std::cout << std::setw( 5 )  << idx      << "|"
                      << std::setw( 7 )  << v.size() << "|"
                      << std::setw( 12 ) << class_number( v )
                      << std::endl;
        }
    }
}

int main() {
    lint n;
    std::cout << "Enter a positive integer : "; std::cin >> n;
    solve( n );
    return 0;
}