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

void BackEnd::encrypt(QVariant aes_algorithm) {

    // this is going to encrypt the message, and the returned message will be returned to the variable ciphered
    QString ciphered = QString::fromStdString(aes_object.cipher(message));

    // the signal is going to be sent to the QML front end with the ciphered message.
    emit encryption_complete(QVariant(ciphered));
}

void BackEnd::decrypt() {

    // this is going to decrypt the message, and the returned message will be returned to the variable deciphered
    QString deciphered = QString::fromStdString(aes_object.decipher());

    // the signal is going to be sent to the QML front with the deciphered message.
    emit decryption_complete(QVariant(deciphered));
}

void BackEnd::save_file(const std::string& text) {

    // this function is going to receive the encrypted text from the front end (or the aes object), and save it to a file.
    QString save_location = QFileDialog::getSaveFileName(nullptr, "save");
    QDir dir;
    if (!dir.exists(save_location))
        dir.mkpath(save_location);

    std::ofstream output_file(save_location.toStdString());
    if (!output_file) {
        emit file_not_open("save");
        return;
    }

    // writes encrypted text to a file.
    output_file << text;

    output_file.close();

    emit saving_complete();
}
