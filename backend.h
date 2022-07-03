#pragma once

#include <QObject>

#include <QDebug>
#include <fstream>
#include <QFileDialog>
#include <AES/AES.h>

class BackEnd : public QObject {
private:
    Q_OBJECT

    QString selected_file_name;
    QString before_encryption;
    std::string message;
    AES aes_object;

public:
    explicit BackEnd(QObject *parent = nullptr);

signals:
    void dialog_cancelled(QVariant dialog_name);
    void file_success(QVariant file_name);
    void file_not_open(QVariant operation);
    void encryption_complete(QVariant encrypted_msg);
    void decryption_complete(QVariant decrypted_msg);
    void saving_complete();


public slots:
    void open_file();
    void encrypt(QVariant aes_algorithm);
    void decrypt();
    void save_file(const std::string& text);


};

