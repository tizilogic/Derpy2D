//
// kernel.cpp
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
#include "kernel.h"

#include <stdlib.h>
#include <time.h>
#include <circle/timer.h>
#include <circle/machineinfo.h>
#include <circle/bcmpropertytags.h>
#include <circle/new.h>
#include <circle/types.h>


CKernel::CKernel(void)
:	CStdlibAppStdio ("03-rect"), display(LCD()),
	graphics(new (HEAP_LOW) Graphics())
{
	mActLED.Blink (2);	// show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	mLogger.Write(GetKernelName(), LogNotice, "Rect drawing!");

	u8 logo[150] = {
		1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
		1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
	};

	mLogger.Write(GetKernelName(), LogNotice, "Drawing a single frame with rectangles...");

	graphics->begin(true, Color::black());

	graphics->draw_rect(10.0f, 10.0f, 140.0f, 108.0f, 4.0f, Color(255.0f, 255.0f, 255.0f, 255.0f));
	graphics->fill_rect(14.0f, 14.0f, 132.0f, 100.0f, Color(255.0f, 0.0f, 0.0f, 255.0f));

	//Color c = Color::black();
	for (int i = 0; i < 150; ++i) {
		if (!logo[i]) {
			continue;
		}
		const float x = (float) ((i % 30) * 4);
		const float y = (float) ((i / 30) * 4);
		graphics->fill_rect(20.0f + x, 54.0f + y, 4.0f, 4.0f, Color(255.0f, 255.0f, 255.0f, 255.0f));
	}

	graphics->end(display);

	mLogger.Write (GetKernelName (), LogNotice, "Rect demo finished!");

	return ShutdownHalt;
}
