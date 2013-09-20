/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "powerMotor.h"

#include <QtCore/QDebug>

using namespace trikControl;

void PowerMotor::init(int engine)
{
	mEngine = engine;
	mPower = 0;
}


void PowerMotor::setPower(int power)
{
	if (power > 100) {
		power = 100;
	} else if (power < -100) {
		power = -100;
	}

	mPower = power;

	char command[100] = {0};

	sprintf(command, "i2cset -y 2 0x48 0x1%d 0x%x w", mEngine, static_cast<unsigned char>(power));

	qDebug() << QString(command);

	system(command);
}

int PowerMotor::power() const
{
	return mPower;
}


void PowerMotor::powerOff()
{
	setPower(0);
}
