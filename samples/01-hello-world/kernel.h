//
// kernel.h
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _kernel_h
#define _kernel_h

#include <circle_stdlib_app.h>
#include "derpy2d/st7735.h"
#include "derpy2d/vec.h"
#include "derpy2d/matrix.h"
#include "derpy2d/aabb.h"

class CKernel : public CStdlibAppStdio
{
public:
	CKernel (void);

	TShutdownMode Run (void);

private:
	LCD m_LCD;
	unsigned *sec, *us;
};

#endif

