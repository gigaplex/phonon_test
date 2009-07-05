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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <QUrl>
#include <phonon/videowidget.h>
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>

#include "videowidget.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow), m_videoWidget(new VideoWidget()), m_mediaObject(new CustomMediaObject()), m_audioOutput(new CustomAudioOutput(Phonon::VideoCategory))
{
	ui->setupUi(this);

	connect(m_videoWidget, SIGNAL(doubleClicked(Qt::MouseButton)), this, SLOT(videoDoubleClicked(Qt::MouseButton)));

	Phonon::createPath(m_mediaObject, m_audioOutput);
	Phonon::createPath(m_mediaObject, m_videoWidget);

	QVBoxLayout* videoLayout = findChild<QVBoxLayout*>("videoLayout");

	if (videoLayout)
	{
		m_videoWidget->setObjectName("videoWidget");
		videoLayout->insertWidget(0, m_videoWidget);

		QVBoxLayout* controlsLayout = findChild<QVBoxLayout*>("controlsLayout");

		if (controlsLayout)
		{
			Phonon::SeekSlider* seekSlider = new Phonon::SeekSlider(m_mediaObject);
			seekSlider->setObjectName("seekSlider");
			controlsLayout->insertWidget(0, seekSlider);
		}
	}
}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_mediaObject;
	delete m_audioOutput;
}

void MainWindow::LoadFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files (*.avi *.mp4)"));

	if (fileName.isEmpty())
		return;

	LoadFile(fileName);
}

void MainWindow::LoadFile(const QString& fileName)
{
	Phonon::MediaSource source(fileName);

	m_mediaObject->setCurrentSource(source);

	if (m_mediaObject->state() == Phonon::ErrorState)
		return;

	m_mediaObject->play();

	QPushButton* b = new QPushButton(m_videoWidget);
	b->setText("test");
	b->setAttribute(Qt::WA_TransparentForMouseEvents);
	b->setAutoFillBackground(false);
	b->raise();

	qDebug((QString("Playing ") + fileName).toAscii());
}

void MainWindow::PlayPause()
{
	Phonon::MediaSource::Type type = m_mediaObject->currentSource().type();
	if (type == Phonon::MediaSource::Invalid || type == Phonon::MediaSource::Empty)
	{
		LoadFile();
	}
	else
	{
		if (m_mediaObject->state() == Phonon::PlayingState)
			m_mediaObject->pause();
		else
			m_mediaObject->play();
	}
}

void MainWindow::Stop()
{
	m_mediaObject->stop();
}

void MainWindow::videoDoubleClicked(Qt::MouseButton button)
{
	if (button == Qt::LeftButton)
	{
		Phonon::MediaSource::Type type = m_mediaObject->currentSource().type();
		if (type == Phonon::MediaSource::Invalid || type == Phonon::MediaSource::Empty)
		{
			LoadFile();
		}
		else
		{
			if (m_videoWidget->isFullScreen())
				m_videoWidget->exitFullScreen();
			else
				m_videoWidget->enterFullScreen();
		}
	}
}

void MainWindow::dragEnterEvent(QDragEnterEvent* dragEnterEvent)
{
	if (dragEnterEvent->mimeData()->hasUrls())
	{
		dragEnterEvent->acceptProposedAction();
	}
}

void MainWindow::dropEvent(QDropEvent* dropEvent)
{
	if (dropEvent->mimeData()->hasUrls())
	{
		QList<QUrl> urls = dropEvent->mimeData()->urls();

		if (!urls.isEmpty())
		{
			QUrl url = *urls.begin();
			LoadFile(url.toString());
		}
	}
}