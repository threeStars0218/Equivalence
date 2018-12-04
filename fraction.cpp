#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>

typedef long int                   lint;
typedef long double                ldouble;
typedef std::pair< lint, lint >    P;
typedef std::vector< lint >        cfracs;

lint gcd( lint a, lint b ) {
    if ( b == 0 ) return a;
    a %= b;
    
    return gcd( b, a );
}

// *****************************************************************************************************
// class Irr
// *****************************************************************************************************
/*
 * Docstring for "class Irr"
 * class Irr keeps irrational number:
 *
 *     a + b * sqrt( c )
 *
 * parameters:
 * ----------
 *     - a  : long int part
 *     - sq : std::pair< lint, lint >,
 *            sq.first  = coefficient of equare root
 *            sq.second = inside square root
 *            i.e.
 *                sq.first * sqrt( sq.second )
 *
 */


class Irr {
    private:
        lint  a;
        P    sq;
    public:
        Irr();
        Irr( lint a, P sq );
        ~Irr();

        Irr operator+ (  Irr &x );
        Irr operator- (  Irr &x );
        Irr operator* (  Irr &x );

        // bool operator~ (  Irr &x );
        bool operator==(  Irr &x );
        bool operator!=(  Irr &x );
        bool operator< (  Irr &x );
        bool operator> (  Irr &x );
        
        Irr  conjugate();
        bool is_conjugate(  Irr &x );
        bool is_lint();
        
        ldouble to_real();

        lint get_a();
        P    get_sq();

        void set_a( lint x );
        void set_sq( lint a, lint b );

        void print();
};

Irr::Irr() {
    a  = 0;
    sq = P( 0, 0 );
}

Irr::Irr( lint x, P v ) {
    a  = x;
    sq = v;
}

Irr::~Irr() {  }

Irr Irr::operator+(  Irr &x ) {
    if ( this->is_lint() && x.is_lint() ) {
        return Irr( this->a + x.a, P( 0, 0 ) );
    } else if ( this->is_lint() ) {
        return Irr( this->a + x.a, x.sq );
    } else if ( x.is_lint() ) {
        return Irr( this->a + x.a, this->sq );
    }else if ( *this != x ) {
        std::cout << " Error: this->sq != x.sq " << std::endl;
        return *this;
    }

    lint  a;
    P    sq;
    a = this->a + x.a;
    sq.first  = this->sq.first + x.sq.first;
    sq.second = this->sq.second;

    return Irr( a, sq );
}

Irr Irr::operator-(  Irr &x ) {

    if ( this->is_lint() && x.is_lint() ) {
        return Irr( this->a - x.a, P( 0, 0 ) );
    } else if ( this->is_lint() ) {
        return Irr( this->a - x.a, x.sq );
    } else if ( x.is_lint() ) {
        return Irr( this->a - x.a, this->sq );
    }else if ( *this != x ) {
        std::cout << " Error: this->sq != x.sq " << std::endl;
        return *this;
    }

    lint  a;
    P    sq;
    a = this->a - x.a;
    sq.first  = this->sq.first - x.sq.first;
    sq.second = this->sq.second;

    return Irr( a, sq );
}

Irr Irr::operator*(  Irr &x ) {
    lint  a;
    P    sq;
    if ( this->is_lint() && x.is_lint() ) {
        return Irr( this->a * x.a, P( 0, 0 ) );
    } else if ( this->is_lint() ) {
        a = this->a * x.a;
        sq.first  = this->a * x.sq.first;
        sq.second = x.sq.second;
        return Irr( a, sq );
    } else if ( x.is_lint() ) {
        a = this->a * x.a;
        sq.first  = this->sq.first * x.a;
        sq.second = this->sq.second;
        return Irr( a, sq );
    } else if ( this->is_conjugate( x ) ) {
        a = this->a * x.a + this->sq.first * this->sq.second * x.sq.first;
        sq = P( 0, 0 );
        return Irr( a, sq );
    } else {
        std::cout << "Error: something wrong, Inside operator*" << std::endl;
        a = this->a * x.a - ( this->sq.first * x.sq.first * this->sq.first );

        return Irr( a, sq );
    }
}

bool Irr::operator==(  Irr &x ) {
    if ( this->a == x.a && this->sq == x.sq ) return true;
    return false;
}

bool Irr::operator!=(  Irr &x ) {
    return !( *this == x );
}

bool Irr::operator< (  Irr &x ) {
    return this->to_real() < x.to_real();
}
bool Irr::operator> (  Irr &x ) {
    return this->to_real() > x.to_real();
}


Irr Irr::conjugate() {
    lint  a;
    P    sq;
    a  = this->a;
    sq = this->sq;
    sq.first = -sq.first;

    return Irr( a, sq );
}

bool Irr::is_conjugate(  Irr &x ) {
    return this->conjugate() == x;
}

bool Irr::is_lint() {
    return this->sq.second == 0;
}

ldouble Irr::to_real() {
    ldouble res;
    res = (ldouble) this->a + this->sq.first * sqrt( this->sq.second );
    return res;
}

lint Irr::get_a()  { return  a; }
P    Irr::get_sq() { return sq; }

void Irr::set_a( lint x ) {
    this->a = x;
}

void Irr::set_sq( lint b, lint c ) {
    this->sq.first  = b;
    this->sq.second = c;
}

