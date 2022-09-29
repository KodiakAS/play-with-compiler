// NOTE: In c++17 and newer standard, there were no temporary created in RVO
// cases

#include <iostream>

#define LOG(x) std::cout << (x) << std::endl

struct Test {
    Test() { LOG("Created!"); }

    Test(const Test& other) { LOG("Copied!"); }

    Test(Test&& other) { LOG("Moved!"); }

    ~Test() { LOG("Destructed!"); }

    Test& operator=(const Test& other) {
        LOG("Assign copied!");
        return *this;
    }

    Test& operator=(Test&& other) {
        LOG("Assign moved!");
        return *this;
    }
};

// This will be optimized to something like: void Nrvo(Test& tt)
Test Nrvo() {
    Test tt = Test();
    return tt;
}

Test NrvoBrokenByStdMove() {
    Test tt = Test();
    return std::move(tt);
}

Test Rvo() {
    return Test();
}

int main() {
    {
        LOG("----- RVO case");

#ifdef DISABLE
        LOG("* 1. ctor (tmp)");
        LOG("* 2. move ctor (tmp) to (tmp for return)");
        LOG("* 3. dtor (tmp)");
        LOG("* 4. move ctor (t1) from (tmp for return)");
        LOG("* 5. dtor (tmp for return)");
        LOG("* 6. dtor (t1)");
#else
        LOG("* 1. ctor (t1)");
        LOG("* 2. dtor (t1)");
#endif

        Test t1 = Rvo();
    }

    {
        LOG("----- NRVO case");

#ifdef DISABLE
        LOG("* one more `Test` constructed than RVO case");
#else
        LOG("* same as RVO");
#endif

        Test t2 = Nrvo();
    }

    {
        LOG("----- NRVO case with std::move");

#ifdef DISABLE
        LOG("* same as NRVO case");
#else
        LOG("* 1. ctor (tmp)");
        LOG("* 2. move ctor (t3) from (tmp)");
        LOG("* 3. dtor (tmp)");
        LOG("* 4. dtor (t3)");
#endif

        Test t3 = NrvoBrokenByStdMove();
    }
}