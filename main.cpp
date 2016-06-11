#include <stdio.h>
#include <conio.h>

#include "Defs.h"
#include <time.h>

#include "Solution.h"
#include "Direction.h"

#include <iostream>

#include "Field.h"
#include "FieldList.h"

#include "main.h"

int main(void)
{
    try
    {
        Direction::initDirections();
        Solution solution(20);
        /* Field field(
            "######\n"
            "# .@ #\n"
            "#   $#\n"
            "#.$$.#\n"
            "#    #\n"
            "# .$ #\n"
            "######"); //*/

        Field field("#######  \n"
				    "#  .$ ###\n"
			        "# .$.$  #\n"
				    "#*$.$. @#\n"
                    "# .$.$ ##\n"
				    "#  .$  # \n"
				    "######## \n");//*/

        field.print();

        try
        {
            StepList result = solution.find(20, field, FieldList());

            result.print();
        }
        catch (bool)
        {
            std::cout << "Nix gefunden, good Bye" << std::endl;
        }

    }
    catch(char c)
    {
        std::cout << "Trying to instantiate unknown char: '" << c << "'" << std::endl;
    }

	return 0;
}





