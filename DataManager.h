#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QList>
#include "AnimeInfo.h"

class DataManager {
public:
    static const QString JSON_FILE;

    static QList<AnimeInfo> loadAnimeData();
    static bool saveAnimeData(const QList<AnimeInfo>& animeList);
};

#endif