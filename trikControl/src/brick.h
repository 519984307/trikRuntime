/* Copyright 2013 - 2015 Yurii Litvinov and CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/QHash>
#include <QtCore/QScopedPointer>

#include "brickInterface.h"

namespace trikControl {

class AnalogSensor;
class Battery;
class ColorSensor;
class DigitalSensor;
class Display;
class Encoder;
class I2cCommunicator;
class Keys;
class Led;
class LineSensor;
class ModuleLoader;
class ObjectSensor;
class PowerMotor;
class PwmCapture;
class RangeSensor;
class ServoMotor;
class VectorSensor;

/// Class representing TRIK controller board and devices installed on it, also provides access
/// to peripherals like motors and sensors.
class Brick : public BrickInterface
{
	Q_OBJECT

public:
	/// Constructor.
	/// @param guiThread - thread in which an application has started. Can be obtaned in main() by code like
	///        QApplication app; app.thread();.
	/// @param systemConfig - file name (with path) of system config, absolute or relative to current directory.
	/// @param modelConfig - file name (with path) of model config, absolute or relative to current directory.
	/// @param startDirPath - path to the directory from which the application was executed (it is expected to be
	///        ending with "/").
	Brick(const QString &systemConfig, const QString &modelConfig, const QString &startDirPath);

	~Brick() override;

	void reset() override;

	DisplayWidgetInterface &graphicsWidget() override;

public slots:
	void playSound(const QString &soundFileName) override;

	void say(const QString &text) override;

	void stop() override;

	MotorInterface *motor(const QString &port) override;

	PwmCaptureInterface *pwmCapture(const QString &port) override;

	SensorInterface *sensor(const QString &port) override;

	QStringList motorPorts(MotorInterface::Type type) const override;

	QStringList pwmCapturePorts() const override;

	QStringList sensorPorts(SensorInterface::Type type) const override;

	QStringList encoderPorts() const override;

	VectorSensorInterface *accelerometer() override;

	VectorSensorInterface *gyroscope() override;

	LineSensorInterface *lineSensor(const QString &port) override;

	ColorSensorInterface *colorSensor(const QString &port) override;

	ObjectSensorInterface *objectSensor(const QString &port) override;

	EncoderInterface *encoder(const QString &port) override;

	BatteryInterface *battery() override;

	KeysInterface *keys() override;

	DisplayInterface *display() override;

	LedInterface *led() override;

private:
	QScopedPointer<I2cCommunicator> mI2cCommunicator;
	QScopedPointer<ModuleLoader> mModuleLoader;

	QScopedPointer<VectorSensor> mAccelerometer;
	QScopedPointer<VectorSensor> mGyroscope;
	QScopedPointer<Battery> mBattery;
	QScopedPointer<Keys> mKeys;
	QScopedPointer<Display> mDisplay;
	QScopedPointer<Led> mLed;

	QHash<QString, ServoMotor *> mServoMotors;  // Has ownership.
	QHash<QString, PwmCapture *> mPwmCaptures;  // Has ownership.
	QHash<QString, PowerMotor *> mPowerMotors;  // Has ownership.
	QHash<QString, AnalogSensor *> mAnalogSensors;  // Has ownership.
	QHash<QString, Encoder *> mEncoders;  // Has ownership.
	QHash<QString, DigitalSensor *> mDigitalSensors;  // Has ownership.
	QHash<QString, RangeSensor *> mRangeSensors;  // Has ownership.
	QHash<QString, LineSensor *> mLineSensors;  // Has ownership.
	QHash<QString, ColorSensor *> mColorSensors;  // Has ownership.
	QHash<QString, ObjectSensor *> mObjectSensors;  // Has ownership.

	QString mPlayWavFileCommand;
	QString mPlayMp3FileCommand;
};

}