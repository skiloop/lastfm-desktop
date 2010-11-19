/*
   Copyright 2005-2009 Last.fm Ltd. 
      - Primarily authored by Jono Cole

   This file is part of the Last.fm Desktop Application Suite.

   lastfm-desktop is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lastfm-desktop is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with lastfm-desktop.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef AUTH_IN_PROGRESS_PAGE_H
#define AUTH_IN_PROGRESS_PAGE_H

#include <QWizardPage>

namespace unicorn{ 
    class LoginProcess;
    class Session;
}

class AuthInProgressPage : public QWizardPage {
    Q_OBJECT
public:
    AuthInProgressPage( QWizard* parent );
    virtual void initializePage();

public slots:
    void onAuthenticated( unicorn::Session* );

protected:
    unicorn::LoginProcess* m_loginProcess;
};

#endif //AUTH_IN_PROGRESS_PAGE_H
