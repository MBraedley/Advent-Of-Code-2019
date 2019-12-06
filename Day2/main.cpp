static int main()
{
	std::vector<int> program;

	int value;
	char split;

	std::ifstream fileIn( "input.txt" );

	while( fileIn >> value >> split )
	{
		program.push_back(value);
	}
	
	program[1] = 12;
	program[2] = 2;
	
	bool halt = false;
	int sp = 0;
	while( !halt )
	{
		switch( program[sp] )
		{
		case 1:
			program[sp + 3] = program[sp + 1] + program[sp + 2];
			break;
		case 2:
			program[sp + 3] = program[sp + 1] * program[sp + 2];
			break;
		case 99:
			halt = true;
			break;
		default:
			assert(false);
		}
		sp += 4;
	}
	
	std::cout << program[0];
}