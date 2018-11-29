#include "./fraction.cpp"


typedef struct _coef{
    lint A;
    lint B;
    lint C;
} coef;
/*
class Quad {
    private:
        lint disc;
        std::vector< coef > cv;
        Fraction frac;
    public:
        Quad(lint D);
        ~Quad();
        void show();
};

Quad::Quad( lint D ) {
    disc = D;
    while ( !cv.empty() ) { cv.pop_back(); }
    frac = Fraction( zero, zero );
}
*/

bool is_equivallent_class( cfracs a, cfracs b ) {
    if ( a.size() != b.size() ) return false;
    size_t n   = b.size();
    size_t itr = 0;
    bool   flag = false;
    while ( itr < n ) {
        if ( a == b ) {
            flag = true;
            break;
        }
        lint tmp = b.front();
        b.erase( b.begin() );
        b.push_back( tmp );
        ++itr;
    }
    return flag;
}

int main() {
    Irr a( 2, P( 1, 10 ) );
    Irr b( 2, P( 0, 0 ) );
    Fraction f( a, b );

    f.print();
    // std::cout << f.lint_part() << std::endl;
    // f = f.rationarize();
    f.continued_fraction();
    f.result();
    
    return 0;
}
