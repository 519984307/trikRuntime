/* Copyright 2014 CyberTech Labs Ltd.
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

#include "trikScriptRunnerInterface.h"
#include <QFileInfo>

namespace trikNetwork {
class MailboxInterface;
}

namespace trikControl {
class BrickInterface;
}

namespace trikScriptRunner {

enum ScriptType { // must be 0, 1, ..
	JAVASCRIPT,
	PYTHON,

	ScriptTypeLength // should always be the last
};

/// General wrapper for other executors (such as Python, JavaScript)
class TrikScriptRunner : public TrikScriptRunnerInterface
{
	Q_OBJECT
public:
	/// Constructor.
	/// @param brick - reference to trikControl::Brick instance.
	/// @param mailbox - mailbox object used to communicate with other robots.
	TrikScriptRunner(trikControl::BrickInterface &brick
					 , trikNetwork::MailboxInterface * const mailbox
					 );

	~TrikScriptRunner();

	void registerUserFunction(const QString &name, QScriptEngine::FunctionSignature function) override;
	void addCustomEngineInitStep(const std::function<void (QScriptEngine *)> &step) override;

	/// Gets all method names from executive objects (brick, script, etc.) from ScriptEngineWorker
	/// (useful when used from outside of the TrikRuntime).
	QStringList knownMethodNames() const;

public slots:
	void run(const QString &script, const QString &fileName = "") override;
	void run(const QString &script, const ScriptType &stype, const QString &fileName = "");
	void runDirectCommand(const QString &command) override;
	void abort() override;
	void brickBeep() override;

private:
	trikControl::BrickInterface &brick;
	trikNetwork::MailboxInterface * mailbox;
	TrikScriptRunnerInterface * mScriptRunnerArray[ScriptTypeLength] = {nullptr};
	ScriptType mLastRunner;
};

}
