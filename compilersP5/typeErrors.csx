int i;
bool b;

struct MyStruct {
    int aa;
    bool bb;
};

struct Wrapper {
    int someInt;
    struct MyStruct someStruct;
};

struct Wrapper aStruct;

void testVoid() { }

void coutTest()
{
    //Attempt to write a function
    cout << testVoid;

    //Attempt to write a struct name
    cout << MyStruct;

    //Attempt to write a struct variable
    cout << aStruct;

    //Attempt to write void
    cout << testVoid();
}

void cinTest()
{
    //Attempt to read a function
    cin >> testVoid;
	cin >> testVoid();

    //Attempt to read a struct name
    cin >> Wrapper;

    //Attempt to read a struct variable
    cin >> aStruct;

}

void someFunc(int zz, bool top) { }

int otherFunc(int r) { }

void fnTest()
{
    //Attempt to call a non-function
    i();

    //Function call with wrong number of args
    someFunc(i, b, aStruct.someInt);

    //Type of actual does not match type of formal
    someFunc(b, i);
    
    someFunc(i, otherFunc(-100));
}

int retTestOne()
{
    //Missing return value
    return;
}

void retTestTwo()
{
    //Return with a value in a void function
    return aStruct.someInt;
}

bool retTestThree()
{
    //Bad return value
    return 5;
}


//DO STUFF WITH TRUE AND FALLLLLLLLLLLLLLLLLLLSE

//ALSO UNARY NODES!

void arithOps()
{
    int x;
    bool y;
    
    //Arithmetic operator applied to non-numeric type
    cout << x + y;
    cout << y * x;

    cout << x * x - x / x + y;

    cout << y - x - x - x;

    cout << x + x + y + x;

    cout << x * (y * x);

    cout << -x / -y;

    cout << "java" + i;

    cout << aStruct.someStruct - i;

    cout << y * y;

    cout << !true/7;

    cout << aStruct.someInt - aStruct.someStruct.aa;

    y--;

    aStruct.someStruct.bb++;

    cout << testVoid() / i;
}

void relOps()
{
    int u;
    int v;
    bool w;

    //Relational operator applied to non-numeric operand
    cout << u < w;

    cout << w >= u;

    cout << ( u < v) <= v;
    
    cout << w < w;

    cout << u + v <= v / u;

    cout << u + v > w * u;

    cout << aStruct.someStruct.bb < aStruct.someStruct.bb;

    cout << u < "wisco";

    cout << u < aStruct;

    cout << aStruct.someStruct.bb < retTestOne();

    cout << !false + 7 < 8;

    cout << -u < "test";

}

void logicOps()
{
    int _a;
    int _b;
    bool _cc;
    bool _dd;
    
    //Logical operator applied to non-bool operand
    cout << _cc && _a;

    cout << _b || _dd;

    cout << (aStruct.someInt < _a) && !_a;

    cout << _cc || _dd && (_a > _b) || aStruct.someStruct.aa;

    cout << _a + _b < _a || _b;

    cout << "bucky" && "badger";

    cout << aStruct || b;

    cout << !retTestOne;

    cout << !retTestOne();

    cout << -_a + _b < 8 || !_a;

}


void testIf()
{
    int _a_;

    //Non-bool expression used as an if condition
    if (_a_)
    {
        _a_++;

        if (_a_ && aStruct.someStruct.bb)
        {
            _a_--;
        }
    }

    _a_ = 5;

    if (-_a_ / aStruct.someInt)
    {
        aStruct.someInt = 5;
    }
    else
    {
        aStruct.someInt = 6;
    }

    if (testVoid || !true)
    {

    }
    else
    {

    }

    if (testVoid())
    {

    }

    if ("may the force be with you")
    {

    }

}

void testWhile()
{
    bool myBool;


    //Non-bool expression used as a while condition
    while(i)
    {
        i = i - 2;
    }

    while (i * -i)
    {
        cout << "hello!";
    }

    while (aStruct)
    {

    }

    while ("mario and luigi")
    {

    }

    while(myBool || myBool && !myBool && !retTestOne)
    {

    }
}

void mismatchTest()
{
    int p;
    bool q;

    //Type mismatch
    q = p == p;

    q = p != q;

    q = p + 1;

    p = q && !q;

    p = q && (!q > (p * 2)) || !p;

    p = "string literal";

    q = aStruct.someInt + retTestOne;

    q = testVoid() == retTestOne();

    if (p == q)
    {
        cout << "whoops";
    }
    
    p = i = aStruct.someInt = aStruct.someStruct.bb - 4;

    i = p = aStruct.someStruct.bb;

}

void eqTestOne()
{
    //Equality operator applied to void functions
    cout << testVoid() == testVoid();
}

void eqTestTwo()
{
    //Equality operator applied to functions
    cout << testVoid != eqTestOne;
}

void eqTestThree()
{
    //Equality operator applied to struct names
    cout << Wrapper == MyStruct;
}

void eqTestFour()
{
    //Equality operator applied to struct variables
    cout << aStruct != aStruct.someStruct;
}

void structAssign()
{
    struct MyStruct abc;

    //Struct name assignment
    Wrapper = MyStruct;
    
    //Stuct variable assignment
    aStruct.someStruct = aStruct = abc;
    
}  




##USE BECKS TEST!

