#include "SearchResultsModal.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>

SearchResultsModal::SearchResultsModal(QWidget *parent) : QDialog(parent) {
    setupUI();
    m_imageNetworkManager = new QNetworkAccessManager(this);
    connect(m_imageNetworkManager, &QNetworkAccessManager::finished, this, &SearchResultsModal::onImageDownloaded);
}

void SearchResultsModal::setupUI() {
    this->setWindowTitle("Selecionar Anime");
    this->resize(600, 350);
    this->setStyleSheet("background-color: #2C1E3D; color: #FFFFFF;");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // Painel Esquerdo: Lista
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QLabel *listLabel = new QLabel("Selecione um anime:", this);
    listLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet("background-color: #6247AA; color: #FFFFFF; font-size: 12px;");

    leftLayout->addWidget(listLabel);
    leftLayout->addWidget(m_listWidget);

    // Painel Direito: Capa do Anime
    QVBoxLayout *rightLayout = new QVBoxLayout();
    m_coverLabel = new QLabel(this);
    m_coverLabel->setFixedSize(150, 220);
    m_coverLabel->setStyleSheet("border: 1px solid #6247AA;");
    m_coverLabel->setScaledContents(true);

    m_confirmButton = new QPushButton("Confirmar Seleção", this);
    m_confirmButton->setStyleSheet("background-color: #6247AA; padding: 8px; border-radius: 4px;");

    rightLayout->addWidget(m_coverLabel);
    rightLayout->addWidget(m_confirmButton);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    connect(m_listWidget, &QListWidget::itemSelectionChanged, this, &SearchResultsModal::onSelectionChanged);
    connect(m_confirmButton, &QPushButton::clicked, this, &SearchResultsModal::onConfirmClicked);
}

void SearchResultsModal::setResults(const QList<AnimeInfo> &results) {
    m_results = results;
    m_listWidget->clear();
    for (const auto &anime : m_results) {
        m_listWidget->addItem(anime.title);
    }
}

void SearchResultsModal::onSelectionChanged() {
    int row = m_listWidget->currentRow();
    if (row < 0 || row >= m_results.size()) return;

    QString imageUrl = m_results[row].imageUrl;

    // Cache check
    if (m_imageCache.contains(imageUrl)) {
        m_coverLabel->setPixmap(m_imageCache[imageUrl]);
    } else {
        m_coverLabel->setText("Carregando...");
        m_imageNetworkManager->get(QNetworkRequest(QUrl(imageUrl)));
    }
}

void SearchResultsModal::onImageDownloaded(QNetworkReply *reply) {
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        
        QString url = reply->url().toString();
        m_imageCache[url] = pixmap;

        int currentRow = m_listWidget->currentRow();
        if (currentRow >= 0 && m_results[currentRow].imageUrl == url) {
            m_coverLabel->setPixmap(pixmap);
        }
    }
}

void SearchResultsModal::onConfirmClicked() {
    int row = m_listWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Aviso", "Por favor, selecione um anime.");
        return;
    }

    // Aqui os dados do anime selecionado podem ser repassados para a janela principal
    this->accept();
}