/****************************************************************************
**
** Copyright (C) 2013 Jolla Ltd.
** Contact: Petri M. Gerdt <petri.gerdt@jollamobile.com>
**
****************************************************************************/

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QMap>
#include <QThread>

#include "link.h"
#include "tab.h"

class DBWorker;

class DBManager : public QObject
{
    Q_OBJECT
public:
    static DBManager *instance();
    virtual ~DBManager();

    void createTab(const Tab &tab);
    void getAllTabs();
    void removeTab(int tabId);
    void removeAllTabs();
    void navigateTo(int tabId, QString url, QString title = "", QString path = "");
    void goForward(int tabId);
    void goBack(int tabId);

    void updateThumbPath(int tabId, QString path);
    void updateTitle(int tabId, QString url, QString title);

    void removeHistoryEntry(int linkId);
    void clearHistory();
    void getHistory(const QString &filter = "");
    void getTabHistory(int tabId);

    void saveSetting(QString name, QString value);
    QString getSetting(QString name);
    void deleteSetting(QString name);

    int getMaxTabId();

signals:
    void tabsAvailable(QList<Tab> tab);
    void historyAvailable(QList<Link> links);
    void tabHistoryAvailable(int tabId, QList<Link> links, int currentLinkId);
    void thumbPathChanged(int tabId, QString path);
    void titleChanged(QString url, QString title);
    void settingsChanged();

private:
    DBManager(QObject *parent = 0);

    QMap<QString, QString> m_settings;

    QThread workerThread;
    DBWorker *worker;
};

#endif // DBMANAGER_H
