#include <QApplication>
#include "SearchResultsModal.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Teste temporário da janela para verificar se compila
    SearchResultsModal modal(nullptr);
    modal.show();

    return app.exec();
}