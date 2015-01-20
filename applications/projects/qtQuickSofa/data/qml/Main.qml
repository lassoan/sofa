import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.3
import SofaBasics 1.0
import SofaTools 1.0
import SofaWidgets 1.0

ApplicationWindow {
    id: root
    width: 1280
    height: 720
    title: Qt.application.name

    style: ApplicationWindowStyle {
        background: null
    }

    Component.onCompleted: {
        visible = true;
    }

    // dialog
    property FileDialog openSofaSceneDialog: openSofaSceneDialog
    FileDialog {
        id: openSofaSceneDialog
        nameFilters: ["Scene files (*.xml *.scn *.pscn *.py *.simu *)"]
        onAccepted: {
            scene.source = fileUrl;
        }
    }

    property FileDialog saveSofaSceneDialog: saveSofaSceneDialog
    FileDialog {
        id: saveSofaSceneDialog
        selectExisting: false
        nameFilters: ["Scene files (*.scn)"]
        onAccepted: {
            scene.save(fileUrl);
        }
    }

    menuBar: DefaultMenuBar {
        id: menuBar
        scene: scene
    }

    Scene {
        id: scene
    }

    DynamicSplitView {
        id: dynamicSplitView
        anchors.fill: parent
        uiId: 1
        sourceComponent: Component {
            DynamicContent {
                defaultContentName: "Viewer"
                sourceDir: "qrc:/SofaWidgets"
                properties: {"scene": scene}
            }
        }
    }

    statusBar: DefaultStatusBar {
        id: statusBar
        scene: scene
    }
}