//
//  geospheregeometry.h
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//
#ifndef GEOSPHEREGEOMETRY_H
#define GEOSPHEREGEOMETRY_H

#include <Qt3DExtras/qt3dextras_global.h>
#include <Qt3DRender/qgeometry.h>

namespace Qt3DRender {

class QAttribute;
class QBuffer;

}    // namespace Qt3DRender

class GeosphereGeometry : public Qt3DRender::QGeometry
{
	Q_OBJECT

public:
	explicit GeosphereGeometry(Qt3DCore::QNode *parent = nullptr);
	~GeosphereGeometry();

	Qt3DRender::QAttribute *positionAttribute() const;
	Qt3DRender::QAttribute *indexAttribute() const;
	Qt3DRender::QAttribute *normalAttribute() const;

protected:
	void init();
	void fillBuffers();

	Qt3DRender::QAttribute *m_positionAttribute = nullptr;
	Qt3DRender::QAttribute *m_indexAttribute = nullptr;
	Qt3DRender::QAttribute *m_normalAttribute = nullptr;
	Qt3DRender::QBuffer *m_vertexBuffer = nullptr;
	Qt3DRender::QBuffer *m_indexBuffer = nullptr;
};

#endif // GEOSPHEREGEOMETRY_H
