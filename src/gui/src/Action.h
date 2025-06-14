/*
 * barrier -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2008 Volker Lanz (vl@fidra.de)
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined(ACTION_H)

#define ACTION_H

#include "KeySequence.h"

#include <QString>
#include <QStringList>
#include <QList>

class ActionDialog;
class QSettings;
class QTextStream;

class Action
{
    public:
        enum ActionType { keyDown, keyUp, keystroke,
                          switchToScreen, toggleScreen, switchInDirection,
                          lockCursorToScreen, mouseDown, mouseUp, mousebutton };
        enum SwitchDirection { switchLeft, switchRight, switchUp, switchDown };
        enum LockCursorMode { lockCursorToggle, lockCursonOn, lockCursorOff  };

    public:
        Action();

    public:
        QString text() const;
        const KeySequence& keySequence() const { return m_KeySequence; }
        void setKeySequence(const KeySequence& seq) { m_KeySequence = seq; }

        void loadSettings(QSettings& settings);
        void saveSettings(QSettings& settings) const;

        int type() const { return m_Type; }
        void setType(int t) { m_Type = t; }

        const QStringList& typeScreenNames() const { return m_TypeScreenNames; }
        void appendTypeScreenName(QString name) { m_TypeScreenNames.append(name); }
        void clearTypeScreenNames() { m_TypeScreenNames.clear(); }

        const QString& switchScreenName() const { return m_SwitchScreenName; }
        void setSwitchScreenName(const QString& n) { m_SwitchScreenName = n; }

        int switchDirection() const { return m_SwitchDirection; }
        void setSwitchDirection(int d) { m_SwitchDirection = d; }

        int lockCursorMode() const { return m_LockCursorMode; }
        void setLockCursorMode(int m) { m_LockCursorMode = m; }

        bool activeOnRelease() const { return m_ActiveOnRelease; }
        void setActiveOnRelease(bool b) { m_ActiveOnRelease = b; }

        bool haveScreens() const { return m_HasScreens; }
        void setHaveScreens(bool b) { m_HasScreens = b; }

        bool hasCustomPosition() const { return m_hasCustomPosition; }
        void setHasCustomPosition(bool b) { m_hasCustomPosition = b; }
        
        int customX() const { return m_customX; }
        void setCustomX(int x) { m_customX = x; }
        
        int customY() const { return m_customY; }
        void setCustomY(int y) { m_customY = y; }

    private:
        KeySequence m_KeySequence;
        int m_Type;
        QStringList m_TypeScreenNames;
        QString m_SwitchScreenName;
        int m_SwitchDirection;
        int m_LockCursorMode;
        bool m_ActiveOnRelease;
        bool m_HasScreens;
        bool m_hasCustomPosition;
        int m_customX;
        int m_customY;

        static const char* m_ActionTypeNames[];
        static const char* m_SwitchDirectionNames[];
        static const char* m_LockCursorModeNames[];
};

QTextStream& operator<<(QTextStream& outStream, const Action& action);

#endif
