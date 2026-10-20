#ifndef SEARCHRESULTSMODAL_H
#define SEARCHRESULTSMODAL_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QPixmap>
#include <QNetworkAccessManager>
#include "AnimeInfo.h"

class SearchResultsModal : public QDialog {
    Q_OBJECT

public:
    explicit SearchResultsModal(QWidget *parent = nullptr);
    void setResults(const QList<AnimeInfo> &results);

private slots:
    void onSelectionChanged();
    void onImageDownloaded(QNetworkReply *reply);
    void onConfirmClicked();

private:
    void setupUI();

    QListWidget *m_listWidget;
    QLabel *m_coverLabel;
    QPushButton *m_confirmButton;

    QList<AnimeInfo> m_results;
    QMap<QString, QPixmap> m_imageCache;
    QNetworkAccessManager *m_imageNetworkManager;
};

#endif