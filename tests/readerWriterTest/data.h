/* Copyright 2015 CyberTech Labs Ltd.
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
 * limitations under the License.
 *
 * This file was modified by Yurii Litvinov to make it comply with the requirements of trikRuntime
 * project. See git revision history for detailed changes. */

#include <QtCore/QVector>

template<int size>
class Data
{
public:
	Data()
	{
		mData.resize(size);
	}

	Data(const Data &data)
	{
		for (int i = 0; i < size; ++i) {
			write(i, data.read(i));
		}
	}

	void write(int item, int value)
	{
		mData[item] = value;
	}

	int read(int item) const;

private:
	QVector<int> mData;
};
