import QtQuick 2.11
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import softlock.encryption 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Softlock Encryption")

    Row {
        id: radio_buttons_choice
        spacing: 5
        anchors.bottom: buttons_grid.top
        property string aes_algorithm: "AES"
        property string encrypted_msg: ""

        RadioButton {
            id: aes
            text: qsTr("AES")

            onClicked: {
                aes_algorithm = "AES"
            }
        }
        RadioButton {
            id: aes_256
            text: qsTr("AES_256")

            onClicked: {
                aes_algorithm = "AES_256"
            }
        }
        RadioButton {
            id: aes_cbc
            text: qsTr("AES_CBC")

            onClicked: {
                aes_algorithm = "AES_CBC"
            }
        }
    }


    BackEnd {
        id: cpp_backend
    }

    Image {
        id: softlock_logo
        width: 300
        opacity: 0.7
        source: "qrc:/images/resources/images/softlock_logo.png"
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        id: footer
        color: "#47a65a"
        opacity: 1
        width: root.width
        height: root.height * 0.1
        anchors.bottom: parent.bottom

        Label {
            id: footer_text
            text: qsTr("Softlock - Information Security Solutions")
            y: footer.height/2 - 7
            x: 25
            color: "white"
            font.family: "Arial"
            font.pointSize: 9
            font.weight: Font.Medium
        }
    }

    Grid {
        id: buttons_grid
        spacing: 25
        anchors.centerIn: parent
        rows: 2
        columns: 2
        transform: Translate{y: -100}

        Button {
            id: browse_button
            text: qsTr("Browse")
            x: 100
            y: 100
            width: 200
            height: 50
            flat: false
            icon.color: "white"
            icon.height: 18
            icon.width: 18
            icon.source: "qrc:/icons/resources/icons/browse_icon.png"
            verticalPadding: 20
            horizontalPadding: 16
            background: Rectangle {
                id: browse_button_background
                anchors.centerIn: parent
                color: browse_button.down ? "#0063c6" : "#0073e5"
                radius: browse_button.width/12
                border.width: browse_button.hovered ? browse_button.height/20 : 0
                border.color: "#eb715a"
            }
            font.family: "Arial"
            font.pointSize: 10
            font.bold: true
            font.weight: Font.Medium

            contentItem :  Row {
                id: browse_button_row
                spacing: 8

                Image {
                    id: browse_button_icon
                    source: browse_button.icon.source
                    width: browse_button.icon.width
                    height: browse_button.icon.height
                    anchors.verticalCenter: parent.verticalCenter

                }
                Text {
                    id: browse_button_text
                    text: browse_button.text
                    font: browse_button.font
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            onClicked: {
                cpp_backend.open_file()
            }

        }
        Button {
            id: encrypt_button
            text: qsTr("Encrypt")
            x: 100
            y: 100
            width: 200
            height: 50
            flat: false
            icon.color: "white"
            icon.height: 18
            icon.width: 18
            icon.source: "qrc:/icons/resources/icons/encrypt_icon.png"
            verticalPadding: 20
            horizontalPadding: 16
            background: Rectangle {
                id: encrypt_button_background
                anchors.centerIn: parent
                color: encrypt_button.down ? "#0063c6" : "#0073e5"
                radius: encrypt_button.width/12
                border.width: encrypt_button.hovered ? encrypt_button.height/20 : 0
                border.color: "#eb715a"
            }
            font.family: "Arial"
            font.pointSize: 10
            font.bold: true
            font.weight: Font.Medium

            contentItem :  Row {
                id: encrypt_button_row
                spacing: 8

                Image {
                    id: encrypt_button_icon
                    source: encrypt_button.icon.source
                    width: encrypt_button.icon.width
                    height: encrypt_button.icon.height
                    anchors.verticalCenter: parent.verticalCenter

                }
                Text {
                    id: encrypt_button_text
                    text: encrypt_button.text
                    font: encrypt_button.font
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            onClicked: {
                encrypted_message = cpp_backend.encrypt(radio_buttons_choice.aes_algorithm)
            }
        }
        Button {
            id: decrypt_button
            text: qsTr("Decrypt")
            x: 100
            y: 100
            width: 200
            height: 50
            flat: false
            icon.color: "white"
            icon.height: 18
            icon.width: 18
            icon.source: "qrc:/icons/resources/icons/decrypt_icon.png"
            verticalPadding: 20
            horizontalPadding: 16
            background: Rectangle {
                id: decrypt_button_background
                anchors.centerIn: parent
                color: decrypt_button.down ? "#0063c6" : "#0073e5"
                radius: decrypt_button.width/12
                border.width: decrypt_button.hovered ? decrypt_button.height/20 : 0
                border.color: "#eb715a"
            }
            font.family: "Arial"
            font.pointSize: 10
            font.bold: true
            font.weight: Font.Medium

            contentItem :  Row {
                id: decrypt_button_row
                spacing: 8

                Image {
                    id: decrypt_button_icon
                    source: decrypt_button.icon.source
                    width: decrypt_button.icon.width
                    height: decrypt_button.icon.height
                    anchors.verticalCenter: parent.verticalCenter

                }
                Text {
                    id: decrypt_button_text
                    text: decrypt_button.text
                    font: decrypt_button.font
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        Button {
            id: save_button
            text: qsTr("Save")
            x: 100
            y: 100
            width: 200
            height: 50
            flat: false
            icon.color: "white"
            icon.height: 18
            icon.width: 18
            icon.source: "qrc:/icons/resources/icons/save_icon.png"
            verticalPadding: 20
            horizontalPadding: 16
            background: Rectangle {
                id: save_button_background
                anchors.centerIn: parent
                color: save_button.down ? "#0063c6" : "#0073e5"
                radius: save_button.width/12
                border.width: save_button.hovered ? save_button.height/20 : 0
                border.color: "#eb715a"
            }
            font.family: "Arial"
            font.pointSize: 10
            font.bold: true
            font.weight: Font.Medium

            contentItem :  Row {
                id: save_button_row
                spacing: 8

                Image {
                    id: save_button_icon
                    source: save_button.icon.source
                    width: save_button.icon.width
                    height: save_button.icon.height
                    anchors.verticalCenter: parent.verticalCenter

                }
                Text {
                    id: save_button_text
                    text: save_button.text
                    font: save_button.font
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            onClicked: {
                cpp_backend.save_file(encrypted_message)
            }
        }
    }


}
