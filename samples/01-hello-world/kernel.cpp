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

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <circle/timer.h>
#include <circle/machineinfo.h>
#include <circle/bcmpropertytags.h>
#include <circle/new.h>

CKernel::CKernel (void)
:	CStdlibAppStdio ("02-stdio-hello"), m_LCD()
{
	mActLED.Blink (5);	// show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run (void)
{
	mLogger.Write (GetKernelName (), LogNotice, "LCD Test...");

	u8 buff[61440];
	m_LCD.set_orientation(3);
	CTimer* m_timer = CTimer::Get();
	m_timer->GetLocalTime(sec, us);
	printf("Start Time: %d.%09d\n", *sec, *us);
	Vec2 origin = Vec2(0.0f);
	for (u8 i = 0; i < 255; i++) {
		Matrix3 mat = (Matrix3::identity() * Matrix3::translation(79.5f, 63.5f) * Matrix3::rotation((float) i / 19.0f) * Matrix3::translation(-79.5f, -63.5f)).inverse();
		for (unsigned x = 0; x < 160; x++) {
			for (unsigned y = 0; y < 128; y++) {
				origin.set_x((float) x);
				origin.set_y((float) y);
				Vec2 texPos = mat * origin;
				if (texPos.get_x() < 0 || texPos.get_y() < 0 || texPos.get_x() > 159 || texPos.get_y() > 127) {
					buff[(y * 160 + x) * 3] = 0;
					buff[(y * 160 + x) * 3 + 1] = 0;
					buff[(y * 160 + x) * 3 + 2] = 0;
				}
				else {
					buff[(y * 160 + x) * 3] = (u8) 95 + (u8) texPos.get_x();
					buff[(y * 160 + x) * 3 + 1] = i;
					buff[(y * 160 + x) * 3 + 2] = (u8) 255 - (u8) texPos.get_y() * 2;
				}
			}
		}
		m_LCD.draw_buffer(buff, 61440);
	}
	m_timer->GetLocalTime(sec, us);
	printf("End Time:   %d.%09d\n", *sec, *us);

	Matrix3 *m = new Matrix3();
	*m = Matrix3::identity() * Matrix3::scale(2.0f, 2.0f) * Matrix3::rotation(0.5f);
	Vec2 dest = *m * origin;
	Vec2 inverse = m->inverse() * dest;
	AABB *aabb = new AABB(0.0f, 0.0f, 1.0f, 1.0f);

	printf("origin: %0.6f, %0.6f - ", origin.get_x(), origin.get_y());
	printf("dest: %0.6f, %0.6f - inverse: %0.6f, %0.6f\n", dest.get_x(), dest.get_y(), inverse.get_x(), inverse.get_y());
	printf("aabb %0.6f, %0.6f, %0.6f, %0.6f\n", aabb->x1, aabb->y1, aabb->x2, aabb->y2);


	mLogger.Write (GetKernelName (), LogNotice, "C Standard Library stdin/stdout/stderr Demo");

	mLogger.Write (GetKernelName (), LogNotice, "stdio test...");

	printf("Hello world!\n");
	fprintf(stderr, "Hello world on stderr!\n");

	printf("Type some characters and hit <RETURN>\n");

	char line[200];
	if (fgets(line, sizeof(line), stdin) != nullptr)
	{
		printf("Read '%s' from stdin...\n", line);
	}
	else
	{
		perror("fgets returned NULL");
	}

	char outstr[200];
        time_t const t = time (nullptr);
        struct tm * const tmp = localtime (&t);

        if (tmp == nullptr)
        {
                perror("localtime");
        }
        else if (strftime(outstr, sizeof(outstr), "%D %T", tmp) == 0)
        {
                fprintf(stderr, "strftime returned 0");
        }
        else
        {
                // Do not expect a valid current time as the Raspberry Pi
                // clock has not been set.
                printf("The current date/time is \"%s\"\n", outstr);
        }

	mLogger.Write (GetKernelName (), LogNotice, "C Standard Library Demo finished");

	return ShutdownHalt;
}
