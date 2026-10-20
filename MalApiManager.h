#ifndef MALAPIMANAGER_H
#define MALAPIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include "AnimeInfo.h"

class MalApiManager : public QObject {
    Q_OBJECT

public:
    explicit MalApiManager(QObject *parent = nullptr);
    void searchAnime(const QString &query);

signals:
    void searchFinished(const QList<AnimeInfo> &results);
    void searchError(const QString &errorMessage);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
    const QString MAL_API_URL = "https://api.myanimelist.net/v2/anime";
    const QString CLIENT_ID = "0d269be41a81866d847864c6535c7291";
};

#endif