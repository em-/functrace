
func1aa()
{
}
 
func1a()
{
	func1aa(); 
}
 
func1()
{
	func1a(); 
}

func2a()
{
}
 
func2bb()
{
} 

func2b()
{
	func2bb();
}

func2()
{
	func2a();
	func2b(); 
}



func3()
{
} 

main()
{
	func1();
	func2(); 
	func3(); 
}
