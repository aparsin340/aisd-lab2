#include <iostream>
#include "LinkedList.h"
#include <random>
#include <cstring>

typedef unsigned short digit;

struct Lodger {
    char name[64];
    size_t age;
};

std::ostream& operator<<(std::ostream& os, Lodger lodger) {
    os << lodger.name << " (" << lodger.age << ")";
    return os;
}

void task_9(size_t n) {
    const char NAMES[][64] = {"Иван", "Виктор", "Анастасия", "Александр", "Елизавета", "Олег", "Галина", "Владислав", "Виктория", "Михаил"};
    std::random_device rd = std::random_device();
    std::mt19937_64 rand_int = std::mt19937_64(rd());
    std::uniform_int_distribution<size_t> ages = std::uniform_int_distribution<size_t>(16, 50);
    
    LinkedList<Lodger> addres_book[10];
    std::uniform_int_distribution<size_t> idx = std::uniform_int_distribution<size_t>(0, 9);

    for (size_t i = 0; i < n; i++) {
        Lodger l = Lodger();
        strcpy_s(l.name, NAMES[idx(rand_int)]);
        l.age = ages(rand_int);

        addres_book[idx(rand_int)].push_head(l);
    }
    std::cout << "Адресная книга:\n";
    for (size_t i = 0; i < 10; i++) {
        if (!addres_book[i].empty())
            std::cout << " \tКвартира №" << i + 1 << ": " << addres_book[i] << "\n";
    }
}

LinkedList<digit> int_to_list(int number) {
    LinkedList<digit> list = LinkedList<digit>();
    while (number) {
        list.push_head(number % 10);
        number /= 10;
    }
    return list;
}

LinkedList<digit> task_2_sum(const LinkedList<digit>& num1, const LinkedList<digit>& num2) {
    LinkedList<digit> res = LinkedList<digit>();
    digit remainder = 0;
    digit sum = 0;
    if (num1.size() > num2.size()) {
        for(size_t i = 0; i < num1.size(); i++) {
            if (i < num2.size())
                sum = num1[num1.size() - i - 1] + num2[num2.size() - i - 1] + remainder;
            else
                sum = num1[num1.size() - i - 1] + remainder;

            if (sum > 9) {
                remainder = 1;
                sum -= 10;
            }
            else 
                remainder = 0;
            res.push_head(sum);
        }
    }
    else {
        for(size_t i = 0; i < num2.size(); i++) {
            if (i < num1.size())
                sum = num2[num2.size() - i - 1] + num1[num1.size() - i - 1] + remainder;
            else
                sum = num2[num2.size() - i - 1] + remainder;

            if (sum > 9) {
                remainder = 1;
                sum -= 10;
            }
            else 
                remainder = 0;
            res.push_head(sum);
        }
    }
    if (remainder)
        res.push_head(remainder);
    return res;
}

LinkedList<digit> task_2_mult(const LinkedList<digit>& num1, const LinkedList<digit>& num2) {
    LinkedList<digit> res = LinkedList<digit>();
    digit mult = 0;
    digit remainder = 0;
    digit prod = 0;
    for (size_t i = 0; i < num1.size(); i++) {
        mult = num1[num1.size() - i - 1];
        LinkedList<digit> sum = LinkedList<digit>();
        for (size_t k = 0; k < i; k++)
            sum.push_tail(0);

        for (size_t j = 0; j < num2.size(); j++) {
            prod = mult * num2[num2.size() - j - 1] + remainder;
            if (prod > 9) {
                remainder = prod / 10;
                prod = prod % 10;
            }
            else 
                remainder = 0;
            sum.push_head(prod);
        }
        if (remainder) {
            sum.push_head(remainder);
            remainder = 0;
        }
        res = task_2_sum(res, sum);
    }
    return res;
}

int main() {
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    std::ios::sync_with_stdio(false);

    LinkedList<digit> number1 = int_to_list(INT_MAX);
    LinkedList<digit> number2 = int_to_list(INT_MAX);
    std::cout << task_2_mult(number1, number2) << "\n";

    // task_9(25);
}
