#include "DataManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

const QString DataManager::JSON_FILE = "anime_data.json";

QList<AnimeInfo> DataManager::loadAnimeData() {
    QList<AnimeInfo> list;
    QFile file(JSON_FILE);
    
    if (!file.open(QIODevice::ReadOnly)) {
        return list;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return list;

    QJsonArray array = doc.array();
    for (const QJsonValue &value : array) {
        QJsonObject obj = value.toObject();
        AnimeInfo anime;
        anime.id = obj["id"].toInt();
        anime.title = obj["title"].toString();
        anime.imageUrl = obj["image_url"].toString();
        list.append(anime);
    }

    return list;
}

bool DataManager::saveAnimeData(const QList<AnimeInfo>& animeList) {
    QJsonArray array;
    for (const auto &anime : animeList) {
        QJsonObject obj;
        obj["id"] = anime.id;
        obj["title"] = anime.title;
        obj["image_url"] = anime.imageUrl;
        array.append(obj);
    }

    QJsonDocument doc(array);
    QFile file(JSON_FILE);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}