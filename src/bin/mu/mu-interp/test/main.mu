use math; 

//
//	to get this file to work, you need to specificy -main
//	on the mu-interp command line.
//

use math;	// test declaration scope

function: main(void; string[] args)
{
    print("hello world!\n");

    for (int i=0; i < args.size(); i++)
    {
	print(args[i] + " ");
    }
    print("\n");
}
