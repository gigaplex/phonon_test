/******************************************************************************
 * Copyright (C) 2009 Tim Boundy <gigaplex@gmail.com>                         *
 *                                                                            *
 * This file is part of phonon_test.                                          *
 *                                                                            *
 * phonon_test is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Lesser General Public License as             *
 * published by the Free Software Foundation, either version 3 of             *
 * the License, or (at your option) any later version.                        *
 *                                                                            *
 * phonon_test is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Lesser General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with phonon_test.                                            *
 * If not, see <http://www.gnu.org/licenses/>.                                *
 ******************************************************************************/

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QtCore/QBasicTimer>

#include <phonon/videowidget.h>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>

class VideoWidget : public Phonon::VideoWidget
{
	Q_OBJECT

public:
	VideoWidget(QWidget* parent = 0);
	virtual ~VideoWidget();

signals:
	void doubleClicked(Qt::MouseButton button);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* mouseEvent);
	bool event(QEvent* event);
	void timerEvent(QTimerEvent* timerEvent);

	QBasicTimer m_timer;
};

// Temporary classes to output debug statements on destruction
class CustomAudioOutput : public Phonon::AudioOutput
{
	Q_OBJECT

public:
	CustomAudioOutput(Phonon::Category category, QObject* parent = 0);
	CustomAudioOutput(QObject* parent = 0);
	virtual ~CustomAudioOutput();
};

class CustomMediaObject : public Phonon::MediaObject
{
	Q_OBJECT

public:
	CustomMediaObject(QObject* parent = 0);
	virtual ~CustomMediaObject();
};

#endif // VIDEOWIDGET_H
