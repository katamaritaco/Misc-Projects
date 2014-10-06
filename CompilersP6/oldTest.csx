struct Num{
	int num;
};

struct Wrap {
    struct Num wrapper;
};

struct Num integer;

int foo()
{
	integer.num = 5;
}

### TEST FOR MAIN ###
#struct Num main;
#int main;

int main (int argc, bool argv)
{
    cout<< "I'm main!";
}

int i;
bool b; #yolo

void testCout ()
{
	cout << 5;
	cout << (5 + 4);
	#cout << 5 >= 4 ;
	
	cout << foo();
	//TEST THAT WRITING A FUNC WITH A VOID RETURN DOESN'T WORK
	
	cout << (2 + foo());
	
	cout << i;
	cout << b;
	
	cout << i + i;
	cout << i + 3;
	cout << (i == i); 
	
	cout << integer.num;
	#cout << integer;
	#cout << Num;
	
	cout << "test string";
}

void testCin()
{
	cin >> i;
	
	cin >> integer.num;
	
	#cin >> testCin();
}



int getFive(){
return 5;
}

int getSeven(){
return 7;
}

void testIntStuff()
{
	int a;
	int b;
	cout << getFive()-4;
	cout << getFive()+4;
	cout << getFive()/4;
	cout << getFive()*4;
	cout << (getFive()-4*42+43/44/45+46-47);
}
	
void testFnCall(bool bull, int eyent){
}
	
void testFnCalls(int t, bool bo){
	testFnCall(bo, getFive());
}

int goober(int a, bool b, int c)
{
	if (b)
	{
		return a + c;
	}
	else
	{
		return a - c;
	}
}


void zomby()
{

	int zzz;

	zzz = goober(10, true, 2);

}

void testRelationalOps()
{

    int g;
    int h;
    g = 3;
    h = g;
    h++;
    cout << h < g;
    cout << g > h;
    cout << g <= h;
    cout << g >= g;
    cout << (g > g+h*2-4);

}

void testLogicalOps()
{
    bool esrb;
    bool pegi;
    esrb = false;
    pegi = false;
    
    esrb = !esrb;
    cout << esrb && pegi;
    cout << pegi || esrb;
    cout << !pegi && esrb || !pegi;

	cout << pegi && true || 3 < 5;
	
	cout << esrb || !false && 43 >= 2 * 75 - 2000;

}

void equalityTest()
{
    cout << getFive() == getSeven();

    cout << getFive() != getSeven();

    cout << getFive() >= getSeven();

    cout << getFive() <= getSeven();

	cout << goober(getFive(), false, getSeven());
	
	cout << false == false;
	
	cout << false != !false;

    cout << 3 + 5 == 8*0+3-1+5*2-6;

}

void ifTest()
{
    if(false)
    {
    }
    else
    {
    }


	if(!true)
	{
	}
	else
	{
	}

	if(true || !false)
	{
	}
	
	if( getSeven() <= 7 + integer.num)
	{
	}

}

void whileTest()
{
    while(false)
    {
    }

	while(!true)
	{
	}

	while(true || !false)
	{
	}
	
	while( getSeven() <= 7 + integer.num)
	{
	}
}

void assignTestN()
{
    int as;
    int sd;
    int df;
    bool fg;
    bool gh;
    df = 2;
    fg = false;
    gh = true;
    as = sd = df;
    df = sd = integer.num;
    
}
