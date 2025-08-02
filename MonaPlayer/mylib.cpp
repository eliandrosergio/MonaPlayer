#include "mylib.hpp"

// ====================== String ======================

string num_to_string( int n ) {
    string  final;
    int     num = n;

    if (n == 0) return ("0");
    while (n != 0) {
        final += ((n % 10) + '0');
        n /= 10;
    }
    if (num >= 10) {
        int vezes = 0;
        if (num <= 99) vezes = 1;
        else vezes = 2;
        while (vezes--) {
            string fim = final.substr(0, final.size() / 2);
            final.erase(0, final.size() / 2);
            final.append(fim);
        }
    }
    return final;
}
