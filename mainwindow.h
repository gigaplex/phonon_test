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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "videowidget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void LoadFile();
	void LoadFile(const QString& fileName);
	void PlayPause();
	void Stop();

protected slots:
	void videoDoubleClicked(Qt::MouseButton button);

private:
    Ui::MainWindow *ui;
	VideoWidget* m_videoWidget;
	CustomMediaObject* m_mediaObject;
	CustomAudioOutput* m_audioOutput;
};

#endif // MAINWINDOW_H
