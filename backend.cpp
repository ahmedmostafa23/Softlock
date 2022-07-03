#include "BackEnd.h"

BackEnd::BackEnd(QObject *parent)
    : QObject{parent}, aes_object(AES("AES")) {}

void BackEnd::open_file() {
    // opens the file browser dialog and prompts the user to select a file to encrypt.
    selected_file_name = QFileDialog::getOpenFileName(nullptr, "Browse for file to encrypt.");

    qDebug() << "user selected " << selected_file_name << "\n";

    // checks if the user has actually selected anything, or just closed the dialog.
    if (selected_file_name.isEmpty()) {
        // if the user has not selected anything, a signal will be emitted, where it can be handled in QML.
        emit dialog_cancelled(QVariant(QString("open_file")));
        return;
    }

    // opens the file connection with the selected file.
    std::ifstream input_file;
    input_file.open(selected_file_name.toStdString());

    // checks if the file has been successfully open or not.
    if (!input_file) {
        emit file_not_open(QVariant(QString("open_file")));
        return;
    }

    // gets all of the file contents into a string.
    char sub_s;
    std::string s;

    while (input_file.get(sub_s))
    {
        s = s + sub_s;
    }

    // stores contents to a class attribute
    message = s;

    // closes the file connection
    input_file.close();

    // notifies user of success
    qDebug() << "reading complete. file closed\n";

    emit file_success(QVariant(selected_file_name));
}

void BackEnd::encrypt(QString aes_algorithm) {
    QString ciphered = QString::fromStdString(aes_object.cipher(message));
    emit encryption_complete(QVariant(ciphered));
}

void BackEnd::decrypt() {
    QString deciphered = QString::fromStdString(aes_object.decipher());
    emit decryption_complete(QVariant(deciphered));
}
