// #include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MOD 11

class Element {
private:
    int m_data;

public:
    Element() : m_data(0) {}
    ~Element() {}
    Element(int data) : m_data(data % MOD) {
        if (m_data < 0) m_data += MOD; 
    }
    Element(const Element& e) : m_data(e.m_data) {}
    Element& operator=(const Element& e) {
        if (this != &e) m_data = e.m_data;
        return *this;
    }

    friend Element operator+(const Element& e1, const Element& e2);
    friend Element operator*(const Element& e1, const Element& e2);

    int getData() const { return m_data; }
};

Element operator+(const Element& e1, const Element& e2) {
    return Element((e1.m_data + e2.m_data) % MOD);
}

Element operator*(const Element& e1, const Element& e2) {
    return Element((e1.m_data * e2.m_data) % MOD);
}

// 加法封闭性判断
bool IsAddClosed(const vector<Element>& aset) {
    for (size_t i = 0; i < aset.size(); ++i) {
        for (size_t j = 0; j < aset.size(); ++j) {
            Element sum = aset[i] + aset[j];
            bool found = false;
            for (const auto& elem : aset) {
                if (elem.getData() == sum.getData()) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
    }
    return true;
}

// 加法结合律判断
bool IsAddAssociativitySatisfied(const vector<Element>& aset) {
    for (size_t i = 0; i < aset.size(); ++i) {
        for (size_t j = 0; j < aset.size(); ++j) {
            for (size_t k = 0; k < aset.size(); ++k) {
                Element left = (aset[i] + aset[j]) + aset[k];
                Element right = aset[i] + (aset[j] + aset[k]);
                if (left.getData() != right.getData()) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 加法单位元判断
bool IsAddIdentityExist(const vector<Element>& aset, Element& Identity) {
    for (const auto& e : aset) {
        bool isIdentity = true;
        for (const auto& a : aset) {
            Element sum = a + e;
            if (sum.getData() != a.getData()) {
                isIdentity = false;
                break;
            }
        }
        if (isIdentity) {
            Identity = e; 
            return true;
        }
    }
    return false;
}

// 加法逆元判断
bool EachHasInverse4Add(const vector<Element>& aset) {
    Element identity; 
    if (!IsAddIdentityExist(aset, identity)) {
        return false;
    }
    for (const auto& a : aset) {
        bool hasInverse = false;
        for (const auto& b : aset) {
            Element sum = a + b;
            if (sum.getData() == identity.getData()) {
                hasInverse = true;
                break;
            }
        }
        if (!hasInverse) {
            return false;
        }
    }
    return true;
}

// 乘法封闭性判断
bool IsMultClosed(const vector<Element>& aset) {
    for (size_t i = 0; i < aset.size(); ++i) {
        for (size_t j = 0; j < aset.size(); ++j) {
            Element product = aset[i] * aset[j];
            bool found = false;
            for (const auto& elem : aset) {
                if (elem.getData() == product.getData()) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
    }
    return true;
}

// 乘法结合律判断
bool IsMultAssociativitySatisfied(const vector<Element>& aset) {
    for (size_t i = 0; i < aset.size(); ++i) {
        for (size_t j = 0; j < aset.size(); ++j) {
            for (size_t k = 0; k < aset.size(); ++k) {
                Element left = (aset[i] * aset[j]) * aset[k];
                Element right = aset[i] * (aset[j] * aset[k]);
                if (left.getData() != right.getData()) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 乘法单位元判断
bool IsMultIdentityExist(const vector<Element>& aset, Element& Identity) {
    for (const auto& e : aset) {
        bool isIdentity = true;
        for (const auto& a : aset) {
            Element product = a * e;
            if (product.getData() != a.getData()) {
                isIdentity = false;
                break;
            }
        }
        if (isIdentity) {
            Identity = e; 
            return true;
        }
    }
    return false;
}

// 乘法逆元判断
bool EachHasInverse4Mult(const vector<Element>& aset) {
    Element identity; 
    if (!IsMultIdentityExist(aset, identity)) {
        return false;
    }
    for (const auto& a : aset) {
        if (a.getData() == 0) continue; 
        bool hasInverse = false;
        for (const auto& b : aset) {
            Element product = a * b;
            if (product.getData() == identity.getData()) {
                hasInverse = true;
                break;
            }
        }
        if (!hasInverse) {
            return false;
        }
    }
    return true;
}

// 辅助函数：将布尔结果转为汉字描述
string boolToChinese(bool result) {
    return result ? "是" : "否";
}

int main()
{
    vector<Element> aset;
    for (int i = 0; i < MOD; i++)
    {
        Element tmp(i);
        aset.push_back(tmp);
    }
    Element tmpIdentity(-1);
    cout << "加法运算是否封闭: " << boolToChinese(IsAddClosed(aset)) << endl;
    cout << "加法运算是否满足结合律: " << boolToChinese(IsAddAssociativitySatisfied(aset)) << endl;
    cout << "加法运算是否存在单位元: " << boolToChinese(IsAddIdentityExist(aset, tmpIdentity)) << endl;
    cout << "加法运算中每个元素是否都有逆元: " << boolToChinese(EachHasInverse4Add(aset)) << endl;

    Element tmpIdentity2(-1);
    cout << "乘法运算是否封闭: " << boolToChinese(IsMultClosed(aset)) << endl;
    cout << "乘法运算是否满足结合律: " << boolToChinese(IsMultAssociativitySatisfied(aset)) << endl;
    cout << "乘法运算是否存在单位元: " << boolToChinese(IsMultIdentityExist(aset, tmpIdentity2)) << endl;
    cout << "乘法运算中非零元素是否都有逆元: " << boolToChinese(EachHasInverse4Mult(aset)) << endl;

    system("pause");
    return 0;
}