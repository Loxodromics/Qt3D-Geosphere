//
//  geospheremesh.cpp
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//
#include "geospheremesh.h"
#include "geospheregeometry.h"

GeosphereMesh::GeosphereMesh(QNode* parent)
	: QGeometryRenderer(parent)
{
	GeosphereGeometry* geometry = new GeosphereGeometry(this);
	QGeometryRenderer::setGeometry(geometry);
	QGeometryRenderer::setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
}

GeosphereMesh::~GeosphereMesh() {}
