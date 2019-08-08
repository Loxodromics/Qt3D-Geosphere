//
//  geospheregeometry.cpp
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//
#include "geospheregeometry.h"
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/qbuffer.h>
#include <QVector3D>

#include <QDebug>

#include <limits>
#include <stdlib.h>

using namespace Qt3DRender;


GeosphereGeometry::GeosphereGeometry(Qt3DCore::QNode *parent)
	: Qt3DRender::QGeometry(parent)
	, m_positionAttribute(nullptr)
	, m_indexAttribute(nullptr)
	, m_vertexBuffer(nullptr)
	, m_indexBuffer(nullptr)
{
	this->init();
}

GeosphereGeometry::~GeosphereGeometry(){}

QAttribute* GeosphereGeometry::positionAttribute() const
{
	return this->m_positionAttribute;
}

QAttribute* GeosphereGeometry::indexAttribute() const
{
	return this->m_indexAttribute;
}

void GeosphereGeometry::init()
{
	m_positionAttribute = new QAttribute(this);
	m_indexAttribute = new QAttribute(this);
	m_vertexBuffer = new Qt3DRender::QBuffer(this);
	m_indexBuffer = new Qt3DRender::QBuffer(this);

	const int nVerts = 12;
	const int stride = 3 * sizeof(float);
	const int faces = 20;

	m_positionAttribute->setName(QAttribute::defaultPositionAttributeName());
	m_positionAttribute->setVertexBaseType(QAttribute::Float);
	m_positionAttribute->setVertexSize(3);
	m_positionAttribute->setAttributeType(QAttribute::VertexAttribute);
	m_positionAttribute->setBuffer(m_vertexBuffer);
	m_positionAttribute->setByteStride(stride);
	m_positionAttribute->setCount(nVerts);

	m_indexAttribute->setAttributeType(QAttribute::IndexAttribute);
	m_indexAttribute->setVertexBaseType(QAttribute::UnsignedShort);
	m_indexAttribute->setBuffer(m_indexBuffer);

	// Each primitive has 3 vertives
	m_indexAttribute->setCount(faces * 3);

	this->addAttribute(m_positionAttribute);
	this->addAttribute(m_indexAttribute);

	this->fillBuffers();
}

void GeosphereGeometry::fillBuffers()
{
	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;

	// Vertices
	const auto v0 = QVector3D(-X, 0.0f, Z);
	const auto v1 = QVector3D(X, 0.0f, Z);
	const auto v2 = QVector3D(-X, 0.0f, -Z);

	const auto v3 = QVector3D(X, 0.0f, -Z);
	const auto v4 = QVector3D(0.0f, Z, X);
	const auto v5 = QVector3D(0.0f, Z, -X);

	const auto v6 = QVector3D(0.0f, -Z, X);
	const auto v7 = QVector3D(0.0f, -Z, -X);
	const auto v8 = QVector3D(Z, X, 0.0f);

	const auto v9 = QVector3D(-Z, X, 0.0f);
	const auto v10 = QVector3D(Z, -X, 0.0f);
	const auto v11 = QVector3D(-Z, -X, 0.0f);

	const auto vertices = QVector<QVector3D>()
							<< v0 <<
							 v1 <<
							 v2 <<
							 v3 <<
							 v4 <<
							 v5 <<
							 v6 <<
							 v7 <<
							 v8 <<
							 v9 <<
							 v10 <<
							 v11;

	auto positionsBufferData = QByteArray();
	positionsBufferData.resize(vertices.size() * sizeof(QVector3D));
	auto rawPositionData = reinterpret_cast<QVector3D *>(positionsBufferData.data());
	memcpy(rawPositionData, vertices.constData(), vertices.size() * sizeof(QVector3D));

	m_vertexBuffer->setData(positionsBufferData);

	const int faces = 20;
	const int numIndices = 3 * faces;
	QByteArray indexBytes;
	indexBytes.resize(numIndices * sizeof(quint16));
	quint16 *indexPtr = reinterpret_cast<quint16 *>(indexBytes.data());

	const std::vector<quint16> indices = {1,4,0,
	4,9,0,
	4,5,9,
	8,5,4,
	1,8,4,
	1,10,8,
	10,3,8,
	8,3,5,
	3,2,5,
	3,7,2,
	3,10,7,
	10,6,7,
	6,11,7,
	6,0,11,
	6,1,0,
	10,1,6,
	11,0,9,
	2,11,9,
	5,2,9,
	11,2,7};

	for (const auto each : indices) {
		*indexPtr++ = each;
	}

	m_indexBuffer->setData(indexBytes);
}
