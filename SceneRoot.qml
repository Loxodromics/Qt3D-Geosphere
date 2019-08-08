//
//  SceneRoot.qml
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//

import Qt3D.Core 2.12
import Qt3D.Render 2.12
import Qt3D.Extras 2.12
import Qt3D.Input 2.12

Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane: 0.1
        farPlane: 1000.0
        position: Qt.vector3d(0.0, 4.0, 6.0)
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

    Entity {
        id: scene

        DirectionalLight {
            id: directionalLight
            color: "white"
            intensity: 1
        }
    }
}
