#include "./fraction.cpp"


typedef struct _coef{
    lint A;
    lint B;
    lint C;
} coef;

std::vector< lint > get_Bs( const lint D );
std::vector< coef > get_coefficients( lint D );
bool is_relatively_prime(const lint A, const lint B, const lint C);
bool is_equivalent_class( cfracs a, cfracs b );
lint class_number( std::vector< cfracs > v );
Fraction quad_eq( coef x, lint D );

std::vector< lint > get_Bs( const lint D ) {
    std::vector< lint > Bs;
    lint sq_D = sqrt( D );
    sq_D = -sq_D;
    lint Dmd2 = D % 2;
    lint cnt  = sq_D;

    while ( cnt < 0 ) {
        lint tmp = abs(cnt);
        if ( Dmd2 == tmp%2 ) {
            Bs.push_back( cnt );
        }
        ++cnt;
    }
/*
    std::vector< lint >::iterator itr = Bs.begin();
    while (itr != Bs.end()) {
        std::cout << *itr << " ";
        ++itr;
    }    
    std::cout << std::endl;
*/
    return Bs;
}

bool is_relatively_prime(const lint A, const lint B, const lint C) {
    lint m;
    lint a = A, b = -B, c = -C;
    m = gcd( a, b );
    m = gcd( m, c );

    return m == 1;
}

std::vector< coef > get_coefficients( lint D ) {
    std::vector< coef > v;
    std::vector< lint > Bs;
    
    while ( !v.empty() ) { v.pop_back(); }
    Bs = get_Bs( D );
    std::vector< lint >::iterator itr = Bs.begin();
    // std::cout << "Debug, size of Bs : " << Bs.size() << std::endl;
    while ( itr != Bs.end() ) {
        lint B  = *itr;
        lint AC = ( B*B - D ) / 4;
        lint lb, ub;
        Fraction lhs, rhs;
        lhs = Fraction( Irr(  B, P( 1, D ) ), Irr( 2, P( 0, 0 ) ) );
        rhs = Fraction( Irr( -B, P( 1, D ) ), Irr( 2, P( 0, 0 ) ) );
        
        if ( lhs.to_real() > (lint) lhs.to_real() ) {
            lb = lhs.to_real() + 1;
        } else {
            lb = lhs.to_real();
        }
        lb = ( lb < 1 ) ? 1 : lb;
        ub = rhs.to_real();
        // std::cout << "Debug: lb = " << lb << ", ub = " << ub << std::endl;
        int counter=0;
        for (lint cnt=lb; cnt<=ub; ++cnt) {
            lint abs_AC = abs( AC );
            lint A, C;
            if (abs_AC%cnt == 0) {
                A = cnt;
                C = AC/cnt;
                if ( is_relatively_prime(A, B, C) ) {
                    coef x;
                    x.A = A; x.B = B; x.C = C;
                    v.push_back( x );
                }
            }
        }
        ++itr;
    }
    return v;
}

bool is_equivalent_class( cfracs a, cfracs b ) {
    if ( a.size() != b.size() ) return false;
    size_t n   = b.size();
    size_t itr = 0;
    bool   flag = false;
    while ( itr < n ) {
        if ( a == b ) {
            flag = true;
            break;
        }
        b.push_back( b.front() );
        b.erase( b.begin() );
        ++itr;

    }
    return flag;
}

Fraction quad_eq( coef x, lint D ) {
    lint A = x.A;
    lint B = x.B;
    lint C = x.C;
    Irr numer = Irr(  -B, P( 1, D ) );
    Irr denom = Irr( 2*A, P( 0, 0 ) );
    Fraction f = Fraction( numer, denom );
    f.reduce();

    return f;
}

std::vector< cfracs > continued_fraction( lint D ) {
    std::vector< coef > v = get_coefficients( D );
    std::vector< coef >::iterator itr = v.begin();
    std::vector< cfracs > res;
    while ( itr != v.end() ) {
        Fraction f = quad_eq( *itr, D );
        f.continued_fraction();
        res.push_back( f.get_cfracs() );
        // f.result();
        ++itr;
    }
/*
    std::cout << "size of res : " << res.size() << std::endl;
    std::cout << "Debug: class number is " << class_number( res ) << std::endl;
*/
    return res;
}

lint class_number( std::vector< cfracs > v ) {
    std::vector< cfracs > w;
    std::vector< cfracs >::iterator vitr = v.begin();
    while ( !w.empty() ) { w.pop_back(); }
    // w.push_back( *vitr );
    // ++vitr;

    while ( vitr != v.end() ) {
        bool flag = true;
        std::vector< cfracs >::iterator witr = w.begin();
        while ( witr != w.end() ) {
            if ( is_equivalent_class( *vitr, *witr ) ) {
                flag = false;
            }
            ++witr;
        }
        if ( flag ) {
                w.push_back( *vitr );
        }
        ++vitr;
    }
    return w.size();
}

