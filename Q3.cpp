#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigInteger {
private:
    std::vector<int> digits;
    bool isNegative;

public:
    BigInteger() : isNegative(false) {}
    BigInteger(const std::string &num) {
        isNegative = (num[0] == '-');
        for (int i = num.length() - 1; i >= (isNegative ? 1 : 0); --i) {
            digits.push_back(num[i] - '0');
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const BigInteger &num) {
        if (num.isNegative) os << "-";
        for (int i = num.digits.size() - 1; i >= 0; --i) {
            os << num.digits[i];
        }
        return os;
    }

    friend std::istream& operator>>(std::istream &is, BigInteger &num) {
        std::string input;
        is >> input;
        num = BigInteger(input);
        return is;
    }

    BigInteger operator+(const BigInteger &other) const {
        if (isNegative == other.isNegative) {
            BigInteger result;
            result.isNegative = isNegative;
            int carry = 0, sum = 0;
            size_t maxLength = std::max(digits.size(), other.digits.size());
            for (size_t i = 0; i < maxLength || carry; ++i) {
                sum = carry;
                if (i < digits.size()) sum += digits[i];
                if (i < other.digits.size()) sum += other.digits[i];
                result.digits.push_back(sum % 10);
                carry = sum / 10;
            }
            return result;
        }
        return isNegative ? (other - (-(*this))) : (*this - (-other));
    }

    BigInteger operator-() const {
        BigInteger result = *this;
        result.isNegative = !isNegative;
        return result;
    }

    BigInteger operator-(const BigInteger &other) const {
        if (isNegative != other.isNegative) return *this + (-other);
        bool negateResult = (*this < other);
        const BigInteger &larger = negateResult ? other : *this;
        const BigInteger &smaller = negateResult ? *this : other;

        BigInteger result;
        result.isNegative = negateResult;
        int borrow = 0, diff = 0;
        for (size_t i = 0; i < larger.digits.size(); ++i) {
            diff = larger.digits[i] - borrow - (i < smaller.digits.size() ? smaller.digits[i] : 0);
            borrow = (diff < 0);
            if (borrow) diff += 10;
            result.digits.push_back(diff);
        }
        while (result.digits.size() > 1 && result.digits.back() == 0) result.digits.pop_back();
        return result;
    }

    bool operator<(const BigInteger &other) const {
        if (isNegative != other.isNegative) return isNegative;
        if (digits.size() != other.digits.size()) return isNegative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) return isNegative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator==(const BigInteger &other) const {
        return isNegative == other.isNegative && digits == other.digits;
    }

    bool operator!=(const BigInteger &other) const { return !(*this == other); }
    bool operator>(const BigInteger &other) const { return other < *this; }
    bool operator<=(const BigInteger &other) const { return !(other < *this); }
    bool operator>=(const BigInteger &other) const { return !(*this < other); }
};

int main() {
    BigInteger a, b;
    std::cin >> a >> b;
    std::cout << "Sum: " << (a + b) << std::endl;
    std::cout << "Difference: " << (a - b) << std::endl;
    return 0;
}
