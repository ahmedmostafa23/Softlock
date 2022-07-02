import QtQuick 2.11
import QtQuick.Window 2.12
import QtQuick.Controls 2.14

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Softlock Encryption")

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
            x: 30
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
    }
}