void Irr::print() {
    std::string op = ( this->sq.first >= 0 ) ? " + " : " - ";
    std::cout << std::setw( 5 ) << a         << op
              << std::setw( 5 ) << abs( sq.first )  << " * sqrt( "
              << std::setw( 5 ) << sq.second << " )"
              << std::endl;
}

Irr zero  = Irr(  0, P( 0, 0 ) );
Irr minus = Irr( -1, P( 0, 0 ) );
// *****************************************************************************************************
// class Fraction
// *****************************************************************************************************

class Fraction {
    private:
        Irr    numer; // numerator
        Irr    denom; // denominator
        cfracs    cf; // vector of continued fraction e.g. [2, 1, 2, 1, 1, 4, 1, .. ]
    public:
        Fraction();
        Fraction( Irr n, Irr d );
        ~Fraction();

        Fraction operator+ (  Fraction &x );
        Fraction operator- (  Fraction &x );
        bool     operator==(  Fraction &x );
        bool     operator!=(  Fraction &x );
        bool     operator< (  Fraction &x );
        bool     operator> (  Fraction &x );

        Fraction rationarize();
        Fraction reduce();
        Fraction decimal_part();
        lint     lint_part();
        ldouble  to_real();
        cfracs   get_cfracs();
        void     inverse();
        void     continued_fraction();
        void     print();  // print fraction
        void     result(); // print cf
};

Fraction::Fraction() {
    numer = zero;
    denom = zero;
    while ( !cf.empty() ){ cf.pop_back(); }
}

Fraction::Fraction( Irr n, Irr d ) {
    if ( d < zero ) {
        n = minus * n;
        d = minus * d;
    }
    numer = n;
    denom = d;
    while ( !cf.empty() ){ cf.pop_back(); }
}

Fraction::~Fraction() {  }

Fraction Fraction::operator+(  Fraction &x ) {

    Irr num = this->numer + x.numer;
    Irr den = this->denom + x.denom;

    return Fraction( num, den );
}

Fraction Fraction::operator-(  Fraction &x ) {

    Irr num = this->numer - x.numer;
    Irr den = this->denom - x.denom;

    return Fraction( num, den );

}

bool Fraction::operator==(  Fraction &x ) {
    return ( this->numer == x.numer ) && ( this->denom == x.denom );
}

bool Fraction::operator!=(  Fraction &x ) {
    return !( *this == x );
}

bool Fraction::operator< (  Fraction &x ) {
    return this->to_real() < x.to_real();
} 
bool Fraction::operator> (  Fraction &x ) {
    return this->to_real() > x.to_real();
}

Fraction Fraction::rationarize() {
    if ( this->denom.is_lint() ) {
        std::cout << "This fraction is already rationarized." << std::endl;
        return *this;
    }
    Irr num = this->denom.conjugate() * this->numer;
    Irr den = this->denom.conjugate() * this->denom;

    return Fraction( num, den ).reduce();
}

Fraction Fraction::reduce() {
    lint m, n;
    m = gcd( this->numer.get_a(), this->numer.get_sq().first );
    n = gcd( this->denom.get_a(), this->denom.get_sq().first );
    m = gcd( m, n );

    if ( m != 1 ) {
        Fraction f = *this;
        f.numer.set_a( f.numer.get_a() / m );
        f.denom.set_a( f.denom.get_a() / m );
        f.numer.set_sq( f.numer.get_sq().first / m, f.numer.get_sq().second );
        f.denom.set_sq( f.denom.get_sq().first / m, f.denom.get_sq().second );

        if ( f.denom < zero ) {
            f.numer = minus * f.numer;
            f.denom = minus * f.denom;
        }

        return f;
    }
    return *this;
}

cfracs Fraction::get_cfracs() {
    return this->cf;
}

ldouble Fraction::to_real() {
    ldouble n, d;
    n = this->numer.to_real();
    d = this->denom.to_real();

    return n/d;
}

lint Fraction::lint_part() {
    lint res;
    res = (lint) this->to_real();
    return res;
}

Fraction Fraction::decimal_part() {
    lint x = this->lint_part();
    x = x * this->denom.get_a();
    this->numer.set_a( this->numer.get_a() - x );
    this->reduce();
    return *this;
}

void Fraction::inverse() {
    std::swap( this->numer, this->denom );
}

void Fraction::continued_fraction() {
    Fraction f  = *this;
    std::vector< Fraction > fvec;
    bool flag = true;

    while ( !(this->cf.empty()) ) { this->cf.pop_back(); }

    if ( f.lint_part() < 1 ) {
        f.inverse();
        f.rationarize();
    }
    fvec.push_back( f );

    while ( flag ) {
        this->cf.push_back( f.lint_part() );
        f = f.decimal_part();
        f.inverse();
        f = f.rationarize();
        // f.print();
        // this->result();
        std::vector< Fraction >::iterator itr=fvec.begin();
        
        while ( itr !=fvec.end() && *itr != f ) { ++itr; }
        if ( itr != fvec.end() ) {
            flag = false;
        } else {
            fvec.push_back( f );
        }
        
    }
}

void Fraction::result() {
    size_t n = this->cf.size();
    std::cout << "[ ";
    for (int idx=0; idx<n-1; ++idx) {
        std::cout << this->cf[idx] << ", ";
    }
    std::cout << this->cf[n-1] << " ]" << std::endl;
}

void Fraction::print() {
    std::cout << "numerator   : "; this->numer.print();
    std::cout << "denominator : "; this->denom.print();
}

