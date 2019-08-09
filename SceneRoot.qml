//
//  SceneRoot.qml
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//

import Qt3D.Core 2.12
import Qt3D.Extras 2.12
import Qt3D.Input 2.12
import Qt3D.Render 2.12
import QtQuick 2.0 as QQ2

import LFD 1.0

Entity {
    id: sceneRoot

    property vector3d upVector: Qt.vector3d(0, 1, 0)

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane: 0.1
        farPlane: 1000.0
        position: Qt.vector3d(0.0, 2.0, 3.0)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "gray"
            }
        },
        InputSettings {
        }
    ]

    OrbitCameraController {
        id: orbitCameraController

        camera: camera
    }

    Entity {
        id: scene

        GeosphereMesh {
            id: geosphere
        }

        PhongMaterial {
            id: material
            diffuse: "blue"
        }

        DirectionalLight {
            id: directionalLight
            color: "white"
            intensity: 1
        }
    }

    Transform {
        id: geosphereTransform
        property real userAngle: 0.0
        matrix: {
            var m = Qt.matrix4x4()
            m.rotate(userAngle, upVector)
            return m
        }
    }

    QQ2.NumberAnimation {
        id: geosphereTransformAnimation
        target: geosphereTransform
        property: "userAngle"
        duration: 10000
        from: 0
        to: 360

        loops: QQ2.Animation.Infinite
        running: true
    }

    Entity {
        components: [geosphere, material, geosphereTransform]
    }
}
