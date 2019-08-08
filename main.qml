//
//  main.qml
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//

import QtQuick 2.12
import QtQuick.Scene3D 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt3D Geosphere")

    Scene3D {

        anchors.fill: parent
        focus: true

        aspects: ["input", "logic"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        SceneRoot {
        }
    }
}
