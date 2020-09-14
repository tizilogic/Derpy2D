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


CKernel::CKernel(void)
:	CStdlibAppStdio ("02-image"), display(LCD()),
	graphics(new (HEAP_LOW) Graphics()), assets()
{
	mActLED.Blink (2);	// show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	mLogger.Write(GetKernelName(), LogNotice, "Image sample!");

	mLogger.Write(GetKernelName(), LogNotice, "Scanning for assets");
	assets.scan();

	mLogger.Write(GetKernelName(), LogNotice, "Loading images into memory");
	Image& logo = assets.image("logo.raw");
	Image& pluto = assets.image("pluto.raw");

	mLogger.Write(GetKernelName(), LogNotice, "Entering main loop...");
	Matrix3 t = Matrix3::scale(0.75, 0.75);
	float x = 0.0f, y = 0.0f, sx = 0.6, sy = 0.4, r=0.0;
	while (true) {
		graphics->begin(true, Color::black());

		graphics->set_opacity(1.0);
		graphics->draw_image(pluto, 8.5f, 0.0f);

		graphics->set_opacity(0.4);
		graphics->set_transform(t * Matrix3::translation(x + 64.0f, y + 64.0f)
								* Matrix3::rotation(r)
								* Matrix3::translation(-64.0f, -64.0f));
		graphics->draw_image(logo, 0.0f, 0.0f);
		graphics->clear_transform();

		graphics->end(display);
		x += sx;
		y += sy;
		if (x < 0.0f) {
			x = 0.0f;
			sx = -sx;
		}
		else if (x + 96.0f >= 159.0f) {
			x = 159.0f - 96.0f;
			sx = -sx;
		}
		if (y < 0.0f) {
			y = 0.0f;
			sy = -sy;
		}
		else if (y + 96.0f >= 127.0f) {
			y = 127.0f - 96.0f;
			sy = -sy;
		}
		r += 0.06f;
	}

	mLogger.Write (GetKernelName (), LogNotice, "Will never reach this point.");

	return ShutdownHalt;
}
