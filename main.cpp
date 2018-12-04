#include "quadratic_equation.cpp"

bool is_square( lint x ) {
    lint y =  (lint) sqrt( x );
    return y*y != x;
}

void print_equivalent_class( std::map< lint, lint > mp ) {
    std::map< lint, lint >::iterator itr = mp.begin();
    std::cout << std::setw( 6 ) << "class"  << "|\n"
              << std::setw( 6 ) << "number" << "|" << std::setw( 13 ) << "Discriminants\n"
              << std::setfill( '=' ) << std::setw( 20 ) << "" << std::setfill( ' ' ) << std::endl;
    while ( itr != mp.end() ) {
        std::cout << std::setw( 6 ) << itr->first  << "|"
                  << std::setw( 5 ) << itr->second << std::endl;
        ++itr;
    }
}

void solve( lint n ) {
    std::map< lint, lint > mp;
/*
    std::cout << std::setw( 5 ) << "D" << "|" << std::setw( 7 ) << "Caliber" << "|" 
              << std::setw( 12 ) << "class number\n"
              << "==========================" << std::endl;
*/
    for (lint idx=5; idx<n; ++idx) {
        if ( (idx%4 == 0 || idx%4 == 1) && is_square( (lint) idx ) ) {
            std::vector< cfracs > v;
            lint class_num;
            v = continued_fraction( idx );
            class_num = class_number( v );
/*
            std::cout << std::setw( 5 )  << idx      << "|"
                      << std::setw( 7 )  << v.size() << "|"
                      << std::setw( 12 ) << class_number( v )
                      << std::endl;
*/
            if ( mp.find( class_num ) != mp.end() ) {
                ++mp[ class_num ];
            } else {
                mp[ class_num ] = 1;
            }
        }
    }
    print_equivalent_class( mp );
}

int main() {
    lint n;
    std::cout << "Enter a positive integer : "; std::cin >> n;
    solve( n );
    return 0;
}
