/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef CUTELYST_H
#define CUTELYST_H

#include <QObject>
#include <QStringList>

class CutelystAction;
class CutelystEngine;
class CutelystRequest;
class CutelystResponse;
class CutelystDispatcher;
class CutelystController;
class CutelystPrivate;
class Cutelyst : public QObject
{
    Q_OBJECT
public:
    Cutelyst(CutelystEngine *engine, CutelystDispatcher *dispatcher);
    ~Cutelyst();

    bool error() const;

    /**
     * Contains the return value of the last executed action.
     */
    bool state() const;
    void setState(bool state);
    QStringList args() const;
    QString uriPrefix() const;
    CutelystEngine *engine() const;
    CutelystResponse *response() const;

    /**
     * Returns a pointer to the current action
     */
    CutelystAction *action() const;

    /**
     * Returns the namespace of the current action.
     * i.e. the URI prefix corresponding to the controller
     * of the current action. For example:
     * // a class named FooBar which inherits CutelystController
     * c->ns(); // returns 'foo/bar'
     */
    QString ns() const;

    /**
     * Returns the current CutelystRequest object containing
     * information about the client request \sa CutelystRequest
     */
    CutelystRequest *request() const;

    /**
     * Short for the method above
     */
    CutelystRequest *req() const;
    CutelystDispatcher *dispatcher() const;
    CutelystController *controller(const QString &name = QString()) const;
    QString match() const;

    QVariantHash* stash();

    bool dispatch();
    bool detached() const;
    void detach();
    bool forward(const QString &action, const QStringList &arguments = QStringList());
    CutelystAction *getAction(const QString &action, const QString &ns = QString());
    QList<CutelystAction*> getActions(const QString &action, const QString &ns = QString());

Q_SIGNALS:
    void beforePrepareAction(bool *skipMethod);
    void afterPrepareAction();
    void beforeDispatch(bool *skipMethod);
    void afterDispatch();

protected:
    void handleRequest(CutelystRequest *req, CutelystResponse *resp);
    void prepareAction();
    void finalizeHeaders();
    void finalizeCookies();
    void finalizeBody();
    void finalizeError();
    int finalize();

    friend class CutelystApplication;
    friend class CutelystDispatchType;
    CutelystPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(Cutelyst)
};

#endif // CUTELYST_H
