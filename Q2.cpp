#include <iostream>
#include <vector>
#include <algorithm>

class Polynomial;

class PolynomialUtils {
public:
    static int evaluate(const Polynomial& p, int x);
    static Polynomial derivative(const Polynomial& p);
};

class Polynomial {
private:
    std::vector<int> coefficients;
    void trim() {
        while (!coefficients.empty() && coefficients.back() == 0) {
            coefficients.pop_back();
        }
    }

public:
    Polynomial() {}
    Polynomial(const std::vector<int>& coeffs) : coefficients(coeffs) {
        trim();
    }

    Polynomial operator+(const Polynomial& other) const {
        std::vector<int> result(std::max(coefficients.size(), other.coefficients.size()), 0);
        for (size_t i = 0; i < coefficients.size(); i++)
            result[i] += coefficients[i];
        for (size_t i = 0; i < other.coefficients.size(); i++)
            result[i] += other.coefficients[i];
        return Polynomial(result);
    }

    Polynomial operator-(const Polynomial& other) const {
        std::vector<int> result(std::max(coefficients.size(), other.coefficients.size()), 0);
        for (size_t i = 0; i < coefficients.size(); i++)
            result[i] += coefficients[i];
        for (size_t i = 0; i < other.coefficients.size(); i++)
            result[i] -= other.coefficients[i];
        return Polynomial(result);
    }

    Polynomial operator*(const Polynomial& other) const {
        std::vector<int> result(coefficients.size() + other.coefficients.size() - 1, 0);
        for (size_t i = 0; i < coefficients.size(); i++) {
            for (size_t j = 0; j < other.coefficients.size(); j++) {
                result[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        return Polynomial(result);
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
        if (p.coefficients.empty()) {
            os << "0";
            return os;
        }
        bool first = true;
        for (int i = p.coefficients.size() - 1; i >= 0; i--) {
            if (p.coefficients[i] != 0) {
                if (!first)
                    os << (p.coefficients[i] > 0 ? " + " : " - ");
                else if (p.coefficients[i] < 0)
                    os << "-";
                first = false;
                os << std::abs(p.coefficients[i]);
                if (i > 0) os << "x^" << i;
            }
        }
        return os;
    }

    friend class PolynomialUtils;
};

int PolynomialUtils::evaluate(const Polynomial& p, int x) {
    int result = 0, power = 1;
    for (int coeff : p.coefficients) {
        result += coeff * power;
        power *= x;
    }
    return result;
}

Polynomial PolynomialUtils::derivative(const Polynomial& p) {
    if (p.coefficients.size() <= 1) return Polynomial({0});
    std::vector<int> deriv(p.coefficients.size() - 1);
    for (size_t i = 1; i < p.coefficients.size(); i++) {
        deriv[i - 1] = p.coefficients[i] * i;
    }
    return Polynomial(deriv);
}

int main() {
    Polynomial p1({3, 0, 2});
    Polynomial p2({1, 1});
    std::cout << "p1: " << p1 << "\n";
    std::cout << "p2: " << p2 << "\n";
    std::cout << "p1 + p2: " << (p1 + p2) << "\n";
    std::cout << "p1 * p2: " << (p1 * p2) << "\n";
    std::cout << "Derivative of p1: " << PolynomialUtils::derivative(p1) << "\n";
    std::cout << "p1 evaluated at x = 2: " << PolynomialUtils::evaluate(p1, 2) << "\n";
    return 0;
}

