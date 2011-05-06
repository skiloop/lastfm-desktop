/***************************************************************************
 *   Copyright 2005-2009 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef PLAYBACK_CONTROLS_WIDGET_H_
#define PLAYBACK_CONTROLS_WIDGET_H_

#include <lastfm/RadioStation>

#include "lib/unicorn/StylableWidget.h"

class QPushButton;
class QToolButton;
class AdvancedOptionsDialog;

namespace lastfm{ class RadioStation; };
namespace Phonon{ class VolumeSlider; };

using lastfm::RadioStation;

class PlaybackControlsWidget : public StylableWidget
{
	Q_OBJECT

public:
    PlaybackControlsWidget( QWidget* parent = 0 );

	struct Ui
    {
        QPushButton* radioOptions;
        AdvancedOptionsDialog* radioOptionsDialog;
        Phonon::VolumeSlider* volume;

        QPushButton* love;
        QPushButton* ban;
        QPushButton* play;
        QPushButton* skip;

        QPushButton* info;
        QToolButton* cog;
        QAction* tagAction;
        QAction* shareAction;
    } ui;

    class QAction* m_loveAction;
    class QAction* m_banAction;
    class QAction* m_playAction;
    class QAction* m_skipAction;

    void addWinThumbBarButtons( QList<QAction*>& thumbButtonActions );

private:
    void setButtonsEnabled( bool enabled );
    void saveRadioOptions();
    void restoreRadioOptions();
    void setRadioOptionsChecked();
    void createActions();

public slots:
    void onRadioStopped();
    void onRadioTuningIn( const class RadioStation& );
    void onTrackSpooled( const Track& track );

    void onPlayClicked( bool checked );
    void onRadioOptionsClicked( bool checked );
    void onRadioOptionsFinished( int result );
    void onTagClicked();
    void onShareClicked();
    void onInfoClicked();
    void onSpaceKey();
    void onLoveTriggered();
    void onMuteTriggered();

    void onLoveClicked(bool);

    void onBanClicked();
    void onBanFinished();

    void onActionsChanged();

signals:
    void startRadio(RadioStation);
};


#endif //PLAYBACK_CONTROLS_WIDGET_H_