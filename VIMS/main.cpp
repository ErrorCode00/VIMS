/*
 * ³ÌÐòÖ÷³ÌÐò
 *
 * @author Afeng
 * @date 2019/04/16
 */

/*


		*       *     * * *        *     *          * * *
		 *     *	    *		  * *   * *       *
		  *   *		    *	     *   * *   *        * * *
		   * *		    *	    *     *     *            *
			*		  * * *	   *             *    * * * *

*/
#include <iostream>
#include <fstream>
#include <cassert>
#include "vims.h"
using namespace vims;

int main()
{
	VIMS sys;
	sys.loadData();

	while (true)
	{
		sys.showMenu();
		sys.getResponse();
		system("pause");
	}
	return 0;
}

