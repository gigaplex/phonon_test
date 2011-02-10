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

#include "videowidget.h"

#include <QMouseEvent>
#include <QPainter>

VideoWidget::VideoWidget(QWidget* parent)
		: Phonon::VideoWidget(parent)
{
}

VideoWidget::~VideoWidget()
{
	qDebug("VideoWidget destructor");
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent* mouseEvent)
{
	Phonon::VideoWidget::mouseDoubleClickEvent(mouseEvent);
	doubleClicked(mouseEvent->button());
}

bool VideoWidget::event(QEvent* event)
{
	switch(event->type())
	{
	case QEvent::MouseMove:
		unsetCursor();
	case QEvent::WindowStateChange:
		{
			if (windowState() & Qt::WindowFullScreen)
			{
				m_timer.start(1000, this);
			}
			else
			{
				m_timer.stop();
				unsetCursor();
			}
		}
		break;
	default:
		break;
	}

	return Phonon::VideoWidget::event(event);
}

void VideoWidget::timerEvent(QTimerEvent* timerEvent)
{
	if (timerEvent->timerId() == m_timer.timerId())
	{
		setCursor(Qt::BlankCursor);
	}

	Phonon::VideoWidget::timerEvent(timerEvent);
}

CustomAudioOutput::CustomAudioOutput(Phonon::Category category, QObject* parent)
		: Phonon::AudioOutput(category, parent)
{
}

CustomAudioOutput::CustomAudioOutput(QObject* parent)
		: Phonon::AudioOutput(Phonon::NoCategory, parent)
{
}

CustomAudioOutput::~CustomAudioOutput()
{
	qDebug("CustomAudioOutput destructor");
}

CustomMediaObject::CustomMediaObject(QObject* parent)
		: Phonon::MediaObject(parent)
{
}

CustomMediaObject::~CustomMediaObject()
{
	qDebug("CustomMediaObject destructor");
}
