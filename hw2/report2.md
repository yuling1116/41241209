#include <iostream>
#include <cmath>
using namespace std;

class Polynomial; // forward declaration

// -------- Term Class --------
class Term {
    friend class Polynomial;
private:
    float coef;  // coefficient
    int exp;     // exponent
};

// -------- Polynomial Class --------
class Polynomial {
private:
    Term* termArray; // dynamic array of terms
    int capacity;     // capacity of termArray
    int terms;        // number of used terms

    void resize() {
        capacity *= 2;
        Term* newArray = new Term[capacity];
        for (int i = 0; i < terms; ++i)
            newArray[i] = termArray[i];
        delete[] termArray;
        termArray = newArray;
    }

public:
    // Constructor
    Polynomial() {
        capacity = 10;
        terms = 0;
        termArray = new Term[capacity];
    }

    // Destructor
    ~Polynomial() {
        delete[] termArray;
    }

    // Add a new term
    void newTerm(float coef, int exp) {
        if (terms == capacity) resize();
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        terms++;
    }

    // Evaluate the polynomial at f
    float Eval(float f) {
        float result = 0;
        for (int i = 0; i < terms; ++i) {
            result += termArray[i].coef * pow(f, termArray[i].exp);
        }
        return result;
    }

    // Add another polynomial
    Polynomial Add(Polynomial b) {
        Polynomial result;
        int aPos = 0, bPos = 0;

        while (aPos < terms && bPos < b.terms) {
            if (termArray[aPos].exp == b.termArray[bPos].exp) {
                float sum = termArray[aPos].coef + b.termArray[bPos].coef;
                if (sum != 0)
                    result.newTerm(sum, termArray[aPos].exp);
                aPos++; bPos++;
            }
            else if (termArray[aPos].exp > b.termArray[bPos].exp) {
                result.newTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            }
            else {
                result.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
                bPos++;
            }
        }

        // Copy remaining terms
        while (aPos < terms) {
            result.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        while (bPos < b.terms) {
            result.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }

        return result;
    }

    // Multiply another polynomial
    Polynomial Mult(Polynomial b) {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            for (int j = 0; j < b.terms; ++j) {
                float coef = termArray[i].coef * b.termArray[j].coef;
                int exp = termArray[i].exp + b.termArray[j].exp;

                // Check if same exponent exists
                bool found = false;
                for (int k = 0; k < result.terms; ++k) {
                    if (result.termArray[k].exp == exp) {
                        result.termArray[k].coef += coef;
                        found = true;
                        break;
                    }
                }
                if (!found)
                    result.newTerm(coef, exp);
            }
        }
        return result;
    }

    // Operator Overloading for Input
    friend istream& operator>>(istream& in, Polynomial& p) {
        cout << "Enter number of terms: ";
        in >> p.terms;
        p.capacity = p.terms;
        delete[] p.termArray;
        p.termArray = new Term[p.capacity];

        for (int i = 0; i < p.terms; ++i) {
            cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
            in >> p.termArray[i].coef >> p.termArray[i].exp;
        }
        return in;
    }

    // Operator Overloading for Output
    friend ostream& operator<<(ostream& out, const Polynomial& p) {
        for (int i = 0; i < p.terms; ++i) {
            out << p.termArray[i].coef << "x^" << p.termArray[i].exp;
            if (i != p.terms - 1)
                out << " + ";
        }
        return out;
    }
};
