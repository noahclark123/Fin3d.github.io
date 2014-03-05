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

#ifndef PROFILE_H
#define PROFILE_H

#include "patheditorfwd/patheditorfwd.h"

#include <QObject>
#include <QPointF>
#include "serialization/serialization.h"

namespace foillogic
{
    class Profile : public QObject
    {
        Q_OBJECT

        // read-only properties
        Q_PROPERTY(qreal thicknessRatio READ thicknessRatio)

        // read-write properties
        Q_PROPERTY(QString symmetry READ symmetryStr WRITE setSymmetryStr)
        Q_PROPERTY(patheditor::Path* topProfile READ pTopProfile WRITE pSetTopProfile)
        Q_PROPERTY(patheditor::Path* botProfile READ pBotProfile WRITE pSetBotProfile RESET pResetBotProfile)

        Q_ENUMS(Symmetry)

    public:
        enum Symmetry { Symmetric, Asymmetric, Flat };

        Q_INVOKABLE explicit Profile(QObject *parent = 0);

        std::shared_ptr<patheditor::Path> topProfile();
        std::shared_ptr<patheditor::Path> botProfile();

        Symmetry symmetry() const;
        void setSymmetry(Symmetry symmetry);

        QPointF topProfileTop(qreal* t_top = 0) const;
        QPointF bottomProfileTop(qreal* t_top = 0) const;
        qreal thickness() const;
        qreal thicknessRatio() const;

        // Q_PROPERTY getters
        QString symmetryStr();
        patheditor::Path* pTopProfile();
        patheditor::Path* pBotProfile();

        // Q_PROPERTY setters
        void setSymmetryStr(QString symmetry);
        void pSetTopProfile(patheditor::Path *topProfile);
        void pSetBotProfile(patheditor::Path *botProfile);

        void pResetBotProfile();

        virtual ~Profile();

    signals:
        void profileChanged(Profile* sender);
        void profileReleased(Profile* sender);

    public slots:

    private:
        Symmetry _symmetry;

        std::shared_ptr<patheditor::Path> _topProfile;
        std::shared_ptr<patheditor::Path> _botProfile;

        QPointF _topProfileTop, _botProfileTop;
        qreal t_topProfileTop, t_botProfileTop;
        qreal _thickness;

        // parts of the profile for connecting when symmetric
        std::shared_ptr<patheditor::CubicBezier> _tPart1;
        std::shared_ptr<patheditor::CubicBezier> _tPart2;
        std::shared_ptr<patheditor::CubicBezier> _bPart1;
        std::shared_ptr<patheditor::CubicBezier> _bPart2;

        void initProfile();

        void mirror(patheditor::CubicBezier* source, patheditor::CubicBezier* destination);

    private slots:
        void onProfileChanged(patheditor::Path *path);
        void onProfileReleased();
    };
}
SERIALIZABLE(foillogic::Profile, profile)

#endif // PROFILE_H
