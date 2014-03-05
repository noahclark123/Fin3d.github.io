/****************************************************************************
  
 Copyright (c) 2013, Hans Robeers
 All rights reserved.
 
 BSD 2-Clause License
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
   * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
   
   * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
   
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
****************************************************************************/

#ifndef THICKNESSPROFILE_H
#define THICKNESSPROFILE_H

#include "patheditorfwd/patheditorfwd.h"

#include <QObject>
#include <memory>
#include "serialization/serialization.h"

namespace foillogic
{
    class ThicknessProfile : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(patheditor::Path* topProfile READ pTopProfile WRITE pSetTopProfile)

    public:
        Q_INVOKABLE explicit ThicknessProfile(QObject *parent = 0);

        std::shared_ptr<patheditor::Path> topProfile();
        std::shared_ptr<patheditor::Path> botProfile();

        // Q_PROPERTY getters
        patheditor::Path* pTopProfile();

        // Q_PROPERTY setters
        void pSetTopProfile(patheditor::Path *topProfile);

        virtual ~ThicknessProfile();

    signals:
        void profileChanged(ThicknessProfile* sender);
        void profileReleased(ThicknessProfile* sender);

        void mirrored();

    public slots:
        void setThicknessRatio(qreal profileRatio);

    private:
        qreal _thicknessRatio;

        std::shared_ptr<patheditor::Path> _topProfile;
        std::shared_ptr<patheditor::Path> _botProfile;

        std::shared_ptr<patheditor::CubicBezier> _topBezier;
        std::shared_ptr<patheditor::CubicBezier> _botBezier;

        void mirror();

    private slots:
        void onProfileChanged(patheditor::Path *path);
        void onProfileReleased();
    };
}
SERIALIZABLE(foillogic::ThicknessProfile, tProfile)

#endif // THICKNESSPROFILE_H
