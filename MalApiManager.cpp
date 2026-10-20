#include "MalApiManager.h"
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MalApiManager::MalApiManager(QObject *parent) : QObject(parent) {
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &MalApiManager::onReplyFinished);
}

void MalApiManager::searchAnime(const QString &query) {
    QUrl url(MAL_API_URL);
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("q", query);
    urlQuery.addQueryItem("limit", "5");
    urlQuery.addQueryItem("fields", "main_picture");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    request.setRawHeader("X-MAL-CLIENT-ID", CLIENT_ID.toUtf8());

    m_networkManager->get(request);
}

void MalApiManager::onReplyFinished(QNetworkReply *reply) {
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        emit searchError(reply->errorString());
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = doc.object();
    QJsonArray dataArray = jsonObj["data"].toArray();

    QList<AnimeInfo> results;
    for (const QJsonValue &value : dataArray) {
        QJsonObject node = value.toObject()["node"].toObject();
        AnimeInfo anime;
        anime.id = node["id"].toInt();
        anime.title = node["title"].toString();
        anime.imageUrl = node["main_picture"].toObject()["medium"].toString();
        results.append(anime);
    }

    emit searchFinished(results);
}