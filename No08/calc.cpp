#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define blank ' '

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int pow(int a, int b);

int abs(int a);

int main() {
    int result = 0;
    fstream file;
    file.open("calc.txt", ios::in);
	if (!file) {
		cout << "No such file";
	}
	else {
        int temp = 0;
		char c, op = blank;
        bool fop = true, ready = false;
        string s;

		while (true) {
			file >> noskipws >> c;		// read a character from the file

            if (fop) {
                if (c == blank) {
                    fop = false;
                    s.push_back(' ');
                    continue;
                }
                int t = c - '0';
                if (t > 9 || t < 0) {
                    cout << "Error: invalid input";
                    break;
                }
                result = result*10 + t;
            } else {
                int t = c - '0';
                if (c == blank || file.eof()) {
                    if (temp != 0) ready = true;
                } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                    if (op != blank) {
                        cout << "Error: multiple operators" << endl;
                        break;
                    }
                    op = c;
                } else if (0 <= t && t <= 9) {
                    if (op == blank) {
                        cout << "Error: missing operator" << endl;
                        break;
                    }
                    temp = temp*10 + t;
                } else {
                    cout << "Error: invalid input" << endl;
                    break;
                }
            } 

            if (ready) {
                switch (op) {
                    case '+':
                        result = add(result, temp);                 
                        break;
                    case '-':
                        result = subtract(result, temp);
                        break;
                    case '*':
                        result = multiply(result, temp);
                        break;
                    case '/':
                        result = divide(result, temp);
                        break;
                    case '^':
                        result = pow(result, temp);
                        break;
                    default:
                        break;
                }
                op = blank;
                temp = 0;
                ready = false;
            }

            if (file.eof()) {
                if (temp == 0) cout << "Error: missing operand" << endl;
                else cout << s << " = " << result << endl;
                break;
            }
            s.push_back(c);
		}    
	}

	file.close();
    return 0;
}

int add(int a, int b) {
    loop:
       int carry = a & b;
       a ^= b; 
       b = carry << 1;
       if (b != 0) goto loop;
    return a;
}

int subtract(int a, int b) {
    loop:
        int borrow = ~a &  b;
        a ^= b;
        b = borrow << 1;
        if (b != 0) goto loop;
    return a;
}

int multiply(int a, int b) {
    int result = 0;

    if (b < 0) goto loop2;
    loop1:
        result = add(result, a);
        b = subtract(b, 1);
        if (b > 0) goto loop1;
        else return result;
    
    loop2:
        result = subtract(result, a);
        b = add(b, 1);
        if (b < 0) goto loop2;
        else return result;
}

int divide(int a, int b) {
    int divisor = 0;

    if (a < 0 || b < 0)  {
        if (a < 0 && b < 0) goto loop1;
        goto loop2;
    } 

    loop1:
        if (abs(a) >= abs(b)) {
            a = subtract(abs(a), abs(b));
            divisor = add(divisor, 1);
            goto loop1;
        } 
        else return divisor;
    
    loop2:
        if (abs(a) >= abs(b)) {
            a = subtract(abs(a), abs(b));
            divisor = subtract(divisor, 1);
            goto loop2;
        } 
        else return divisor;
}

int pow(int a, int b) {
    int result = 1;

    if (b < 0) {
        cout << "Error: Negative exponent" << endl;
        return 0;
    }
    loop:
        result = multiply(result, a);
        b = subtract(b, 1);
        if (b > 0) goto loop;
        else return result;
}

int abs(int a) {
    int mask = a >> 31;
    a ^= mask;
    a -= mask;
    return a;
}